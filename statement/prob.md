## Problem Description

**The description on [NTU COOL]() shall be considered the official one. This version is provided for reference only.**

In this problem, we ask you to design a system to emulate Tien's todo list, currently containing thousands of jobs :-(. This system needs to support the following three operations:
* **Add** Operation: Insert a job into the todo list with some given priority.
* **Complete** Operation: Remove the job with the highest priority, which will then be attended by Tien.
* **Drop** Operation: Remove the job with the lowest priority, which will then be ignored and dropped after Tien drinks a few bottles of beer.

The max-heap data structure, as covered in class, efficiently supports Insert and RemoveMax operations but does not handle RemoveMin efficiently. Similarly, a min-heap supports Insert and RemoveMin but struggles with RemoveMax. While it is possible to construct both a max-heap and a min-heap with some cross-link mechanism to support all these operations efficiently, such an approach is complex to implement and requires additional space.

To design the system efficiently, we suggest you to learn related data structures that can handle both RemoveMax and RemoveMin operations efficiently. One possibility is the min-max heap. The following description of the min-max heap is modified from [Wikipedia](https://en.wikipedia.org/wiki/Min-max_heap): 

*The min-max heap property is: each node at an even level in the tree is less than all of its descendants, while each node at an odd level in the tree is greater than all of its descendants.*
The pseudo code on Wikipedia appears pretty clear, and hence we do not list them here. In this problem, we suggest you implement the min-max heap to conquer the tasks.


## Input

Assuming that Tien's job queue is initially empty, the input begins with an integer $N$, representing the total number of operations. Each of the next $N$ lines is given in one of the following formats:

* $\texttt{1 job_id priority}$: add operation
Insert a job with $\texttt{job_id}$ into the job queue, assigning it the priority $\texttt{priority}$.

* $\texttt{2}$: complete operation
Complete the job with the highest priority, and remove it from the job queue.

* $\texttt{3}$: drop operation
Drop the job with the lowest priority, and remove it from the job queue.


## Output

* For each $\textbf{add}$ operation, print a line that indicates the number of jobs in the job queue with the format: 

    $\texttt{[num_of_jobs] jobs waiting}$

* For each $\textbf{complete}$ operation, if there is a job to be completed, print a line of 

    $\texttt{[job_id] with [priority] completed}$
    
    Otherwise (the queue is empty), print a line of

    $\texttt{no job in queue}$


* For each $\textbf{drop}$ operation, if there is a job to be dropped, print a line of 

    $\texttt{[job_id] with [priority] dropped}$

    Otherwise (the queue is empty), print a line of

    $\texttt{no job in queue}$


## Constraints
* $1 \leq N \leq 10^6$
* $1 \leq \texttt{job_id}, \texttt{priority} \leq 10^9$
* It is guaranteed that all $\texttt{priority}$ and $\texttt{job_id}$ values will be distinct at any given time. 
* All operations will be valid, ensuring that all IDs remain within the specified range.


## Subtasks

### Subtask 1 (20 pts)

* only $\textbf{add}$ and $\textbf{complete}$ operations are implemented. 

### Subtask 2 (20 pts)

* $1 \leq N \leq 10^5$
* all operations are implemented
* $0 \leq$ $\textbf{drop}$ operations $\leq 10^4$

### Subtask 3 (60 pts)

* no other constraints


## Sample Testcases

### Sample Input 1
```
7
1 1 1126
1 2 314
1 3 520
2
2
2
2
```
### Sample Output 1
```
1 jobs waiting
2 jobs waiting
3 jobs waiting
job 1 with priority 1126 completed
job 3 with priority 520 completed
job 2 with priority 314 completed
no job in queue
```

### Sample Input 2
```
15
1 1 1126
2
3
1 2 10
1 3 11
1 4 8
1 5 12
1 6 1
1 7 13
3
1 8 3
1 9 2
1 10 7
3
2
```

### Sample Output 2
```
1 jobs waiting
job 1 with priority 1126 completed
no job in queue
1 jobs waiting
2 jobs waiting
3 jobs waiting
4 jobs waiting
5 jobs waiting
6 jobs waiting
job 6 with priority 1 dropped
6 jobs waiting
7 jobs waiting
8 jobs waiting
job 9 with priority 2 dropped
job 7 with priority 13 completed
```