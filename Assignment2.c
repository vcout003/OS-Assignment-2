// --------------------
// Data structure
// --------------------
struct Process {
    int pid;            // process ID
    int arrival_time;   // when it arrives
    int burst_time;     // how long it needs
    int waiting_time;   // time spent waiting
    int turnaround_time;// total time from arrival to finish
};

// --------------------
// Input
// --------------------
void getProcesses(struct Process p[], int *n);  //victoria
// Ask user (or read from file) how many processes and their details

// --------------------
// Scheduling Algorithms
// --------------------
void fcfs(struct Process p[], int n);  //victoria
// First-Come, First-Served scheduling

void sjf(struct Process p[], int n);   //Aranza
// OR Shortest Job First scheduling
// (You can swap this out for Round Robin or Priority Scheduling)

// --------------------
// Helpers
// --------------------
void calculateAverage(struct Process p[], int n, //Aranza
                      float *avg_waiting, float *avg_turnaround);  
// Compute average waiting and turnaround time

void printResults(struct Process p[], int n, //Andy
                  float avg_waiting, float avg_turnaround);  
// Print table of results (pid, arrival, burst, waiting, turnaround)

void printGanttChart(struct Process p[], int n);  //Andy
// Show a simple timeline of execution

// --------------------
// Error Handling
// --------------------
int validateInput(struct Process p[], int n);  //victoria
// Check for invalid values (like negative times or duplicate PIDs)

int main() {
    struct Process processes[20];
    int n;

    // Step 1: Get input
    getProcesses(processes, &n);

    // Step 2: Validate input
    if (!validateInput(processes, n)) {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    // Step 3: Run FCFS
    fcfs(processes, n);

    // Step 4: Run another algorithm (SJF / RR / Priority)
    sjf(processes, n);

    return 0;
}

