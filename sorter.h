#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <span>
#include <functional>
#include <iterator>
#include <array>        // std::array 
#include <algorithm>    // std::transform
#include <cctype>       // std::toupper/tolower
#include <utility>      // std::swap
#include <cstddef>      // std::size_t
// NOT USING NAMESPACE STD FOR MORE ROBUST CODE

/*
1. Sorter (templated)
    Use: Sort vectors/lists of numbers, strings, or custom structs (with a comparator).
    Steps: Accept container + comparator → choose algorithm (quick/merge/intro-lite) → sort → optionally return stable/unstable result.
    Goals:
        - allow both arrays and vectors to be input in the function (CHECK)
        - create a system (something like sorter::quicksort()) 
          to create easier access to different sorting capabilities for the user.
        - A later version might include std::variants as part of the program to handle more complex data sets
    Major Issues during Programming:
        - Understanding typename and span. The compilar wants to decide these separately
            Can not decide them both at the same time ex: "std::span<T> someVariableName" can not be a function param
            unless you are passing in a variable of type T.
        
*/

class Sorter {
private:
    // will contain private functions 
    template <typename T, typename Less>
    void mergeSort(T& arr, int left, int right, Less less) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, less);
        mergeSort(arr, mid + 1, right, less);
        merge    (arr, left, mid, right, less);
    }

    template <typename T, typename Less >
    void merge(T& arr, int left, int mid, int right, Less less) {
        // Takes span separately of computing the type of the input variable const T& arr
        // This is because the compilar can't do both at the same type
        // Ex: std::span<T> arr can't be a function parameter. Compiler can't compute span and T
        // So it asks you to pass in a variable of type T, w/ computing T
        auto s = std::span(arr);

        int n1 = mid - left + 1;
        int n2 = right - mid;

        using Elem = typename decltype(s)::element_type;

        // REAL temp buffers (do not alias s)
        std::vector<Elem> L;
        std::vector<Elem> R;
        L.reserve(n1);
        R.reserve(n2);

        for (int i = 0; i < n1; ++i) L.push_back(s[left + i]);
        for (int j = 0; j < n2; ++j) R.push_back(s[mid + 1 + j]);

        int i = 0, j = 0, k = left;

        // Stable merge using comparator:
        // take from left when equal
        while (i < n1 && j < n2) {
            if (!less(R[j], L[i])) {     // i.e., L[i] <= R[j]
                s[k++] = L[i++];
            } else {
                s[k++] = R[j++];
            }
        }

        while (i < n1) s[k++] = L[i++];
        while (j < n2) s[k++] = R[j++];
    }

    // Compares both individual strings and is case insensitive by comparing the lowercase version of both string inputs.
    bool compareStrings(const std::string &a, const std::string &b) {
        std::string A = a, B = b;
        transform(A.begin(), A.end(), A.begin(), ::tolower);
        transform(B.begin(), B.end(), B.begin(), ::tolower);
        return A < B;
    }

    // Used for mergesort and deals with upper and lower case characters/strings
    bool compareStringsMerge(const std::string &a, const std::string &b) {
        std::string A = a, B = b;
        transform(A.begin(), A.end(), A.begin(), ::tolower);
        transform(B.begin(), B.end(), B.begin(), ::tolower);
        return A <= B;
    }

    template <typename T, std::size_t Extent, typename Less>
    int partition(std::span<T, Extent> s, int low, int high, Less less) {
        auto pivot = s[low];      // pivot value (copy)
        int i = low - 1;
        int j = high + 1;

        while (true) {
            do { ++i; } while (less(s[i], pivot));   // while s[i] < pivot
            do { --j; } while (less(pivot, s[j]));   // while pivot < s[j]

            if (i >= j) return j;
            std::swap(s[i], s[j]);
        }
    }

    template <typename T, std::size_t Extent, typename Less>
    void quickSort(std::span<T, Extent> s, int low, int high, Less less) {
        if (low >= high) return;

        int p = partition(s, low, high, less);
        quickSort(s, low, p, less);        // left:  [low..p]
        quickSort(s, p + 1, high, less);   // right: [p+1..high]
    }

public:
    Sorter() = default;

    //template <typename T>
    //explicit Sorter(std::greater<T>& greatOp = std::greater) : greatOp_(greatOp) {}

    //template <typename T>
    //explicit Sorter(std::less<T>& lessOp = std::less) : lessOp_(lessOp) {}
    // quicksort for an array
    template <typename T, typename Less = std::less<>>
    void quicksort(T& arr, Less less = {}) {
        auto s = std::span(arr);
        if (s.empty()) {
            std::cout << "data set is empty\n";
            return;
        }

        int high = static_cast<int>(s.size()) - 1;   // safe unless size > INT_MAX
        quickSort(s, 0, high, less);

        std::cout << "Quick Sort: ";
        for (int i = 0; i < s.size(); i++) {
            std::cout << s[i] << ", ";
        }
        std::cout << "\n\n";
    }

    template <typename T, typename Less = std::less<>>
    void msort(T& arr, Less less = {}) {
        auto s = std::span(arr);
        if (s.empty()) {
            std::cout << "data set is empty\n";
            return;
        }

        int high = static_cast<int>(s.size()) - 1;
        mergeSort(s, 0, high, less);

        std::cout << "Merge Sort: ";
        for (int i = 0; i < s.size(); i++) {
            std::cout << s[i] << ", ";
        }
        std::cout << "\n\n";
    }
    template <typename T>
    void quicksort_ci(T& v) {
        // lambda is defined *inside the class*, not in main
        this->quicksort(v, [this](const std::string& a, const std::string& b) {
            return compareStrings(a, b);
        });
    }
    template <typename T>
    void msort_ci(T& v) {
        this->msort(v, [this](const std::string& a, const std::string& b) {
            return compareStringsMerge(a, b);
        });
    }
};

// Mainly useful for testing
int main() {
    int arr[] = {6,2,7,4,3};
    std::string arrString[] = {"hello", "make", "fish", "apple", "BOGO", "banana", "WoAh", "woah", "werewolf"};
    char arrChar[] = {'a', 'c', 'B', 'F', 'Z', 'g', '1', 'v', 'i', 'b'};
    
    std::vector<int> vec = {1,8,0,25,13};
    std::vector<std::string> vecString = {"hello", "make", "fish", "apple", "BOGO", "banana", "WoAh", "woah", "werewolf"};
    
    std::array<int, 5> arrSTD = {9,20,3,7,1};
    std::array<std::string, 9> stringSTD = {"hello", "make", "fish", "apple", "BOGO", "banana", "WoAh", "woah", "werewolf"};

    Sorter s;
    // All tests below function properly, except for a slight difference between the merge and quicksort
    // Where quicksort appears to be stable and merge isn't. Which is odd. The "WoAh", and "woah" are swapped.

    //s.test(arr);
    //s.test(vec);
    
    //s.msort(arr);
    //s.quicksort(arr);
    //s.msort(vec);
    //s.quicksort(vec);

    //s.msort(arrChar);
    //s.quicksort(arrChar);
    //s.msort(arrString);
    //s.quicksort(arrString);
    //s.msort(vecString);
    //s.quicksort(vecString);

    // Case-Insensitive, only used for strings.
    //s.msort_ci(vecString);
    //s.quicksort_ci(vecString);
    //s.msort_ci(arrString);
    //s.quicksort_ci(arrString);

    //s.msort(arrSTD);
    //s.quicksort(arrSTD);
    //s.msort(stringSTD);
    //s.quicksort(stringSTD);
    //s.msort_ci(stringSTD);
    //s.quicksort_ci(stringSTD);

return 0;
}