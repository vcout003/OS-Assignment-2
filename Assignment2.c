#include <stdio.h> 

struct Process {
    int pid;            // process ID
    int arrival_time;   // when it arrives
    int burst_time;     // how long it needs
    int waiting_time;   // time spent waiting
    int turnaround_time;// total time from arrival to finish
};

//collect user input
void getProcesses(struct Process p[], int *n) {
    printf("Enter the number of processes: ");
    scanf("%d", n);                    // read into the pointer

    if (*n <= 0) {                     // need braces + no return value in a void func
        printf("You must input a value greater than 0 for number of processes.\n");
        return;
    }

    int pid[*n], burst[*n], arrival[*n];   // use *n, not n

    for (int i = 0; i < *n; i++) {
        pid[i] = i + 1;

        printf("\nP%d Arrival time: ", pid[i]);
        scanf("%d", &arrival[i]);
        if (arrival[i] < 0) {
            printf("You must input a positive integer for arrival.\n");
            return;
        }

        printf("P%d Burst time: ", pid[i]);
        scanf("%d", &burst[i]);
        if (burst[i] <= 0) {
            printf("You must input a value greater than 0 for burst.\n");
            return;
        }

        // write into the struct array the rest of your code uses
        p[i].pid = pid[i];
        p[i].arrival_time = arrival[i];
        p[i].burst_time = burst[i];
        p[i].waiting_time = 0;
        p[i].turnaround_time = 0;
    }

    printf("\nEnter process details:\n");
    for (int i = 0; i < *n; i++) {
        printf("P%d: Arrival=%d, Burst=%d\n", pid[i], arrival[i], burst[i]);
    }
}

//first-come-first-serve method
void fcfs(int n, int pid[], int burst[], int arrival[]) {

    int exit[n], turnaround[n], waiting[n];//variables for outputs
    int time = 0; //variable to track time
    float totalWait = 0, totalTurnaround = 0;//variables to store wait and turnaround time totals

    for (int i = 0; i < n - 1; i++) {//bubble sort for arrival times
        for (int j = 0; j < n - i - 1; j++) {

            if (arrival[j] > arrival[j + 1]) {

                //switch arrival
                int temp = arrival[j];
                arrival[j] = arrival[j + 1];
                arrival[j + 1] = temp;

                //switch burst
                temp = burst[j];
                burst[j] = burst[j + 1];
                burst[j + 1] = temp;

                //switch pid
                temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {//for loop to compute times for processes

        if (time < arrival[i]) {//if CPU is idle
            time = arrival[i]; //wait
        }

        time += burst[i]; //add burst
        exit[i] = time; //store exit time
        turnaround[i] = exit[i] - arrival[i];//compute turnaround time
        waiting[i] = turnaround[i] - burst[i];//compute wait time
        totalWait += waiting[i];//adding to total wait time
        totalTurnaround += turnaround[i];//adding to total turnaround time
    }

    //print expected outputs
    printf("\nSimulating FCFS...\n");
    printf("Order: ");

    for (int i = 0; i < n; i++) {

        printf("P%d", pid[i]);
        if (i < n - 1) printf(" -> ");
    }

    printf("\nAvg Waiting Time: %.2f\n", totalWait / n);
    printf("Avg Turnaround Time: %.2f\n", totalTurnaround / n);

}

void sjf(struct Process p[], int n) { //Arantza
    if (n <= 0) return;

    int time = 0, done_count = 0;
    int done[n];         // 0 = not done, 1 = done
    int order[n];        // execution order (indices into p[])
    for (int i = 0; i < n; i++) done[i] = 0;

    // start at earliest arrival
    time = p[0].arrival_time;
    for (int i = 1; i < n; i++)
        if (p[i].arrival_time < time) time = p[i].arrival_time;

    float totW = 0.0f, totT = 0.0f;

    while (done_count < n) {
        // pick the arrived job with the smallest burst
        int pick = -1;
        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival_time <= time) {
                if (pick == -1 || p[i].burst_time < p[pick].burst_time)
                    pick = i;
            }
        }

        if (pick == -1) {
            // CPU idle: jump to next arrival
            int next = -1;
            for (int i = 0; i < n; i++)
                if (!done[i] && (next == -1 || p[i].arrival_time < next))
                    next = p[i].arrival_time;
            time = next;
            continue;
        }

        time += p[pick].burst_time;
        p[pick].turnaround_time = time - p[pick].arrival_time;
        p[pick].waiting_time = p[pick].turnaround_time - p[pick].burst_time;

        totW += p[pick].waiting_time;
        totT += p[pick].turnaround_time;

        done[pick] = 1;
        order[done_count++] = pick;
    }

    // print like FCFS
    printf("\nSimulating SJF...\n");
    printf("Order: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", p[order[i]].pid);
        if (i < n - 1) printf(" -> ");
    }
    printf("\nAvg Waiting Time: %.2f\n", totW / n);
    printf("Avg Turnaround Time: %.2f\n", totT / n);

    // reorder p[] to the SJF execution order so your Gantt chart matches
    struct Process tmp[n];
    for (int i = 0; i < n; i++) tmp[i] = p[order[i]];
    for (int i = 0; i < n; i++) p[i] = tmp[i];

}


