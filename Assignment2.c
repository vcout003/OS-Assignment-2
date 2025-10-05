#include <stdio.h>
#include <stdlib.h>

struct Process {
    int pid;             // process ID
    int arrival_time;    // arrival time
    int burst_time;      // burst time
    int waiting_time;    // waiting time
    int turnaround_time; // turnaround time
    int completion_time; // completion time
};

// Function prototypes
void getProcesses(struct Process p[], int *n);
void printResults(struct Process p[], int n, float avg_waiting, float avg_turnaround);
void printGanttChart(struct Process p[], int n);
void fcfs(struct Process p[], int n);
void sjf(struct Process p[], int n);

// Input processes from user
void getProcesses(struct Process p[], int *n) {
    printf("Enter the number of processes: ");
    if (scanf("%d", n) != 1 || *n <= 0) {
        printf("Invalid number of processes!\n");
        exit(1);
    }

    for (int i = 0; i < *n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time of P%d: ", p[i].pid);
        if (scanf("%d", &p[i].arrival_time) != 1 || p[i].arrival_time < 0) {
            printf("Invalid input for arrival time!\n");
            exit(1);
        }
        printf("Enter burst time of P%d: ", p[i].pid);
        if (scanf("%d", &p[i].burst_time) != 1 || p[i].burst_time <= 0) {
            printf("Invalid input for burst time!\n");
            exit(1);
        }
    }
}

// Print process table and averages
void printResults(struct Process p[], int n, float avg_waiting, float avg_turnaround) {
    printf("\n%-5s %-10s %-10s %-10s %-15s %-15s\n", 
           "PID", "Arrival", "Burst", "Completion", "Waiting", "Turnaround");
    for (int i = 0; i < n; i++) {
        printf("%-5d %-10d %-10d %-10d %-15d %-15d\n", 
               p[i].pid, p[i].arrival_time, p[i].burst_time, 
               p[i].completion_time, p[i].waiting_time, p[i].turnaround_time);
    }
    printf("Average Waiting Time   = %.2f\n", avg_waiting);
    printf("Average Turnaround Time= %.2f\n", avg_turnaround);
}

// Print Gantt chart
void printGanttChart(struct Process p[], int n) {
    printf("\nGantt Chart:\n ");
    for (int i = 0; i < n; i++) {
        printf("----");
    }
    printf("-\n|");
    for (int i = 0; i < n; i++) {
        printf(" P%d |", p[i].pid);
    }
    printf("\n ");
    for (int i = 0; i < n; i++) {
        printf("----");
    }
    printf("-\n0");
    for (int i = 0; i < n; i++) {
        printf("   %d", p[i].completion_time);
    }
    printf("\n");
}

// First Come First Serve
void fcfs(struct Process p[], int n) {
    printf("\n===== First Come First Serve (FCFS) =====\n");

    // sort by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].arrival_time > p[j+1].arrival_time) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    int time = 0;
    float total_wait = 0, total_turn = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time) time = p[i].arrival_time; // CPU idle
        time += p[i].burst_time;
        p[i].completion_time = time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        total_wait += p[i].waiting_time;
        total_turn += p[i].turnaround_time;
    }

    printResults(p, n, total_wait / n, total_turn / n);
    printGanttChart(p, n);
}

// Shortest Job First (Non-preemptive)
void sjf(struct Process p[], int n) {
    printf("\n===== Shortest Job First (SJF Non-preemptive) =====\n");

    int completed = 0, time = 0;
    float total_wait = 0, total_turn = 0;
    int isCompleted[100] = {0};

    while (completed < n) {
        int idx = -1, min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= time && !isCompleted[i]) {
                if (p[i].burst_time < min_burst) {
                    min_burst = p[i].burst_time;
                    idx = i;
                }
                else if (p[i].burst_time == min_burst) {
                    if (p[i].arrival_time < p[idx].arrival_time) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            time += p[idx].burst_time;
            p[idx].completion_time = time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

            total_wait += p[idx].waiting_time;
            total_turn += p[idx].turnaround_time;
            isCompleted[idx] = 1;
            completed++;
        } else {
            time++;
        }
    }

    printResults(p, n, total_wait / n, total_turn / n);
    printGanttChart(p, n);
}

int main() {
    struct Process processes[100];
    int n;

    getProcesses(processes, &n);

    fcfs(processes, n);
    sjf(processes, n);

    return 0;
}





