#include <stdio.h>
#define MAXN (1000000 + 5)

typedef struct Heap_prototype {
    int jobid, priority, id;
} Heap;

void swap(Heap* a, Heap* b) {
    if(a == b) return ;
    Heap tmp = *a;
    *a = *b;
    *b = tmp;
}

Heap maxheap[MAXN], minheap[MAXN];
int used[MAXN];
int maxheapsz, minheapsz, sz;

void maxheap_add(int jobid, int priority, int id) {
    maxheap[maxheapsz].jobid = jobid;
    maxheap[maxheapsz].priority = priority;
    maxheap[maxheapsz].id = id;
    int idx = maxheapsz;
    while(idx > 1) {
        int parent = idx / 2;
        if(maxheap[parent].priority < maxheap[idx].priority) {
            swap(&maxheap[parent], &maxheap[idx]);
            idx = parent;
        }
        else break;
    }
}

void minheap_add(int jobid, int priority, int id) {
    minheap[minheapsz].jobid = jobid;
    minheap[minheapsz].priority = priority;
    minheap[minheapsz].id = id;
    int idx = minheapsz;
    while(idx > 1) {
        int parent = idx / 2;
        if(minheap[parent].priority > minheap[idx].priority) {
            swap(&minheap[parent], &minheap[idx]);
            idx = parent;
        }
        else break;
    }
}

void add(int jobid, int priority, int id) {
    maxheapsz++, minheapsz++;
    maxheap_add(jobid, priority, id);
    minheap_add(jobid, priority, id);
    printf("%d jobs waiting\n", sz);
}

void remove_biggest() {
    if(maxheapsz == 0) {
        printf("no job in queue\n");
        sz++;
        return ;
    }

    Heap tmp = maxheap[1];
    swap(&maxheap[1], &maxheap[maxheapsz]);
    maxheapsz--;
    int idx = 1;
    while(idx * 2 <= maxheapsz) {
        int maxindex = idx;
        if(maxheap[maxindex].priority < maxheap[idx * 2].priority) maxindex = idx * 2;
        if(idx * 2 + 1 <= maxheapsz && maxheap[maxindex].priority < maxheap[idx * 2 + 1].priority) maxindex = idx * 2 + 1;
        if(maxindex == idx) break;
        swap(&maxheap[idx], &maxheap[maxindex]);
        idx = maxindex;
    }
    if(used[tmp.id] == 0) {
        printf("job %d with priority %d completed\n", tmp.jobid, tmp.priority);
        used[tmp.id] = 1;
    }
    else {
        remove_biggest();
    }
}

void remove_lowest() {
    if(minheapsz == 0) {
        printf("no job in queue\n");
        sz++;
        return ;
    }
    
    Heap tmp = minheap[1];
    swap(&minheap[1], &minheap[minheapsz]);
    minheapsz--;
    int idx = 1;
    while(idx * 2 <= minheapsz) {
        int minindex = idx;
        if(minheap[minindex].priority > minheap[idx * 2].priority) minindex = idx * 2;
        if(idx * 2 + 1 <= minheapsz && minheap[minindex].priority > minheap[idx * 2 + 1].priority) minindex = idx * 2 + 1;
        if(minindex == idx) break;
        swap(&minheap[idx], &minheap[minindex]);
        idx = minindex;
    }

    if(used[tmp.id] == 0) {
        printf("job %d with priority %d dropped\n", tmp.jobid, tmp.priority);
        used[tmp.id] = 1;
    }
    else {
        remove_lowest();
    }

}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int type;
        scanf("%d", &type);
        if(type == 1) {
            int jobid, priority;
            scanf("%d%d", &jobid, &priority);
            sz++;
            add(jobid, priority, i);
        }
        else if(type == 2) {
            remove_biggest();
            sz--;
        }
        else {
            remove_lowest();
            sz--;
        }
    }
}