# Sorting Algorithms Analysis 
- CPTS223, MA4, Itay Shemesh

## Question 1, Comparison
| Algorithm        | Min Time (ms) | Max Time (ms) | Average Time (ms) | Std Deviation (ms) |
|:----------------:|:-------------:|:-------------:|:-----------------:|:------------------:|
| Insertion Sort   | 6.644         | 7.417         | 6.813             | 0.208              |
| Quick Sort       | 0.363         | 0.389         | 0.372             | 0.007              |
| Shell Sort       | 0.437         | 0.468         | 0.443             | 0.009              |
| Heap Sort        | 0.353         | 0.401         | 0.362             | 0.013              |

## Question 2
### Observations
- **Heap Sort** achieved the fastest minimum runtime (0.353 ms) overall.
- **Quick Sort** was very close in performance to Heap Sort, with a slightly higher maximum time.
- **Shell Sort** performed better than Insertion Sort, but was still slower than Heap and Quick Sort.
- **Insertion Sort** was significantly slower than all other algorithms, with runtimes about 10x higher.
### Reasoning
- **Insertion Sort** operates with O(n²) time complexity, making it inefficient for large random datasets (10,000 elements). It performs well only on very small or nearly sorted arrays.
- **Quick Sort** and **Heap Sort** both have O(n log n) complexity:
  - Quick Sort benefits from better average-case performance due to efficient partitioning of elements around a pivot.
  - Heap Sort, although having O(n log n) worst-case complexity, incurs slightly more overhead due to heap maintenance operations.
- **Shell Sort** reduces the number of inversions compared to Insertion Sort by comparing distant elements first. Its approximate complexity of O(n^4/3) makes it much closer to Quick Sort and Heap Sort in terms of time.

## Question 3
- I experimented with:
  - Shell's Original Sequence, gap = n/2, n/4, ..., 1
  - Hibbard’s Sequence, 1, 3, 7, 15, 31, ...
  - Sedgewick’s Sequence, 1, 5, 19, 41, 109, ...
- I eventually settled on Sedgewick’s Sequence as it had a faster time complexity, by around 0.2ms
  - gap = 9 × (2^(2k)) - 9 × (2^k) + 1