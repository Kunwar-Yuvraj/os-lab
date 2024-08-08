#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id, at, bt, rt, ct, wt, tat, rt_start;
} Process;

void findTimes(Process proc[], int n) {
    int time = 0, completed = 0, min_index;
    int min_rt;

    while (completed < n) {
        min_rt = __INT_MAX__;
        min_index = -1;

        for (int i = 0; i < n; i++) {
            if (proc[i].at <= time && proc[i].rt < min_rt && proc[i].rt > 0) {
                min_rt = proc[i].rt;
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++;
            continue;
        }

        if (proc[min_index].rt == proc[min_index].bt) {
            proc[min_index].rt_start = time;
        }

        proc[min_index].rt--;
        time++;

        if (proc[min_index].rt == 0) {
            proc[min_index].ct = time;
            proc[min_index].tat = proc[min_index].ct - proc[min_index].at;
            proc[min_index].wt = proc[min_index].tat - proc[min_index].bt;
            completed++;
        }
    }
}

void printResults(Process proc[], int n) {
    int total_wt = 0, total_tat = 0, total_rt = 0;

    printf("ID\tAT\tBT\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        total_rt += (proc[i].rt_start - proc[i].at);
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].at, proc[i].bt, proc[i].ct, proc[i].wt, proc[i].tat, (proc[i].rt_start - proc[i].at));
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        proc[i].id = i + 1;
        scanf("%d %d", &proc[i].at, &proc[i].bt);
        proc[i].rt = proc[i].bt;
        proc[i].rt_start = -1; // Initialize response time start
    }

    findTimes(proc, n);
    printResults(proc, n);

    return 0;
}
