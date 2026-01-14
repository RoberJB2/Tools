#include <span>
#include <iostream>
#include <vector>
#include <array>
#include <typeinfo>
#include <ranges>

template <typename T>
void testFuncSpan(const T& arr) {
    auto s = std::span(arr);
    for (const auto& value : s) {
        std::cout << value << ", ";
    }
    std::cout << "\n\n";
}

int main() {
    std::vector<int> vec = {1,2,3,4,5};
    int arr[] = {1,2,3,4,5};
    std::array<int, 5> c_arr = {1,2,3,4,5};

    testFuncSpan(vec);
    testFuncSpan(arr);
    testFuncSpan(c_arr);

    std::cout << "Non-span test: \n" << std::endl;

    //testFunc(vec);
    //testFunc(arr);
    //testFunc(c_arr);

    return 0;
}