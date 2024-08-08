#include <stdio.h>
#include <limits.h>

#define MAX 10

typedef struct {
    int id, arr, burst, prio, rem, fin, tat, wt;
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
        p[i].rem = p[i].burst;
    }

    sched(p, n);
    print(p, n);

    return 0;
}

void sched(P p[], int n) {
    int t = 0, c = 0, i;
    while (c < n) {
        P *cur = NULL;
        int hp = -1;

        for (i = 0; i < n; i++) {
            if (p[i].arr <= t && p[i].rem > 0) {
                if (p[i].prio > hp) {
                    hp = p[i].prio;
                    cur = &p[i];
                }
            }
        }

        if (cur) {
            cur->rem--;
            if (cur->rem == 0) {
                cur->fin = t + 1;
                cur->tat = cur->fin - cur->arr;
                cur->wt = cur->tat - cur->burst;
                c++;
            }
        }
        t++;
    }
}

void print(P p[], int n) {
    int i;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("ID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        avg_rt += p[i].tat - p[i].burst; // Response time = Turnaround time - Burst time
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].id, p[i].arr, p[i].burst, p[i].prio, p[i].fin, p[i].tat, p[i].wt);
    }

    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_rt);
}
