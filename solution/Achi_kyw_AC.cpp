#include <stdio.h>
#include <stdlib.h>

typedef struct job {
    int job_id;
    int priority;
} Job;

#define is_min_level(x) (__builtin_clz(x) & 1)

Job heap[1000005];

int sz;

void swap(Job *a, Job *b){
    Job temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_up_(int id, int is_max){// 1 for max, -1 for min
    if(id<=3) return;
    int grand_par = (id >> 2);
    if(heap[id].priority*is_max > heap[grand_par].priority*is_max){
        swap(&heap[id], &heap[grand_par]);
        bubble_up_(grand_par, is_max);
    }
}

void bubble_up(int id){
    if(sz>1){
        int par_id = (sz >> 1);
        if(is_min_level(sz)){
            if(heap[sz].priority > heap[par_id].priority){
                swap(&heap[sz], &heap[par_id]);
                bubble_up_(par_id,1);
            }
            else {
                bubble_up_(sz,-1);
            }
        }
        else {
            if(heap[sz].priority < heap[par_id].priority){
                swap(&heap[sz], &heap[par_id]);
                bubble_up_(par_id,-1);
            }
            else {
                bubble_up_(sz,1);
            }
        }
    }
}
void bubble_down(int id, int is_max){// 1 for max, -1 for min
    if ((id << 1) > sz) return;
    int t_id = id;
    int candidate[6] = {(id << 1), (id << 1) + 1, (id << 2), (id << 2) + 1, (id << 2) + 2, (id << 2) + 3};
    for (int i = 0; i < 6; i++){
        if (candidate[i] > sz) break;
        if (heap[candidate[i]].priority*is_max > heap[t_id].priority*is_max){
            t_id = candidate[i];
        }
    }
    if(t_id == id) return;
    swap(&heap[id], &heap[t_id]);
    if(t_id >= (id << 2)){
        if(heap[(t_id) >> 1].priority*is_max > heap[t_id].priority*is_max){
            swap(&heap[t_id], &heap[(t_id) >> 1]);
        }
        bubble_down(t_id, is_max);
    }
}

void remove_biggest(){
    int biggest_id;
    if(sz>0){
        if(sz<3) biggest_id=sz;
        else biggest_id = (heap[2].priority > heap[3].priority)? 2: 3;
        printf("job %d with priority %d completed\n", heap[biggest_id].job_id, heap[biggest_id].priority);
        swap(&heap[biggest_id], &heap[sz]);
        sz--;
        if(biggest_id <= sz) bubble_down(biggest_id, 1);
    }
    else printf("no job in queue\n");
}

void remove_smallest(){
    if(sz>0){
        printf("job %d with priority %d dropped\n", heap[1].job_id, heap[1].priority);
        swap(&heap[1], &heap[sz]);
        if(--sz > 0) bubble_down(1, -1);
    }
    else printf("no job in queue\n");
}


int main() {
    int n;
    scanf("%d", &n);
    while(n--){
        int type;
        scanf("%d", &type);
        if(type==1){
            int job_id, priority;
            scanf("%d %d", &job_id, &priority);
            sz++;
            heap[sz].job_id = job_id;
            heap[sz].priority = priority;
            bubble_up(sz);
            printf("%d jobs waiting\n", sz);
        }
        else if(type==2){
            remove_biggest();
        }
        else if(type==3){
            remove_smallest();
        }
        else {
            return -1;
        }
    }
}