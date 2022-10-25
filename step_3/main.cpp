#include <iostream>
#include <vector>
#include <string>
#include <tuple>

template<bool condition, typename THEN, typename ELSE>
struct if_;

template<typename THEN, typename ELSE>
struct if_<true, THEN, ELSE>
{
    using type = THEN;
};

template<typename THEN, typename ELSE>
struct if_<false, THEN, ELSE>
{
    using type = ELSE;
};

template<typename SEARCH, typename TUPLE, size_t start_from=0>
struct contains_type : if_<// IF
        std::is_same<std::tuple_element_t<start_from, TUPLE>, SEARCH>::value,
        // THEN
        std::true_type,
        // ELSE
        typename if_< //IF
        (start_from==std::tuple_size<TUPLE>::value - 1),
        // THEN
        std::false_type,
        // ELSE
        contains_type<SEARCH, TUPLE, start_from + 1>>::type>::type
{

};

template<typename SEARCH>
struct contains_type<SEARCH, std::tuple<>, 0> : std::false_type
{

};

bool contains(const std::string& search, const std::vector<std::string>& v, size_t start_from=0) {
    if(v[start_from] == search) {
        return true;
    } else {
        if(start_from == v.size() - 1){
            return false;
        }
        else {
            return contains(search, v, start_from + 1);
        }
    }

}

int main() {
    std::vector<std::string> vec{"int", "bool", "float"};
    std::cout << std::boolalpha << contains("double", vec) << '\n';
    std::cout << std::boolalpha << std::is_same_v<int, if_<(10>5), int, float>::type> << '\n';
    std::tuple<int, bool, float> t{};
    std::cout << std::boolalpha << contains_type<int, decltype(t)>::value << '\n';
    std::cout << std::boolalpha << contains_type<double, decltype(t)>::value << '\n';
    std::cout << std::boolalpha << contains_type<double, std::tuple<>>::value << '\n';
}
