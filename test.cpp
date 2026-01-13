#include <span>
#include <iostream>
#include <vector>
#include <array>
#include <typeinfo>
#include <ranges>

template <std::ranges::sized_range Range>
void testFunc(Range &&span) {
    using T = std::ranges::range_value_t<Range>;
    // used to initialize T variables:
    T sum{};

    for (const auto element : span) {
        std::cout << element << ", ";
    }
    std::cout << "\n\n";
}

int main() {
    std::vector<int> vec = {1,2,3,4,5};
    int arr[] = {1,2,3,4,5};
    std::array<int, 5> c_arr = {1,2,3,4,5};

    testFunc(vec);
    testFunc(arr);
    testFunc(c_arr);

    return 0;
}