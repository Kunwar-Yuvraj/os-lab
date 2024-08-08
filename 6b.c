#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id, at, bt, ct, wt, tat;
} Process;

void sjfNonPreemptive(Process proc[], int n) {
    int completed = 0, time = 0;
    Process temp;

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].at > proc[j].at) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    while (completed < n) {
        int idx = -1, min_bt = 1e9;
        // Find the process with the shortest burst time that has arrived
        for (int i = 0; i < n; i++) {
            if (proc[i].at <= time && proc[i].bt < min_bt && proc[i].bt > 0) {
                min_bt = proc[i].bt;
                idx = i;
            }
        }
        
        if (idx != -1) {
            time += proc[idx].bt;
            proc[idx].ct = time;
            proc[idx].tat = proc[idx].ct - proc[idx].at;
            proc[idx].wt = proc[idx].tat - proc[idx].bt;
            proc[idx].bt = 0;
            completed++;
        } else {
            time++;
        }
    }
}

void printResults(Process proc[], int n) {
    int total_wt = 0, total_tat = 0;

    printf("ID\tAT\tBT\tCT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].at, proc[i].bt, proc[i].ct, proc[i].wt, proc[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
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
        proc[i].bt = proc[i].bt; // Initialize burst time
    }

    sjfNonPreemptive(proc, n);
    printResults(proc, n);

    return 0;
}
