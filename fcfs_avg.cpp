#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int pid[10], at[10], bt[10], ct[10], tat[10], wt[10];

    int total_wt = 0, total_tat = 0;

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "\nEnter Arrival Time for Process " << pid[i] << ": ";
        cin >> at[i];
        cout << "Enter Burst Time for Process " << pid[i] << ": ";
        cin >> bt[i];
    }


    int current_time = 0;
    for(int i = 0; i < n; i++) {
        if(current_time < at[i]) {
            current_time = at[i];
        }
        ct[i] = current_time + bt[i];
        current_time = ct[i];
    }

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];

        total_wt += wt[i];
        total_tat += tat[i];
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

    cout << "\nGantt Chart:\n";

    int time = 0;


    cout << time;

    for(int i = 0; i < n; i++) {
        if(time < at[i]) {

            cout << " -- Idle -- " << at[i];
            time = at[i];
        }

        cout << " -- P" << pid[i] << " -- " << ct[i];

        time = ct[i];
    }
    cout << endl;


    cout << "\nAverage Waiting Time: "
         << total_wt / n << endl;

    cout << "Average Turnaround Time: "
         << total_tat / n << endl;

    return 0;
}
