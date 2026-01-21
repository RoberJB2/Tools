#include "sorter.h"
/*
// Data + containers utilities
    1. Sorter (templated) - DONE
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

// Compile using g++ -std=c++20 for span.
// Modified compareStrings function for Searching
bool compareStringsSearch(std::string &a, std::string &b) {
    std::string A = a, B = b;
    transform(A.begin(), A.end(), A.begin(), ::tolower);
    transform(B.begin(), B.end(), B.begin(), ::tolower);

    int sizeA = A.length();
    int sizeB = B.length();
    int sizeOp{};

    if (sizeA > sizeB) {
        return false;
    }
    else if (sizeA < sizeB) {
        return false;
    }

    for (int i = 0; i < sizeOp; i++) {
        if (A[i] == B[i]) {
            continue;
        }
        else {
            return false;
        }
    }
return true;
}

// Binary Search
template <typename T, typename value>
auto binarySearch(T& arr, const value& x) {
    auto s = std::span(arr);
    int low = 0;
    int high = s.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (s[mid] == x)
            return mid;

        // If x greater, ignore left half
        if (s[mid] < x)
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }

    // If we reach here, then element was not present
    std::cout << "nothing found" << std::endl;
    return;
}

// Linear Search
template <typename T, typename value>
auto search(T& arr, const value& x) {
    auto s = std::span(arr);
    
    // Iterate over the array in order to
    // find the key x
    for (int i = 0; i < s.size(); i++)
        if (s[i] == x)
            return i;
    return;
}

// Lambda for string searches
template <typename T>
void binarySearch_ci(T& v) {
    this->binarySearch(v, [this](const std::string& a, const std::string& b) {
        return compareStringsSearch(a, b);
    });
}
template <typename T>
void search_ci(T& v) {
    this->search(v, [this](const std;;string& a, const std::string& b) {
        return compareStringsSearch(a, b);
    });
}

int main() {
    // TESTING /////
    // Object from Sorter.h
    Sorter s;

    // Instantiation:
    int arr[] = {9,5,7,4,12};
    int arrNo[] = {9,7,3,1,5,6,3,7};
    std::array<int, 5> arrSTD = {1,2,3,4,5};
    std::vector<int> vec = {1,7,3,7,9,5,2};

    std::string arrString[] = {"woah", "squib", "blarp", "yaga", "bsdfdsf", "meow"};
    std::array<std::string, 5> strSTD = {"woah", "squib", "blarp", "yaga", "waka"};
    std::vector<std::string> vecStr = {"banana", "apple", "nyoom", "woah", "squib", "blarp", "yaga", "waka"};

    // Sort data
    s.quicksort(arr);
    s.quicksort(vec);
    s.quicksort(arrString);
    s.quicksort(strSTD);
    s.quicksort(vecStr);

    // Search data
    int result = binarySearch(arr, 5);
    int result2 = search(arrNo, 7);
    int result3 = binarySearch(vec, 9);

    std::string resultStr = binarySearch_ci(arrString, "yaga");
    std::string resultStr2 = search_ci(arrString, "blarp");
    std::string resultStr3;

    // Output results:
    std::cout << arr[result] << " at " << result << ", " << arrNo[result2] << " at " << result2 << std::endl;

return 0;
}