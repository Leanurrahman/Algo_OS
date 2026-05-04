#include <iostream>
using namespace std; //NON-preeemtive

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int pid[10], at[10], bt[10], pr[10];
    int ct[10], tat[10], wt[10];
    bool done[10] = {false};

    for(int i = 0; i < n; i++) {
        pid[i] = i + 1;
        cout << "\nEnter Arrival Time for P" << pid[i] << ": ";
        cin >> at[i];

        cout << "Enter Burst Time for P" << pid[i] << ": ";
        cin >> bt[i];

        cout << "Enter Priority for P" << pid[i] << " (Higher is better): ";
        cin >> pr[i];
    }

    int time = 0;
    int completed = 0;
    int total_wt = 0, total_tat = 0;

    cout << "\nGantt Chart:\n";
    cout << time;

    while(completed < n) {
        int idx = -1;
        int max_priority = -1;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && !done[i]) {
                if(pr[i] > max_priority) {
                    max_priority = pr[i];
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            cout << " -- P" << (idx+1) << " -- ";

            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            total_wt += wt[idx];
            total_tat += tat[idx];

            done[idx] = true;
            completed++;

            cout << time;
        }
        else {
            cout << " -- Idle -- ";
            time++;
            cout << time;
        }
    }

    cout << "\n\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)total_wt / n << endl;
    cout << "Average Turnaround Time: " << (float)total_tat / n << endl;

    return 0;
}
