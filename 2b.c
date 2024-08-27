// Preemptive Priority Scheduling

#include <stdio.h>
#include <limits.h>

typedef struct{
    int id, at, bt, rt, ct, tat, wt, start, priority;
} Process;

int findMinIndex(Process procs[], int n, int time){
    int minIndex = -1;
    int maxPriority = INT_MIN;

    for (int i = 0; i < n; i++){
        Process p = procs[i];
        if (p.at <= time && p.rt > 0 && p.priority > maxPriority){
            maxPriority = p.priority;
            minIndex = i;
        }
    }

    return minIndex;
}

void findTimes(Process procs[], int n){
    int time = 0;
    int completed = 0;

    printf("Gantt Chart:\n");

    while (completed < n){
        int curIndex = findMinIndex(procs, n, time);

        if (curIndex == -1){
            printf("Idle ");
            time++;
            continue;
        }

        Process *p = &procs[curIndex];

        if (p->rt == p->bt){
            p->start = time;
        }

        printf("P%d ", p->id);

        time++;
        p->rt--;

        if (p->rt == 0){
            p->ct = time;
            p->tat = p->ct - p->at;
            p->wt = p->tat - p->bt;

            completed++;
        }
    }
    printf("\n");
}

void printRes(Process procs[], int n){
    float tat = 0;
    float wt = 0;
    float response = 0;

    printf("ID\tAT\tBT\tPr\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++){
        Process p = procs[i];
        tat += p.tat;
        wt += p.wt;
        response += (p.start - p.at);

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p.id, p.at, p.bt, p.priority, p.ct, p.tat, p.wt, (p.start - p.at));
    }

    printf("Average Turnaround Time: %.2f\n", tat / n);
    printf("Average Waiting Time: %.2f\n", wt / n);
    printf("Average Response Time: %.2f\n", response / n);
}

void main(){
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process procs[n];

    for (int i = 0; i < n; i++){
        printf("Enter arrival time, burst time and priority: ");
        scanf("%d %d %d", &procs[i].at, &procs[i].bt, &procs[i].priority);

        procs[i].rt = procs[i].bt;
        procs[i].id = i + 1;
        procs[i].start = -1;
    }

    findTimes(procs, n);
    printRes(procs, n);
}
