Itay Shemesh
PA3, AVL Trees
Professor, Dr. Kandaswamy
Due, March 2nd

Questions:

- AVL Tree Performance: The `avl_map` implementation supports logarithmic insertion, deletion, and lookup operations due to the self-balancing nature of AVL trees. Rotations ensure that the tree remains balanced, maintaining a height of O(log n).

- Comparison with `std::map`: Both `avl_map` and `std::map` provide O(log n) lookup times. However, `std::map` may have slightly different performance characteristics due to its balancing strategy. In my benchmark, `avl_map` performed similar to `std::map`.

- Trade-offs: 
    - `avl_map` is better for lookup-heavy workloads due to its strict balancing.
    - `std::map` is better for dynamic workloads with frequent insertions and deletions due to its lower overhead.

Results: 

avl_map lookup time: 0.000289819 seconds
std::map lookup time: 0.000320349 seconds

avl_map lookup time: 0.000249042 seconds
std::map lookup time: 0.000247432 seconds

avl_map lookup time: 0.000238544 seconds
std::map lookup time: 0.0003111 seconds

avl_map lookup time: 0.000286366 seconds
std::map lookup time: 0.000383478 seconds

avl_map lookup time: 0.00038418 seconds
std::map lookup time: 0.000462901 seconds

It seems that overall avl_map is slightly better for this PA (on my computer) than std::map