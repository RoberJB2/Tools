#include <span>
#include <iostream>
#include <vector>
#include <array>
#include <typeinfo>

template <typename T>
void testFunc(std::span<T> arrVec) {
    for (T& value : arrVec) {
        std::cout << value << ", ";
    }
    std::cout << "\n" << endl;
}

template <typename T>
void printSpan(std::span<const T> s) {
    for (const T& x : s) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> vector;
    int arr[] = {1,2,3,4,5};
    std::array<int, 5> c_arr = {1,2,3,4,5};
    testFunc(vector);
    testFunc(arr);

    return 0;
}