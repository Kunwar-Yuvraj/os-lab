// Pre-emptive SJF

#include <stdio.h>
#include <limits.h>

typedef struct {
    int id, at, bt, rt, ct, tat, wt, start;
} Process;

// Function to find the index of the process with the shortest burst time
int findShortestJobIndex(Process procs[], int n, int time) {
    int minIndex = -1;
    int minRT = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (procs[i].at <= time && procs[i].rt > 0 && procs[i].rt < minRT) {
            minIndex = i;
            minRT = procs[i].rt;
        }
    }

    return minIndex;
}

// Function to calculate times and generate Gantt Chart for non-preemptive SJF
void findTimes(Process procs[], int n) {
    int time = 0;
    int completed = 0;

    printf("Gantt Chart:\n");

    while (completed < n) {
        int curIndex = findShortestJobIndex(procs, n, time);

        if (curIndex == -1) {
            printf("Idle ");
            time++;
            continue;
        }

        Process* p = &procs[curIndex];

        if (p->rt == p->bt) {
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

// Function to print results
void printRes(Process procs[], int n) {
    float tat = 0;
    float wt = 0;
    float response = 0;

    printf("ID\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        Process p = procs[i];
        tat += p.tat;
        wt += p.wt;
        response += (p.start - p.at);

        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p.id, p.at, p.bt, p.ct, p.tat, p.wt, (p.start - p.at));
    }

    printf("Average Turnaround Time: %.2f\n", tat / n);
    printf("Average Waiting Time: %.2f\n", wt / n);
    printf("Average Response Time: %.2f\n", response / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process procs[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &procs[i].at, &procs[i].bt);

        procs[i].id = i + 1;
        procs[i].rt = procs[i].bt;
        procs[i].start = -1;
    }

    findTimes(procs, n);
    printRes(procs, n);

    return 0;
}
