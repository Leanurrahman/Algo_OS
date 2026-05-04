#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[10], bt[10], pr[10];
    int rt[10];
    int ct[10], tat[10], wt[10];
    bool completed[10] = {false};

    for(int i = 0; i < n; i++) {
        cout << "\nEnter Arrival Time for P" << (i+1) << ": ";
        cin >> at[i];
        cout << "Enter Burst Time for P" << (i+1) << ": ";
        cin >> bt[i];
        cout << "Enter Priority for P" << (i+1) << " (Lower is better): ";
        cin >> pr[i];

        rt[i] = bt[i];
    }

    int time = 0;
    int completed_count = 0;
    int total_wt = 0, total_tat = 0;

    cout << "\nGantt Chart:\n";
    cout << time;

    int last_process = -1;

    while(completed_count < n) {
        int idx = -1;
        int min_priority = 100000;

        for(int i = 0; i < n; i++) {
            if(at[i] <= time && !completed[i]) {
                if(pr[i] < min_priority) {
                    min_priority = pr[i];
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            if(last_process != idx) {
                cout << " -- P" << (idx+1);
                last_process = idx;
            }

            rt[idx]--;
            time++;

            if(rt[idx] == 0) {
                completed[idx] = true;
                completed_count++;

                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                total_wt += wt[idx];
                total_tat += tat[idx];

                cout << " -- " << time;
                last_process = -1;
            }
        } else {
            cout << " -- Idle -- " << (time + 1);
            time++;
            last_process = -1;
        }
    }

    cout << "\n\nProcess\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << (i+1) << "\t"
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
