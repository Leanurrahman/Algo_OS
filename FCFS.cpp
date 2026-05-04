#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    // Arrays for process data
    int pid[10], at[10], bt[10], ct[10], tat[10], wt[10];

    // Input
    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "\nEnter Arrival Time for Process " << pid[i] << ": ";
        cin >> at[i];
        cout << "Enter Burst Time for Process " << pid[i] << ": ";
        cin >> bt[i];
    }

    // Calculate Completion Time (NO SORTING - input order maintained)
    int current_time = 0;
    for(int i = 0; i < n; i++) {
        if(current_time < at[i]) {
            current_time = at[i]; // CPU idle, wait until arrival
        }
        ct[i] = current_time + bt[i];
        current_time = ct[i];
    }

    // Calculate TAT and WT
    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    // Output Table
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << endl;
    }

    // Gantt Chart in format: 0 -- P1 -- 10 -- P2 -- 15 -- ...
    cout << "\nGantt Chart:\n";
    cout << at[0]; // Start time of first process

    for(int i = 0; i < n; i++) {
        cout << " -- P" << pid[i] << " -- " << ct[i];
    }
    cout << endl;

    return 0;
}
