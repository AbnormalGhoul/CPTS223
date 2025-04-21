# Amazon Inventory REPL
- CPTS223, PA5, Itay Shemesh

## Question 1
- Insertion sort is simple and works well for small data sets, even more so when the data is nearly sorted.
- Merge sort is significantly faster for larger datasets due to its O(n log n) performance in all cases, but it uses more memory.
- In this PA merge sort is slightly faster by around 30 microsecounds on average.

## Question 2
### Supported Commands
- `find <inventoryid>`: Print full product details for a given inventory ID.
- `listInventory <category>`: Lists inventory items in a category, sorted by selling price (ascending, default).
- `listInventory <category> desc`: Lists inventory sorted by selling price (descending) using **insertion sort**.
- `listInventory <category> merge`: Lists inventory sorted (ascending) using **merge sort**.
- `listInventory <category> merge desc`: Lists inventory sorted (descending) using **merge sort**.

### Observations
- Insertion sort performs better on smaller or nearly sorted lists.
- Merge sort is better suited for large datasets.
- Both algorithms were tested with ascending and descending comparators.
- The better searching algorithm for this PA (Time wise) is merge sort.

## Assumptions & Notes
- Missing categories are labeled "NA".
- Products with missing or malformed prices are treated as $0.00.
- CSV parsing accounts for quoted strings with embedded commas.