// OR Shortest Job First scheduling
// (You can swap this out for Round Robin or Priority Scheduling)

// --------------------
// Helpers
// --------------------
void calculateAverage(struct Process p[], int n, float *avg_waiting, float *avg_turnaround) { //Arantza
    if (n <= 0) {
        if (avg_waiting) *avg_waiting = 0.0f;
        if (avg_turnaround) *avg_turnaround = 0.0f;
        return;
    }

    long total_wait = 0;
    long total_turn = 0;

    for (int i = 0; i < n; i++) {
        total_wait += p[i].waiting_time;
        total_turn += p[i].turnaround_time;
    }

    if (avg_waiting) *avg_waiting = (float) total_wait / (float) n;
    if (avg_turnaround) *avg_turnaround = (float) total_turn / (float) n;
}
// Compute average waiting and turnaround time

void printResults(struct Process p[], int n, float avg_waiting, float avg_turnaround) { // Andy
    printf("\n%-8s %-10s %-10s %-12s %-15s\n",
           "PID", "Arrival", "Burst", "Waiting", "Turnaround");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("P%-7d %-10d %-10d %-12d %-15d\n",
               p[i].pid, p[i].arrival_time, p[i].burst_time,
               p[i].waiting_time, p[i].turnaround_time);
    }

    printf("-----------------------------------------------------------\n");
    printf("Average Waiting Time   = %.2f\n", avg_waiting);
    printf("Average Turnaround Time= %.2f\n", avg_turnaround);
}
// Print table of results (pid, arrival, burst, waiting, turnaround)

void printGanttChart(struct Process p[], int n) { //Andy 
    printf("\nGantt Chart:\n");

    // top bar
    printf(" ");
    for (int i = 0; i < n; i++) printf("------");
    printf("\n|");

    // process sequence (uses the order of p[])
    for (int i = 0; i < n; i++) printf(" P%d  |", p[i].pid);

    // bottom bar
    printf("\n ");
    for (int i = 0; i < n; i++) printf("------");

    // timeline: start at earliest arrival, include idle gaps
    int time = p[0].arrival_time;
    for (int i = 1; i < n; i++)
        if (p[i].arrival_time < time) time = p[i].arrival_time;

    printf("\n%d", time);
    for (int i = 0; i < n; i++) {
        if (time < p[i].arrival_time) time = p[i].arrival_time; // idle until it arrives
        time += p[i].burst_time;
        printf("     %d", time);
    }
    printf("\n");
}


// Show a simple timeline of execution

int main() {

    struct Process processes[20];
    int n;

    getProcesses(processes, &n);//collect input from user

    // build arrays for FCFS
    int pid[20], burst[20], arrival[20];
    for (int i = 0; i < n; i++) {
        pid[i] = processes[i].pid;
        burst[i] = processes[i].burst_time;
        arrival[i] = processes[i].arrival_time;
    }

    fcfs(n, pid, burst, arrival);//trigger first come first serve algorithm
    struct Process fcfsSeq[20];
    for (int i = 0; i < n; i++) {
        fcfsSeq[i].pid = pid[i];
        fcfsSeq[i].arrival_time = arrival[i];
        fcfsSeq[i].burst_time = burst[i];
    }
    printf("\nGantt Chart (FCFS):");
    printGanttChart(fcfsSeq, n);

    sjf(processes, n);//trigger shortest job first algorithm
    printf("\nGantt Chart (SJF):");
    printGanttChart(processes, n);
    return 0;
}




