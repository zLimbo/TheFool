#include <fmt/format.h>

template <typename T, std::size_t N>
constexpr std::size_t array_size(T (&)[N]) noexcept
{
    return N;
}

int main() 
{
    int arr[10];
    constexpr size_t n = array_size(arr);

    fmt::println("array size: {}", n);


    return 0;
}