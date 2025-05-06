#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*
 * This implementation uses a single max heap taught
 * in the lecture to store jobs and their priorities.
 * It handles insertion of jobs and deletion of the job with the highest priority, 
 * and deletion of the job with the lowest priority by sequential searching the heap. 
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

void BubbleUp(int idx){
    while (idx > 0){
        int parent = (idx - 1) / 2;
        if (heap[parent].priority < heap[idx].priority){
            swap(&heap[parent], &heap[idx]);
            idx = parent;
        }
        else {
            break;
        }
    }
}

void heapify(int idx){
    while (idx < size){
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        int largest = idx;

        if (left < size && heap[left].priority > heap[largest].priority){
            largest = left;
        }
        if (right < size && heap[right].priority > heap[largest].priority){
            largest = right;
        }

        if (largest != idx){
            swap(&heap[largest], &heap[idx]);
            idx = largest;
        }
        else {
            break;
        }
    }
}

int FindMin(){
    int minIdx = 0;
    for (int i=1; i<size; i++){
        if (heap[i].priority < heap[minIdx].priority){
            minIdx = i;
        }
    }
    return minIdx;
}

int main(){
    int N;
    scanf("%d", &N);
    
    int type, job_id, priority;
    for (int i=0; i<N; i++){
        scanf("%d", &type);
        if (type == 1){
            scanf("%d %d", &job_id, &priority);
            heap[size].job_id = job_id;
            heap[size].priority = priority;
            size++;
            BubbleUp(size - 1);
            printf("%d jobs waiting\n", size);
        }
        else if (type == 2){
            if (size == 0){
                printf("no job in queue\n");
                continue;
            }
            printf("job %d with priority %d completed\n", heap[0].job_id, heap[0].priority);
            heap[0] = heap[--size];
            heapify(0);
        }
        else {
            if (size == 0){
                printf("no job in queue\n");
                continue;
            }
            int minIdx = FindMin();
            printf("job %d with priority %d dropped\n", heap[minIdx].job_id, heap[minIdx].priority);
            heap[minIdx] = heap[--size];
            while (minIdx > 0){
                int parent = (minIdx - 1) / 2;
                if (heap[parent].priority < heap[minIdx].priority){
                    swap(&heap[parent], &heap[minIdx]);
                    minIdx = parent;
                }
                else {
                    break;
                }
            }
            heapify(minIdx);
        }
    }

    return 0;
}