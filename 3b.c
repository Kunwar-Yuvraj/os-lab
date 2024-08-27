#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;         // Process ID
    int at;         // Arrival Time
    int bt;         // Burst Time
    int rt;         // Remaining Time
    int ct;         // Completion Time
    int tat;        // Turnaround Time
    int wt;         // Waiting Time
    int firstStart; // First Start Time for Response Time Calculation
} Process;

// Function to sort processes by arrival time
void sortByArrival(int n, Process p[]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Function to calculate times and generate Gantt Chart for Round-Robin Scheduling
void findTimes(Process procs[], int n, int quantum) {
    int time = 0, completed = 0;
    int front = 0, rear = 0, queueSize = 0;
    int *queue = (int *)malloc(n * sizeof(int));
    int allArrived = 0;

    // Enqueue processes that have arrived
    for (int i = 0; i < n; i++) {
        if (procs[i].at <= time) {
            queue[rear++] = i;
            queueSize++;
        }
    }

    printf("Gantt Chart:\n");
    printf("|");

    while (completed < n) {
        if (queueSize == 0) {
            printf(" Idle ");
            time++;
            allArrived = 0;
            // Check for newly arrived processes
            for (int i = 0; i < n; i++) {
                if (procs[i].at <= time && procs[i].rt > 0) {
                    queue[rear++] = i;
                    queueSize++;
                }
            }
            continue;
        }

        int curIndex = queue[front++];
        queueSize--;

        Process *p = &procs[curIndex];
        if (p->rt == p->bt) {
            p->firstStart = time;
        }

        int slice = (p->rt < quantum) ? p->rt : quantum;
        int endTime = time + slice;

        printf("P%d(%d) %d| ", p->id, slice, endTime);

        time = endTime;
        p->rt -= slice;

        if (p->rt == 0) {
            p->ct = time;
            p->tat = p->ct - p->at;
            p->wt = p->tat - p->bt;
            completed++;
        }

        // Enqueue new processes if they have arrived
        for (int i = 0; i < n; i++) {
            if (procs[i].at <= time && procs[i].rt > 0 && procs[i].firstStart == -1) {
                queue[rear++] = i;
                queueSize++;
                procs[i].firstStart = time; // Set first start time when enqueued
            }
        }

        // Re-enqueue the current process if it still has remaining time
        if (p->rt > 0) {
            queue[rear++] = curIndex;
            queueSize++;
        }
    }

    printf("\n");
    free(queue);
}

// Function to print results
void printRes(Process procs[], int n) {
    float tat = 0, wt = 0, response = 0;

    printf("ID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        Process p = procs[i];
        tat += p.tat;
        wt += p.wt;
        response += (p.firstStart - p.at);

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p.id, p.at, p.bt, p.ct, p.tat, p.wt, (p.firstStart - p.at));
    }

    printf("Average Turnaround Time: %.2f\n", tat / n);
    printf("Average Waiting Time: %.2f\n", wt / n);
    printf("Average Response Time: %.2f\n", response / n);
}

int main() {
    int n, quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process procs[n];
    printf("Enter the arrival time and burst time of each process (AT BT):\n");
    for (int i = 0; i < n; i++) {
        printf("Process P%d: ", i + 1);
        scanf("%d %d", &procs[i].at, &procs[i].bt);
        procs[i].id = i + 1;
        procs[i].rt = procs[i].bt;
        procs[i].firstStart = -1;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    sortByArrival(n, procs);
    findTimes(procs, n, quantum);
    printRes(procs, n);

    return 0;
}
