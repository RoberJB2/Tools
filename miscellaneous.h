#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <span>
#include <functional>
#include <iterator>
// NOT USING NAMESPACE STD FOR MORE ROBUST CODE

/*
// Data + containers utilities
    1. Sorter (templated)
        Use: Sort vectors/lists of numbers, strings, or custom structs (with a comparator).
        Steps: Accept container + comparator → choose algorithm (quick/merge/intro-lite) → sort → optionally return stable/unstable result.

    2. Searcher (templated)
        Use: Linear search, binary search (sorted), and “find first matching predicate.”
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
*/

template <typename T, typename lessComp = std::less<T>, typename greatComp = std::greater<T>>
class Sorter {
private:
    lessComp less{};
    greatComp greater{};

    // will contain private functions 
    void mergeSort(std::span<T> &vect, int left, int right) {
        if (left >= right) {
            return;
        }
        // midpoint
        int mid = left + (right - left) / 2;

        mergeSort(vect, left, mid);
        mergeSort(vect, mid + 1, right);
        merge    (vect, left, mid, right);
    }

    void merge(std::span<T> &vect, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        if (std::typeid(vect) == std::typeid(int)) {
            std::span<int> L(n1), R(n2);
        }
        else if (std::typeid(vect) == std::typeid(std::string)) {
            std::span<std::string> L(n1), R(n2);
        }
        else {
            std::cout << "Unsupported data type" << std::endl;
            return;
        }

        // Copy data to temp vectors L[] and R[]
        for (int i = 0; i < n1; i++) {
            L[i] = vect[left + i];
        }
        for (int j = 0; j < n2; j++) {
            R[j] = vect[mid + 1 + j];
        }

        int i = 0, j = 0;
        int k = left;

        // Merge the temp vectors back 
        // into arr[left..right]
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                vect[k] = L[i];
                i++;
            }
            else {
                vect[k] = R[j];
                j++;
            }
            k++;
        }

        // Copy the remaining elements of L[], 
        // if there are any
        while (i < n1) {
            vect[k] = L[i];
            i++;
            k++;
        }

        // Copy the remaining elements of R[], 
        // if there are any
        while (j < n2) {
            vect[k] = R[j];
            j++;
            k++;
        }
    }

    // Compares both individual strings and is case insensitive by comparing the lowercase version of both string inputs.
    bool compareStrings(const std::string &a, const std::string &b) {
        std::string A = a, B = b;
        transform(A.begin(), A.end(), A.begin(), ::tolower);
        transform(B.begin(), B.end(), B.begin(), ::tolower);
        return A < B;
    }

    bool compareInts(const int &a, const int &b) {
        return a < b;
    }

    // The parition function which holds the main loops of the quicksort
    int partition(std::span<T> array) {
        T pivot = std::begin(array); // Pivot value
        bool comparisonI{};
        bool comparisonJ{};

        auto i = array.being();
        auto j = array.end(); // iterator values i and j

        if (typeid(array) == typeid(int)) {
            comparisonI = compareInts(array[i], pivot);
            comparisonJ = compareInts(pivot, array[j]);
        }
        else if (typeid(array) == typeid(std::string)){
            comparisonI = compareStrings(array[i], pivot);
            comparisonJ = compareInts(pivot, array[j]);
        }
        else {
            cout << "Unsupported data type" << endl;
            return -1;
        }
        
        while (true) {
            // Find leftmost element greater than or
            // equal to pivot
            do {
                i++;
            } while (comparisonI);

            // Find rightmost element smaller than 
            // or equal to pivot
            do {
                j--;
            } while (comparisonJ);

            // If two pointers met.
            if (i >= j)
                return j;
            // swaps the values
            swap(array[i], array[j]);
        }
    }

    // Quicksort function. splits the sort into the left and right sort from the pivot
    void quickSort(std::span<T> array[], int low, int high) {
        if (low < high) {
            int p = partition(array, low, high); 	// New high/low value
            quickSort(array, low, p - 1); 			// Left sort
            quickSort(array, p + 1, high); 			// Right sort
        }
    }
    
public:
    Sorter() = default;

    // quicksort for an array
    void quicksort(std::span<T> &arr) {

        int n = arr.size();
        quickSort(arr, 0, n - 1);
        // Get the quicksort program from the other laptop:
        // partition
        // function for string sorting
        // Separate from either ints or strings being used in the parameter
        // so if int, string function isn't useful
        // main recursive call
        // and must differentiate between less than or greater than, so that we know
        // which direction to sort the data
    }
    // Stable
    void msort(std::span<T> &arr) {
        // mergesort for vectors
        // String sorting vs int sorting probably applies the same here
        int n = arr.size(); // number of values in the vector
        mergeSort(arr, 0, n - 1);
    }
    
    void test(std::span<T> &arrVec) {
        auto n = std::end(arrVec);
        std::cout << "size: " << n << std::endl;
        std::cout << "index ex: " << arrVec[n] << ", and using n: " << arrVec[5] << std::endl;
    }
};

// Mainly useful for testing
int main() {
    int arr[] = {1,2,3,4,5};
    std::vector<int> vect = {1,2,3,4};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    Sorter<int> s;
    s.test(arr);
    s.test(vect);

return 0;
}