#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <span>
#include <functional>   //std::less, std::equal_to
#include <iterator>
#include <array>        // std::array 
#include <algorithm>    // std::transform
#include <cstddef>      // std::size_t
#include <string_view>

class Search {
private:
    static unsigned char lower_uc(unsigned char c) {
        return static_cast<unsigned char>(std::tolower(c));
    }

    bool compareStringsSearch(const std::string_view &a, const std::string_view &b) const {
        if (a.size() != b.size()) return false;
        for (size_t i = 0; i < a.size(); ++i) {
            if (lower_uc(static_cast<unsigned char>(a[i])) !=
                lower_uc(static_cast<unsigned char>(b[i])))
                return false;
        }
    return true;
    }

    bool compareStrings(const std::string &a, const std::string &b) {
        std::string A = a, B = b;
        transform(A.begin(), A.end(), A.begin(), ::tolower);
        transform(B.begin(), B.end(), B.begin(), ::tolower);
        return A < B;
    }
public:
    template <typename T, typename Value, typename Eq = std::equal_to<>>
    void search(T& arr, const Value& x, Eq eq = {}) const {
        auto s = std::span(arr);
        
        // Iterate over the array in order to
        // find the key x
        for (size_t i = 0; i < s.size(); i++) {
            if (eq(s[i], x)) {
                std::cout << "found" << std::endl;
                return;
            }
        }
        std::cout << "not found" << std::endl;
        return;
    }
    
    template <typename T>
    void search_ci(T& v, std::string_view x) {
        this->search(v, x, [this](const std::string& a, const std::string& b) {
            return compareStringsSearch(std::string_view(a), b);
        });
    }

    template <typename T>
    void quicksort_ci(T& v) {
        // lambda is defined *inside the class*, not in main
        this->quicksort(v, [this](const std::string& a, const std::string& b) {
            return compareStrings(std::string_view(a), b);
        });
    }
};



int main() {
    std::vector<int> vec = {1,2,3,4,5};
    int arr[] = {1,2,3,4,5};
    std::array<int, 5> c_arr = {1,2,3,4,5};


    std::cout << "Non-span test: \n" << std::endl;

    //testFunc(vec);
    //testFunc(arr);
    //testFunc(c_arr);

    return 0;
}