#include <fmt/format.h>
#include <type_traits>

template <typename T, std::size_t N>
constexpr std::size_t array_size(T (&)[N]) noexcept
{
    return N;
}



template <typename T>
constexpr bool f(T &x)
{
    return std::is_reference_v<T>;
}

int main() 
{
    int arr[10];
    constexpr size_t n = array_size(arr);

    fmt::println("array size: {}", n);

    const volatile int * const volatile y = new int{10};
    auto b0 = f(y);
    auto b = f(10);

    decltype(b) b1;
    decltype((b)) b2 = b1;
    


    return 0;
}