#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id, at, bt, rt, ct, wt, tat, start_time;
} Process;

void roundRobin(Process proc[], int n, int quantum) {
    int time = 0, completed = 0;

    while (completed < n) {
        int all_done = 1;
        
        for (int i = 0; i < n; i++) {
            if (proc[i].rt > 0) {
                all_done = 0;
                if (proc[i].at <= time) {
                    if (proc[i].rt == proc[i].bt) {
                        proc[i].start_time = time; // Time when the process first starts execution
                    }
                    
                    if (proc[i].rt <= quantum) {
                        time += proc[i].rt;
                        proc[i].rt = 0;
                        proc[i].ct = time;
                        proc[i].tat = proc[i].ct - proc[i].at;
                        proc[i].wt = proc[i].tat - proc[i].bt;
                        completed++;
                    } else {
                        time += quantum;
                        proc[i].rt -= quantum;
                    }
                }
            }
        }
        
        if (all_done) {
            break;
        }
    }
}

void printResults(Process proc[], int n) {
    int total_wt = 0, total_tat = 0, total_rt = 0;

    printf("ID\tAT\tBT\tCT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        total_wt += proc[i].wt;
        total_tat += proc[i].tat;
        total_rt += (proc[i].start_time - proc[i].at);
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", proc[i].id, proc[i].at, proc[i].bt, proc[i].ct, proc[i].wt, proc[i].tat, (proc[i].start_time - proc[i].at));
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_tat / n);
    printf("Average Response Time: %.2f\n", (float)total_rt / n);
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process proc[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        proc[i].id = i + 1;
        scanf("%d %d", &proc[i].at, &proc[i].bt);
        proc[i].rt = proc[i].bt;
        proc[i].start_time = -1; // Initialize response time start
    }

    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    roundRobin(proc, n, quantum);
    printResults(proc, n);

    return 0;
}
