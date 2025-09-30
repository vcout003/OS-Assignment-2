struct Process {
    int pid;            // process ID
    int arrival_time;   // when it arrives
    int burst_time;     // how long it needs
    int waiting_time;   // time spent waiting
    int turnaround_time;// total time from arrival to finish
};

//collect user input
void getProcesses(struct Process p[], int *n) {
     
    int n;  //variable to store # of processes

    printf("Enter the number of processes: ");//prompting user
    scanf("%d", &n);//storing user input

    if (n <= 0)
            printf("You must input a value greater than 0 for number of processes.\n");
            return 1;

    int pid[n], burst[n], arrival[n]; //creating arrays to store process details from user

    for (int i = 0; i < n; i++) { //for loop to request the details for the processes based on # of processes entered by user
        pid[i] = i + 1; // assign process IDs automatically as P1, P2, ...
        
        printf("\nP%d Arrival time: ", pid[i]);
        scanf("%d", &arrival[i]);

        if (arrival[i] < 0)
            printf("You must input a positive integer for arrival.\n");
            return 1;

        printf("P%d Burst time: ", pid[i]);
        scanf("%d", &burst[i]);

        if (burst[i] <= 0)
            printf("You must input a value greater than 0 for burst.\n");
            return 1;
    }

    printf("\nEnter process details:\n");

    for (int i = 0; i < n; i++) {
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

void sjf(struct Process p[], int n);   //Arantza
// OR Shortest Job First scheduling
// (You can swap this out for Round Robin or Priority Scheduling)

// --------------------
// Helpers
// --------------------
void calculateAverage(struct Process p[], int n, //Arantza
                      float *avg_waiting, float *avg_turnaround);  
// Compute average waiting and turnaround time

void printResults(struct Process p[], int n, //Andy
                  float avg_waiting, float avg_turnaround);  
// Print table of results (pid, arrival, burst, waiting, turnaround)

void printGanttChart(struct Process p[], int n);  //Andy
// Show a simple timeline of execution

int main() {

    struct Process processes[20];
    int n;

    getProcesses(processes, &n);//collect input from user

    fcfs(processes, n);//trigger first come first serve algorithm

    sjf(processes, n);//trigger shortest job first algorithm

    return 0;
}



