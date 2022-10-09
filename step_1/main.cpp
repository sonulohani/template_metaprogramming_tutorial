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
void print(T t)
{
    if constexpr (std::is_pointer<T>::value) {
        std::cout << *t;
    } else {
        std::cout << t;
    }
    std::cout << '\n';
}

int main()
{
    print(1);
    int i = 9;
    print(&i);
    return 0;
}
