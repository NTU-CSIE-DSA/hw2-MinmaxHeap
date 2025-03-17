#include <stdio.h>
#include <stdbool.h>
#define MAXN (1000000 + 5)

typedef struct Heap_prototype {
    int jobid, priority;
} Heap;

Heap heap[MAXN];
int level_prefix[MAXN], sz;

bool is_min_level(int n) {
    return level_prefix[n] == 0;
}

void swap(Heap* a, Heap* b) {
    if(a == b) return ;
    Heap tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_up_min(int n) {
    if(n <= 3) return ;
    int grand_parent = n / 4;
    if(heap[n].priority < heap[grand_parent].priority) {
        swap(&heap[n], &heap[grand_parent]);
        bubble_up_min(grand_parent);
    }
}

void bubble_up_max(int n) {
    if(n <= 3) return ;
    int grand_parent = n / 4;
    if(heap[n].priority > heap[grand_parent].priority) {
        swap(&heap[n], &heap[grand_parent]);
        bubble_up_max(grand_parent);
    }
}

void add(int jobid, int priority) {
    sz++;
    heap[sz].jobid = jobid;
    heap[sz].priority = priority;
    if(sz > 1) {
        int parent = sz / 2;
        if(is_min_level(sz)) {
            if(heap[sz].priority > heap[parent].priority) {
                swap(&heap[sz], &heap[parent]);
                bubble_up_max(parent);
            }
            else {
                bubble_up_min(sz);
            }
        }
        else {
            if(heap[sz].priority < heap[parent].priority) {
                swap(&heap[sz], &heap[parent]);
                bubble_up_min(parent);
            }
            else {
                bubble_up_max(sz);
            }
        }
    }
    printf("%d jobs waiting\n", sz);
}

void bubble_down_min(int n) {
    if(n * 2 > sz) return ;
    int candidate[6] = {n * 2, n * 2 + 1, n * 4, n * 4 + 1, n * 4 + 2, n * 4 + 3};
    int minindex = n;

    for(int i = 0; i < 6; i++) {
        if(candidate[i] > sz) break;
        if(heap[candidate[i]].priority < heap[minindex].priority) {
            minindex = candidate[i];
        }
    }

    if(minindex != n) {
        swap(&heap[n], &heap[minindex]);
        if(minindex >= n * 4) {
            int parent = minindex / 2;
            if(heap[parent].priority < heap[minindex].priority) {
                swap(&heap[parent], &heap[minindex]);
            }
            bubble_down_min(minindex);
        }
    }
}

void bubble_down_max(int n) {
    if(n * 2 > sz) return ;
    int candidate[6] = {n * 2, n * 2 + 1, n * 4, n * 4 + 1, n * 4 + 2, n * 4 + 3};
    int maxindex = n;

    for(int i = 0; i < 6; i++) {
        if(candidate[i] > sz) break;
        if(heap[candidate[i]].priority > heap[maxindex].priority) {
            maxindex = candidate[i];
        }
    }

    if(maxindex != n) {
        swap(&heap[n], &heap[maxindex]);
        if(maxindex >= n * 4) {
            int parent = maxindex / 2;
            if(heap[parent].priority > heap[maxindex].priority) {
                swap(&heap[parent], &heap[maxindex]);
            }
            bubble_down_max(maxindex);
        }
    }
}

void remove_smallest() {
    if(sz > 0) {
        printf("job %d with priority %d dropped\n", heap[1].jobid, heap[1].priority);
        swap(&heap[1], &heap[sz]);
        if(--sz > 0) bubble_down_min(1);
    }
    else {
        printf("no job in queue\n");
    }
}

void remove_biggest() {
    if(sz > 0) {
        int biggest;
        if(sz == 1) {
            biggest = 1;
        }
        else if(sz == 2) {
            biggest = 2;
        }
        else {
            biggest = heap[2].priority > heap[3].priority ? 2 : 3;
        }
        printf("job %d with priority %d completed\n", heap[biggest].jobid, heap[biggest].priority);
        swap(&heap[biggest], &heap[sz]);
        sz--;
        if(biggest <= sz) bubble_down_max(biggest);
    }
    else {
        printf("no job in queue\n");
    }
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1, k = 1, tp = 0; i <= n; i += k, k *= 2, tp ^= 1) {
        for(int j = 0; j < k && i + j <= n; j++) {
            level_prefix[i + j] = tp;
        }
    }
    

    for(int i = 0; i < n; i++) {
        int type;
        scanf("%d", &type);
        if(type == 1) {
            int jobid, priority;
            scanf("%d%d", &jobid, &priority);
            add(jobid, priority);
        }
        else if(type == 2) {
            remove_biggest();
        }
        else {
            remove_smallest();
        }
    }
}