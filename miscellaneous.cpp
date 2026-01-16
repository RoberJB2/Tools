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
// Data + containers utilities
    1. Sorter (templated)
        Use: Sort vectors/lists of numbers, strings, or custom structs (with a comparator).
        Steps: Accept container + comparator → choose algorithm (quick/merge/intro-lite) → sort → optionally return stable/unstable result.

    2. Searcher (templated)
        Use: Linear search (unsorted), binary search (sorted), and “find first matching predicate.”
        Steps: Accept container + target/predicate → pick search mode → scan or binary search → return index/iterator + “found” flag.

    3. Uniq + Deduper
        Use: Remove duplicates from a container (sorted or unsorted).
        Steps: If unsorted: track seen keys → rebuild container; if sorted: sweep and skip repeats → return new size/result.

    4. SetOps
        Use: Union/intersection/difference of two containers.
        Steps: Normalize (sort or hash) → compute requested operation → output container.

    5. Chunker / Batcher
        Use: Split a vector into fixed-size chunks (pagination, batch processing).
        Steps: Take container + chunk size → create subranges → return vector of slices/ranges.

    6. RingBuffer
        Use: Fixed-capacity buffer for streaming inputs (logs, sensor samples).
        Steps: Allocate capacity → push overwriting oldest when full → pop/peek → expose current size/order.

    7. LRUCache (small)
        Use: Cache computed values (parsing, expensive transforms).
        Steps: get(key) updates recency → put(key,val) evicts least-recently-used if full → maintain map + order.

    8. FrequencyCounter
        Use: Counts occurrences of items (words, IDs).
        Steps: Iterate inputs → increment counts → expose top-K / sorted frequencies / percent breakdown.

    9.BidirectionalMap
        Use: Map name↔ID lookups without duplicating data.
        Steps: Insert pair → store in both maps → enforce uniqueness → allow erase by either side.

    10. RangeTools
        Use: Clamp, map ranges, normalize values, generate integer ranges.
        Steps: Validate bounds → compute clamp/normalize/map → return transformed results.

// Strings + text processing

    11. StringSplitter
        Use: Split on delimiters, CSV-ish splitting (basic), trimming tokens.
        Steps: Scan string → detect delimiter boundaries → emit tokens → optional keep-empty → optional trim.

    12. StringBuilder (lightweight)
        Use: Efficient concatenation for generating logs/output.
        Steps: Append pieces → optional join with delimiter → output final string.

    13. CaseConverter
        Use: lower/upper/title/snake_case↔camelCase conversions.
        Steps: Scan chars → detect word boundaries → apply casing rules → rebuild.

    14. FuzzyMatchLite
        Use: “Did the user mean…?” for commands, names (typo tolerance).
        Steps: Normalize strings → compute simple distance score → pick best matches → threshold acceptance.

    15. PatternFinder
        Use: Find all occurrences, highlight ranges, replace all.
        Steps: Search through text → record start/end indices → optionally apply replacements → return result + match list.

    16. Tokenizer
        Use: Turn text into tokens (identifiers, numbers, punctuation) for mini-parsers.
        Steps: Iterate chars → classify sequences → emit token objects → store positions for error reporting.

    17. MiniFormatter
        Use: Format tables/columns for console output.
        Steps: Compute column widths → align left/right/center → render lines → optional borders.

// File + config helpers (still header-only friendly)

    18. PathTools
        Use: Join paths, normalize separators, extract filename/extension.
        Steps: Parse path → apply normalization rules → combine segments safely → return final path pieces.

    19. FileLoader
        Use: Read entire file, read lines, write text file safely.
        Steps: Open → validate → read bytes/lines → close → return optional error status.

    20. SimpleConfig (INI-like)
        Use: Lightweight key=value settings without bringing in a full parser.
        Steps: Read lines → ignore comments → split key/value → store typed getters (string/int/bool) → defaults.

    21. CSVTableLite
        Use: Load/save basic CSV for small datasets.
        Steps: Read file → split rows/columns → store as vector<vector<string>> → allow column access → write out.

// Validation + parsing

    22. Validator
        Use: Central place for “is integer?”, “in range?”, “matches allowed set?”
        Steps: Provide static checks → return bool + message → optional accumulate multiple errors.

    23. NumberParser
        Use: Parse ints/doubles safely with error handling.
        Steps: Strip whitespace → detect sign/base → parse → detect overflow/invalid → return optional/result+error.

    24. DateTimeLite
        Use: Parse and format timestamps (limited scope: ISO-like).
        Steps: Validate pattern → parse components → range-check → format back → compare/compute simple deltas.

    25. EnumMapper
        Use: Convert between strings and enum values (CLI args, config).
        Steps: Register pairs → lookup by string → return enum or error → reverse lookup to string.

// Logging + debugging utilities

    26. Logger (levels + sinks)
        Use: Uniform logging without rewriting it each project.
        Steps: Define levels → write to console/file → timestamp + tag → filter by level → optional ring buffer.

    27. Timer / ProfilerLite
        Use: Time code sections and report elapsed durations.
        Steps: Start/stop → compute duration → aggregate by label → print summary.

    28. EventBusLite
        Use: Simple pub/sub for decoupling modules (UI events, game events).
        Steps: Subscribe callbacks by event name/type → publish event payload → call listeners → allow unsubscribe.

// Math + common algorithms

    29. StatsLite
        Use: mean/median/stddev/min/max/percentiles for numeric vectors.
        Steps: Validate non-empty → compute aggregates → sort if needed for median/percentiles → return results struct.

    30. RandomTools
        Use: Uniform int/double, shuffle, sample without replacement.
        Steps: Seed generator → provide randInt, randReal → implement shuffle → implement sample-K.
*/

// Current generic "tool" class which will be altered and split into different .h files for more specified use cases.

class tools {
private:
    
public:
    
};

// PROTOTYPE CODE:
// This code is in development and not implemented as a class or inside a class.
// Useful as an experimenting space and as a way to better keep track of the many lines of code

// CURRENT TASK:
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
    // WORKS
    //s.test(arr);
    //s.test(vec);
    // WORKS
    //s.msort(arr);
    //s.quicksort(arr);
    //s.msort(vec);
    //s.quicksort(vec);

    // Testing:
    s.msort(arrChar);
    s.quicksort(arrChar);
    s.msort(arrString);
    s.quicksort(arrString);
    s.msort(vecString);
    s.quicksort(vecString);

    // Case-Insensitive, only used for strings.
    s.msort_ci(vecString);
    s.quicksort_ci(vecString);
    s.msort_ci(arrString);
    s.quicksort_ci(arrString);

return 0;
}