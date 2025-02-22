# Itay Shemesh
# PA2, Josephus Problem
# Professor Kandaswamy
# Due Feburay 17th

# Question 1: Does machine processing power affect execution time?
Yes, machine processing power does affect execution time. A more powerful machine with a faster CPU and more cores can perform calculations more quickly, reducing the execution time of the program. However it also depends on how easy the process is to run, for instance if a super computer with 1000 cores wanted to run a simple program it would need to first organize all the tasks to all the cores it has, which takes time. While a normal computer with 10 cores would probably finish the program in less time due to not needing to sync up all the cores (for long).

# Question 2: Which performs better: std::list or std::vector? Under what conditions?
std::vector performs better when you need random access to elements
std::list performs better when frequent insertions and deletions are needed in the middle of the container, as these operations are done in constant time

# Question 3:
As N increases the runtime increases linearly because more people need to be processed in the elimination cycle. Larger N means more iterations of the elimination process, so execution time increases.
As M increases it will reduce the number of elimination cycles, since people will be skipped over in larger steps. However, a larger M still requires the algorithm to manage the elimination process efficiently.
