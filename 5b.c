#include <stdio.h>

#define MAX 10

typedef struct {
    int id, arr, burst, fin, tat, wt, rt, start;
} Process;

void fcfs(Process p[], int n);
void print(Process p[], int n);

int main() {
    int n, i;
    Process p[MAX];

    printf("Number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("P%d arrival and burst time: ", i + 1);
        scanf("%d %d", &p[i].arr, &p[i].burst);
    }

    fcfs(p, n);
    print(p, n);

    return 0;
}

void fcfs(Process p[], int n) {
    int i;
    int t = 0; // Current time

    for (i = 0; i < n; i++) {
        if (p[i].arr > t) {
            t = p[i].arr; // If the process arrives after the current time, set current time to arrival
        }
        p[i].start = t;
        p[i].fin = t + p[i].burst;
        p[i].tat = p[i].fin - p[i].arr;
        p[i].wt = p[i].tat - p[i].burst;
        p[i].rt = p[i].start - p[i].arr; // Response time is start time - arrival time
        t += p[i].burst; // Move time forward by burst time
    }
}

void print(Process p[], int n) {
    int i;
    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("ID\tArrival\tBurst\tStart\tCompletion\tTurnaround\tWaiting\tResponse\n");
    for (i = 0; i < n; i++) {
        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
        avg_rt += p[i].rt;
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\t\t%d\t%d\n", p[i].id, p[i].arr, p[i].burst, p[i].start, p[i].fin, p[i].tat, p[i].wt, p[i].rt);
    }

    avg_wt /= n;
    avg_tat /= n;
    avg_rt /= n;

    printf("\nAverage Waiting Time: %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
    printf("Average Response Time: %.2f\n", avg_rt);
}
