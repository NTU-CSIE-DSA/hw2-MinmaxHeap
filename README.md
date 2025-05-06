# Solution

## Introduction

This problem asked to implement a double-ended priority queue using a min-max heap in C. It supports:
- Inserting jobs with an integer ID and priority.
- Deleting the job with the highest priority (`deleteMax`).
- Deleting the job with the lowest priority (`deleteMin`).

## Min-max Heap
A min-max heap is a double-ended priority queue which has the following properties:
- A complete binary tree containing alternating max and min levels. 
- The root has the minimum key among all keys in the tree. 
- If a node $x$ is on a min level, then $x.key$ is the minimum key among all keys in the subtree with root $x$. 
- If a node $x$ is on a max level, then $x.key$ is the maximum key among all keys in the subtree with root $x$. 
- Efficient job insertion: $O(\log n)$
- Efficient min and max deletion: $O(\log n)$

## File Structure

```
public/
├── correct.c           # Main solution 
├── mle.c               # Correct solution but using exceeding memory 
├── subtask1.c          # Solution solves subtask 1 
└── subtask2.c          # Solution solves subtask 2 
```

## Common Mistakes 
1. Off-by-One Error
    * This may occur when calculating the minimum level, calculating the index of the (grand)parent/children. 
2. Edge Case
    * The job with the highest priority in the heap should be countered carefully when there is only 1 or 2 jobs. 
3. Miss Comparing When Heapifying
    * When swapped with grandchild, it should compare with its original child (new parent) if the min-max heap properties are not violated. 
