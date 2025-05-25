# Digit-Shift Sort Algorithm

This repository contains an implementation of the "Digit-Shift Sort" algorithm, a stable, in-place sorting algorithm that operates by iteratively sorting numbers based on their digits, from the least significant to the most significant.

## What is Digit-Shift Sort?

Digit-Shift Sort is a variation of the Radix Sort algorithm (specifically, LSD - Least Significant Digit first). Unlike traditional Radix Sort which typically uses counting sort or bucket sort as its stable subroutine for each digit pass, Digit-Shift Sort employs a shifting and insertion mechanism reminiscent of Insertion Sort.

The key idea is:

1.  **Find the Maximum Value:** Determine the largest number in the array to know how many digit passes are required (i.e., the number of digits in the maximum value).
2.  **Iterate Through Digits:** Starting from the units digit (least significant), and moving to the tens, hundreds, and so on.
3.  **Digit-Based Shifting:** For each digit position:
    *   The algorithm iterates through the array, taking each element (`current_num`).
    *   It extracts the `current_digit` of `current_num` for the current `exp` (exponent, e.g., 1, 10, 100).
    *   It then shifts elements to the left (`prev_num`) to the right (`arr[j+1] = arr[j]`) *only if* their `prev_digit` (at the same `exp` position) is greater than `current_digit`.
    *   **Stability:** If `prev_digit` is equal to `current_digit`, the shifting stops. This crucial step ensures that elements with the same digit value maintain their original relative order from previous passes, making the algorithm stable.
    *   Finally, `current_num` is inserted into its correct position based on its `current_digit`.

This process repeats for each digit position until all digits of the maximum number have been processed.

## Implementations

The algorithm has been implemented in:

*   Python (`digit_shift_sort.py`)
*   C++ (`digit_shift_sort.cpp`)
*   JavaScript (`digit_shift_sort.js`)

Each implementation adheres to the core logic described above and includes example usage and basic tests.

## Complexity Analysis

The complexity of Digit-Shift Sort depends on the number of elements (`N`) and the number of digits (`D`) in the largest number. Let `D` be the number of digits in `max_val` (i.e., `D = floor(log10(max_val)) + 1`).

### Time Complexity

*   **Finding Max Value (`get_max`):** O(N)
*   **Outer Loop (Digit Passes):** The `while` loop runs `D` times (once for each digit).
*   **Inner Loops (Shifting/Insertion):**
    *   The main `for` loop runs `N` times for each digit pass.
    *   The nested `while` loop (the shifting part) behaves like the inner loop of Insertion Sort. In the worst case, an element might need to be shifted up to `N` positions to the left.
    *   Therefore, each digit pass can take O(N^2) time in the worst case (similar to Insertion Sort's worst case).

*   **Overall Time Complexity:**
    *   **Worst Case:** O(D \* N^2)
    *   **Average Case:** O(D \* N^2)
    *   **Best Case:** O(D \* N) (when the array is already mostly sorted for each digit pass)

**Note:** This algorithm, due to its Insertion Sort-like inner mechanism, is generally less efficient in terms of time complexity than a standard Radix Sort (which typically achieves O(D \* (N + B)) where B is the base, usually 10, often simplified to O(D \* N)). However, it achieves *in-place* sorting.

### Space Complexity

*   The algorithm sorts the array directly in place.
*   It only uses a few auxiliary variables (`n`, `max_val`, `exp`, `current_num`, `j`, etc.).

*   **Auxiliary Space Complexity:** O(1)

This O(1) auxiliary space is a significant advantage over traditional Radix Sort, which usually requires O(N + B) auxiliary space for its buckets/queues.

## Comparison with Common In-Place Sorting Algorithms

Here's a comparison of Digit-Shift Sort with other common in-place sorting algorithms:

| Algorithm           | Time Complexity (Best) | Time Complexity (Average) | Time Complexity (Worst) | Space Complexity (Auxiliary) | Stable |
| :------------------ | :--------------------- | :------------------------ | :---------------------- | :--------------------------- | :----- |
| **Digit-Shift Sort**| O(D \* N)              | O(D \* N^2)               | O(D \* N^2)             | O(1)                         | Yes    |
| Bubble Sort         | O(N)                   | O(N^2)                    | O(N^2)                  | O(1)                         | Yes    |
| Insertion Sort      | O(N)                   | O(N^2)                    | O(N^2)                  | O(1)                         | Yes    |
| Selection Sort      | O(N^2)                 | O(N^2)                    | O(N^2)                  | O(1)                         | No     |
| Quick Sort          | O(N log N)             | O(N log N)                | O(N^2)                  | O(log N) - O(N)              | No     |
| Heap Sort           | O(N log N)             | O(N log N)                | O(N log N)              | O(1)                         | No     |

**Key Takeaways from the Comparison:**

*   **In-Place and Stable:** Digit-Shift Sort stands out by being both in-place (O(1) space) and stable. This is a combination not found in algorithms like Quick Sort or Heap Sort, which are faster but not stable, or require more space for stability.
*   **Performance Trade-off:** While it offers O(1) space and stability, its O(D \* N^2) worst-case time complexity makes it less efficient than comparison-based algorithms like Quick Sort or Heap Sort for general purpose sorting, especially for large `N` or numbers with many digits (`D`). It's also less efficient than a traditional Radix Sort in terms of time.
*   **Niche Use:** This algorithm might be interesting for specific scenarios where O(1) auxiliary space *and* stability are absolute requirements for sorting numbers, and `N` or `D` are relatively small.

## Usage

To run the examples:

**Python:**
```bash
python your_script_name.py
```

**C++:**
```bash
g++ your_script_name.cpp -o digit_shift_sort
./digit_shift_sort
```

**JavaScript (Node.js):**
```bash
node your_script_name.js
```

The example usage sections in each respective file will print the original and sorted arrays, demonstrating the algorithm's functionality.
