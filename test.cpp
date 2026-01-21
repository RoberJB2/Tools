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

bool compareTest() {
    std::string A = "bad";
    std::string B = "good";
    transform(A.begin(), A.end(), A.begin(), ::tolower);

    for (int i = 0; i < A.length() && i < B.length(); i++) {
        if (A[i] == B[i]) {
            continue;
        }
        else if (true) {
            continue;
        }
    }
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