#include <stdio.h>

#define MAX 10

typedef struct {
    int id, arr, burst, prio, fin, tat, wt, rt, start;
} P;

void sched(P p[], int n);
void print(P p[], int n);

int main() {
    int n, i;
    P p[MAX];

    printf("Processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d arrival, burst, priority: ", i + 1);
        scanf("%d %d %d", &p[i].arr, &p[i].burst, &p[i].prio);
    }

    sched(p, n);
    print(p, n);

    return 0;
}

void sched(P p[], int n) {
    int i, j, t = 0, c = 0;
    int completed[MAX] = {0}; // Track completed processes

    while (c < n) {
        int idx = -1;
        int hp = -1;

        // Find the process with highest priority that has arrived
        for (i = 0; i < n; i++) {
            if (p[i].arr <= t && !completed[i]) {
                if (p[i].prio > hp) {
                    hp = p[i].prio;
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            p[idx].start = t;
            t += p[idx].burst;
            p[idx].fin = t;
            p[idx].tat = p[idx].fin - p[idx].arr;
            p[idx].wt = p[idx].tat - p[idx].burst;
            p[idx].rt = p[idx].start - p[idx].arr;
            completed[idx] = 1;
            c++;
        } else {
            t++; // Increment time if no process is ready
        }
    }
}

void print(P p[], int n) {
    int i;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("ID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\tResponse\n");
    for (i = 0; i < n; i++) {
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        avg_rt += p[i].rt;
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\t%d\n", p[i].id, p[i].arr, p[i].burst, p[i].prio, p[i].fin, p[i].tat, p[i].wt, p[i].rt);
    }

    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_rt);
}
