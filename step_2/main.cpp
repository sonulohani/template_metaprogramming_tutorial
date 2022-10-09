#include <iostream>
#include <type_traits>

template <typename T>
struct is_pointer {
    static constexpr bool value = false;
};

template <typename T>
struct is_pointer<T*> {
    static constexpr bool value = true;
};

template <typename T>
struct strip_pointer {
    using type = T;
};

template <typename T>
struct strip_pointer<T*> {
    using type = T;
};

template <typename T>
void print(T t)
{
    using T_without_pointer = typename strip_pointer<T>::type;
    if constexpr (std::is_pointer<T>::value && std::is_floating_point_v<T_without_pointer>) {
        std::cout << *t;
    } else {
        std::cout << t;
    }
    std::cout << '\n';
}

int main()
{
    float a = 1.0;
    float b = 2.0;
    std::string str = "hello";
    print(&a);
    print(&b);
    print(&str);
    return 0;
}
