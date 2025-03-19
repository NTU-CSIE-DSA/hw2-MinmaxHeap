#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAXSZ 1000000

typedef struct job {
    int job_id;
    int priority;
} Job;

void swap(Job *a, Job *b){
    Job temp = *a;
    *a = *b;
    *b = temp;
}

int isMinLevel(int idx){
    idx++;
    int level = 0;
    while (idx > 0){
        idx >>= 1;
        level++;
    }
    return level % 2;
}

void heapify(Job **heap, int m, int size){
    while (2 * m + 1 < size){
        int i = m;
        if (isMinLevel(i)){
            int minIdx = -1, minPrio = 2147483647;
            int idxArr[6] = {2 * i + 1, 2 * i + 2, 4 * i + 3, 4 * i + 4, 4 * i + 5, 4 * i + 6};
            for (int j=0; j<6; j++){
                if (idxArr[j] < size && heap[idxArr[j]] -> priority < minPrio){
                    minPrio = heap[idxArr[j]] -> priority;
                    minIdx = idxArr[j];
                }
            }
            m = minIdx;

            if (heap[m] -> priority < heap[i] -> priority){
                swap(heap[m], heap[i]);
                if (m >= 4 * i + 3){
                    if (heap[m] -> priority > heap[(m - 1) / 2] -> priority){
                        swap(heap[m], heap[(m - 1) / 2]);
                    }
                }
                else break;
            }
            else break;
        }
        else {
            int maxIdx = -1, maxPrio = -2147483648;
            int idxArr[6] = {2 * i + 1, 2 * i + 2, 4 * i + 3, 4 * i + 4, 4 * i + 5, 4 * i + 6};
            for (int j=0; j<6; j++){
                if (idxArr[j] < size && heap[idxArr[j]] -> priority > maxPrio){
                    maxPrio = heap[idxArr[j]] -> priority;
                    maxIdx = idxArr[j];
                }
            }
            m = maxIdx;

            if (heap[m] -> priority > heap[i] -> priority){
                swap(heap[m], heap[i]);
                if (m >= 4 * i + 3){
                    if (heap[m] -> priority < heap[(m - 1) / 2] -> priority){
                        swap(heap[m], heap[(m - 1) / 2]);
                    }
                }
                else break;
            }
            else break;
        }
    }
}

void BubbleMax(Job **heap, int idx){
    int grandparentIdx = (idx - 3) / 4;
    while (idx > 2 && heap[idx] -> priority > heap[grandparentIdx] -> priority){
        swap(heap[idx], heap[grandparentIdx]);
        idx = grandparentIdx;
        grandparentIdx = (idx - 3) / 4;
    }
}

void BubbleMin(Job **heap, int idx){
    int grandparentIdx = (idx - 3) / 4;
    while (idx > 2 && heap[idx] -> priority < heap[grandparentIdx] -> priority){
        swap(heap[idx], heap[grandparentIdx]);
        idx = grandparentIdx;
        grandparentIdx = (idx - 3) / 4;
    }
}

void BubbleUp(Job **heap, int idx){
    if (idx > 0){
        int parentIdx = (idx - 1) / 2;
        if (isMinLevel(idx)){
            if (heap[idx] -> priority > heap[parentIdx] -> priority){
                swap(heap[idx], heap[parentIdx]);
                BubbleMax(heap, parentIdx);
            }
            else {
                BubbleMin(heap, idx);
            }
        }
        else {
            if (heap[idx] -> priority < heap[parentIdx] -> priority){
                swap(heap[idx], heap[parentIdx]);
                BubbleMin(heap, parentIdx);
            }
            else {
                BubbleMax(heap, idx);
            }
        }
    }
}

int FindMin(int size){
    return (size > 0)? 0: -1;
}

int FindMax(Job **heap, int size){
    if (size == 0) return -1;
    if (size < 3) return (size - 1);
    return (heap[1] -> priority > heap[2] -> priority)? 1: 2;
}

int main(){
    int N;
    scanf("%d", &N);

    Job **heap = (Job **) malloc(MAXSZ * sizeof(Job *));
    
    int size = 0;
    int type, job_id, priority;
    for (int i=0; i<N; i++){
        scanf("%d", &type);
        if (type == 1){
            scanf("%d %d", &job_id, &priority);
            Job *newJob = (Job *) malloc(sizeof(Job));
            newJob -> job_id = job_id;
            newJob -> priority = priority;

            heap[size++] = newJob;
            BubbleUp(heap, size - 1);
            printf("%d jobs waiting\n", size);
        }
        else if (type == 2){
            int maxIdx = FindMax(heap, size);
            if (maxIdx == -1){
                printf("no job in queue\n");
                continue;
            }
            printf("job %d with priority %d completed\n", heap[maxIdx] -> job_id, heap[maxIdx] -> priority);
            heap[maxIdx] = heap[--size];
            heapify(heap, maxIdx, size);
        }
        else {
            int minIdx = FindMin(size);
            if (minIdx == -1){
                printf("no job in queue\n");
                continue;
            }
            printf("job %d with priority %d dropped\n", heap[minIdx] -> job_id, heap[minIdx] -> priority);
            heap[minIdx] = heap[--size];
            heapify(heap, minIdx, size);
        }
    }

    return 0;
}