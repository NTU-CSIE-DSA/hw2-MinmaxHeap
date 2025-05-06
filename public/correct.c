#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * Maintaining one min heap and one max heap doesn't fulfill the memory constraint. 
 * In each node of each heap, it is necessary to store job and priority.
 * There are at most 10^6 jobs, so this implementation uses at least 4B * 2 * 2 * 10^6 = 16MB. 
 * In addition, memory to maintain the connection between the heaps is not counted yet.
 * So this implementation is not feasible.
 */

#define MAXSZ 1000000

typedef struct job {
    int job_id;
    int priority;
} Job;

Job heap[MAXSZ];
int size = 0;

void swap(Job *a, Job *b){
    Job temp = *a;
    *a = *b;
    *b = temp;
}

int isMinLevel(int idx){    // Time complexity: O(log |idx|)
    idx++;
    int level = 0;
    while (idx > 0){
        idx >>= 1;
        level++;
    }
    return level % 2;
}

void heapify(int m){        // Time complexity: O(log(size))
    while (2 * m + 1 < size){   // O(log(size))
        int i = m;
        if (isMinLevel(i)){
            int minIdx = -1, minPrio = 2147483647;
            // Find the minimum among the children and grandchildren
            int idxArr[6] = {2 * i + 1, 2 * i + 2, 4 * i + 3, 4 * i + 4, 4 * i + 5, 4 * i + 6};
            for (int j=0; j<6; j++){
                if (idxArr[j] < size && heap[idxArr[j]].priority < minPrio){
                    minPrio = heap[idxArr[j]].priority;
                    minIdx = idxArr[j];
                }
            }
            m = minIdx;

            if (heap[m].priority < heap[i].priority){
                swap(&heap[m], &heap[i]);
                if (m >= 4 * i + 3){
                    // Is grandchild
                    if (heap[m].priority > heap[(m - 1) / 2].priority){
                        swap(&heap[m], &heap[(m - 1) / 2]);
                    }
                }
                else break;
            }
            else break;
        }
        else {
            int maxIdx = -1, maxPrio = -2147483648;
            // Find the maximum among the children and grandchildren
            int idxArr[6] = {2 * i + 1, 2 * i + 2, 4 * i + 3, 4 * i + 4, 4 * i + 5, 4 * i + 6};
            for (int j=0; j<6; j++){
                if (idxArr[j] < size && heap[idxArr[j]].priority > maxPrio){
                    maxPrio = heap[idxArr[j]].priority;
                    maxIdx = idxArr[j];
                }
            }
            m = maxIdx;

            if (heap[m].priority > heap[i].priority){
                swap(&heap[m], &heap[i]);
                if (m >= 4 * i + 3){
                    // Is grandchild
                    if (heap[m].priority < heap[(m - 1) / 2].priority){
                        swap(&heap[m], &heap[(m - 1) / 2]);
                    }
                }
                else break;
            }
            else break;
        }
    }
}

void BubbleMax(int idx){    // Time complexity: O(log(size))
    int grandparentIdx = (idx - 3) / 4;
    while (idx > 2 && heap[idx].priority > heap[grandparentIdx].priority){
        swap(&heap[idx], &heap[grandparentIdx]);
        idx = grandparentIdx;
        grandparentIdx = (idx - 3) / 4;
    }
}

void BubbleMin(int idx){    // Time complexity: O(log(size))
    int grandparentIdx = (idx - 3) / 4;
    while (idx > 2 && heap[idx].priority < heap[grandparentIdx].priority){
        swap(&heap[idx], &heap[grandparentIdx]);
        idx = grandparentIdx;
        grandparentIdx = (idx - 3) / 4;
    }
}

void BubbleUp(int idx){     // Time complexity: O(log(size))
    if (idx > 0){
        int parentIdx = (idx - 1) / 2;
        if (isMinLevel(idx)){
            if (heap[idx].priority > heap[parentIdx].priority){
                swap(&heap[idx], &heap[parentIdx]);
                BubbleMax(parentIdx);   // O(log(size))
            }
            else {
                BubbleMin(idx);         // O(log(size))
            }
        }
        else {
            if (heap[idx].priority < heap[parentIdx].priority){
                swap(&heap[idx], &heap[parentIdx]);
                BubbleMin(parentIdx);   // O(log(size))
            }
            else {
                BubbleMax(idx);         // O(log(size))
            }
        }
    }
}

int FindMin(){              // Time complexity: O(1)
    return (size > 0)? 0: -1;
}

int FindMax(){              // Time complexity: O(1)
    if (size == 0) return -1;
    if (size < 3) return (size - 1);
    return (heap[1].priority > heap[2].priority)? 1: 2;
}

int main(){
    int N;
    scanf("%d", &N);
    
    int type, job_id, priority;
    for (int i=0; i<N; i++){
        scanf("%d", &type);
        if (type == 1){             // Time complexity of insertion: O(log(size))
            scanf("%d %d", &job_id, &priority);
            heap[size].job_id = job_id;
            heap[size].priority = priority;
            size++;
            
            BubbleUp(size - 1);     // O(log(size))
            printf("%d jobs waiting\n", size);
        }
        else if (type == 2){        // Time complexity of deleteMax: O(log(size))
            int maxIdx = FindMax(); // O(1)
            if (maxIdx == -1){
                printf("no job in queue\n");
                continue;
            }
            printf("job %d with priority %d completed\n", heap[maxIdx].job_id, heap[maxIdx].priority);
            heap[maxIdx] = heap[--size];
            heapify(maxIdx);        // O(log(size))
        }
        else {                      // Time complexity of deleteMin: O(log(size))
            int minIdx = FindMin(); // O(1)
            if (minIdx == -1){
                printf("no job in queue\n");
                continue;
            }
            printf("job %d with priority %d dropped\n", heap[minIdx].job_id, heap[minIdx].priority);
            heap[minIdx] = heap[--size];
            heapify(minIdx);        // O(log(size))
        }
    }

    return 0;
}