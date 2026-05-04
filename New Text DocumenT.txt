//1.FCFS

#include <iostream>
using namespace std;

#define max 30

int main()
{
    int i, j, num_of_process;
    int burst[max], waiting[max], TAT[max], arrival[max], temp[max];
    string pid[max];
    float avg_waiting = 0, avgTAT = 0;

    cout << "Enter num of process: ";
    cin >> num_of_process;

    cout << "Enter Burst Time of the process: ";
    for (i = 0; i < num_of_process; i++)
    {
        cin >> burst[i];
        pid[i] = "P" + to_string(i + 1);
    }

    cout << "Enter Arrival time of this processes: ";
    for (i = 0; i < num_of_process; i++)
    {
        cin >> arrival[i];
    }

    // 🔹 FCFS Sorting (stable)
    for (i = 0; i < num_of_process - 1; i++)
    {
        for (j = 0; j < num_of_process - i - 1; j++)
        {
            if (arrival[j] > arrival[j + 1])
            {
                swap(arrival[j], arrival[j + 1]);
                swap(burst[j], burst[j + 1]);
                swap(pid[j], pid[j + 1]);
            }
        }
    }

    // 🔹 Gantt Chart
    int time = 0;

    cout << "\n ----------------------------------------\n|";

    for (i = 0; i < num_of_process; i++)
    {
        if (time < arrival[i])
        {
            cout << "       |"; // idle
            time = arrival[i];
        }

        cout << "  " << pid[i] << "   |";
        time += burst[i];
    }

    cout << "\n ----------------------------------------\n";

    // Timeline
    time = 0;
    cout << "0";

    for (i = 0; i < num_of_process; i++)
    {
        if (time < arrival[i])
        {
            time = arrival[i];
            cout << "       " << time;
        }

        time += burst[i];
        cout << "       " << time;
    }

    cout << "\n\n";

    // 🔹 Calculation (same logic but corrected with arrival)
    temp[0] = 0;
    time = 0;

    cout << "process\t burst time\t Arrival time\t waiting time\t Turn Around Time\n";

    for (i = 0; i < num_of_process; i++)
    {
        if (time < arrival[i])
            time = arrival[i];

        temp[i] = time;
        waiting[i] = temp[i] - arrival[i];
        TAT[i] = waiting[i] + burst[i];

        time += burst[i];

        avg_waiting += waiting[i];
        avgTAT += TAT[i];

        cout << pid[i] << "\t"
             << burst[i] << "\t\t"
             << arrival[i] << "\t\t"
             << waiting[i] << "\t\t"
             << TAT[i] << endl;
    }

    avg_waiting = avg_waiting / num_of_process;
    avgTAT = avgTAT / num_of_process;

    cout << "\navg waiting time: " << avg_waiting;
    cout << "\nAVG Turn Around time: " << avgTAT;

    return 0;
}

--------------------------------------------------------------------------------

//2.SRTF

#include <iostream>
using namespace std;

int main() {
    int n = 5;

    int pid[] = {1, 2, 3, 4, 5};
    int at[]  = {3, 1, 4, 0, 2};
    int bt[]  = {1, 4, 2, 6, 3};

    int rt[5];
    for(int i = 0; i < n; i++)
        rt[i] = bt[i];

    int wt[5] = {0}, tat[5];

    int complete = 0, t = 0;
    int shortest, minm;
    bool found;

    int gantt[100], time[100];
    int idx = 0;

    while (complete != n) {

        minm = 9999;
        found = false;

        for (int i = 0; i < n; i++) {
            if (at[i] <= t && rt[i] > 0 && rt[i] < minm) {
                minm = rt[i];
                shortest = i;
                found = true;
            }
        }

        if (!found) {
            t++;
            continue;
        }

        // Gantt store
        gantt[idx] = pid[shortest];
        time[idx] = t;
        idx++;

        rt[shortest]--;

        if (rt[shortest] == 0) {
            complete++;
            int finish = t + 1;

            wt[shortest] = finish - bt[shortest] - at[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        t++;
    }

    // TAT calculate
    for (int i = 0; i < n; i++)
        tat[i] = bt[i] + wt[i];

    // 🔥 Average calculation add
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }

    float avg_wt = total_wt / n;
    float avg_tat = total_tat / n;

    // Gantt Chart
    cout << "\nGantt Chart:\n";

    cout << time[0];

    for (int i = 0; i < idx; i++) {
        cout << " -- P" << gantt[i];

        if (i == idx - 1 || gantt[i] != gantt[i + 1]) {
            cout << " -- " << time[i] + 1;
        }
    }

    cout << endl;

    // Table
    cout << "\nPID\tAT\tBT\tWT\tTAT\n";
    for (int i = 0; i < n; i++) {
        cout << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << wt[i] << "\t"
             << tat[i] << "\n";
    }

    // 🔥 Print averages
    cout << "\nAverage Waiting Time = " << avg_wt;
    cout << "\nAverage Turnaround Time = " << avg_tat;

    return 0;
}


-------------------------------------------------------------------------
//3.SJF

#include <iostream>
using namespace std;

int main() {
    int n = 5;

    // Given data
    int at[5] = {4, 0, 1, 6, 2};
    int bt[5] = {5, 2, 5, 7, 3};

    int ct[5], tat[5], wt[5];
    bool visited[5] = {false};

    int completed = 0, time = 0;

    // Gantt Chart
    int order[5];
    int timeline[6];
    int k = 0;

    timeline[0] = 0;

    while (completed < n) {
        int idx = -1;
        int min_bt = 100000;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && !visited[i]) {
                if (idx == -1 ||
                    bt[i] < min_bt ||
                    (bt[i] == min_bt && at[i] < at[idx])) {

                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            order[k] = idx;

            time += bt[idx];
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];

            visited[idx] = true;
            completed++;

            k++;
            timeline[k] = time;
        } else {
            time++; // CPU idle
        }
    }

    // Output Table
    cout << "Process\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << "\n";
    }

    // Gantt Chart
    cout << "\nGantt Chart:\n|";
    for (int i = 0; i < n; i++) {
        cout << " P" << order[i] + 1 << " |";
    }

    cout << "\n" << timeline[0];
    for (int i = 1; i <= n; i++) {
        cout << "    " << timeline[i];
    }
    cout << endl;

    return 0;
}

----------------------------------------------------------------

//4.Priority(lower val higher priority)

#include <iostream>
#include <vector>
using namespace std;

int main() {

    int n = 5;

    vector<int> pid = {1, 2, 3, 4, 5};
    vector<int> at  = {0,5,12,2,9};
    vector<int> bt  = {11,28,2,10,16};
    vector<int> pr  = {2,0,3,1,4};

    vector<int> ct(n), tat(n), wt(n), st(n), done(n, 0);

    vector<int> gantt_pid;
    vector<int> gantt_time;

    int completed = 0;
    int time = 0;

    while (completed < n) {

        int idx = -1;

        for (int i = 0; i < n; i++) {

            if (at[i] <= time && done[i] == 0) {

                if (idx == -1 ||
                    pr[i] < pr[idx] ||
                    (pr[i] == pr[idx] && at[i] < at[idx])) {

                    idx = i;
                }
            }
        }

        // CPU idle
        if (idx == -1) {
            time++;
            continue;
        }

        st[idx] = time;
        ct[idx] = time + bt[idx];

        gantt_pid.push_back(pid[idx]);
        gantt_time.push_back(time);

        time = ct[idx];
        done[idx] = 1;
        completed++;
    }

    gantt_time.push_back(time);

    // ---------------- GANTT CHART ----------------
    cout << "\nGantt Chart:\n";
    cout << "-------------------------------------------------\n|";

    for (int i = 0; i < gantt_pid.size(); i++) {
        cout << " P" << gantt_pid[i] << " |";
    }

    cout << "\n-------------------------------------------------\n";

    for (int i = 0; i < gantt_time.size(); i++) {
        cout << gantt_time[i] << " ";
    }

    cout << "\n\n";

    // ---------------- TABLE ----------------
    float total_wt = 0, total_tat = 0;

    cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {

        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];

        total_wt += wt[i];
        total_tat += tat[i];

        cout << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << "\n";
    }

    cout << "\nAverage Waiting Time = " << total_wt / n;
    cout << "\nAverage Turnaround Time = " << total_tat / n << endl;

    return 0;
}

----------------------------------------
(Higher val Higher priority)

#include <iostream>
#include <vector>
using namespace std;

int main() {

    int n = 6;

    vector<int> pid = {1, 2, 3, 4, 5, 6};
    vector<int> at  = {3, 2, 5, 4, 1, 0};
    vector<int> bt  = {5, 4, 1, 7, 6, 2};
    vector<int> pr  = {2, 1, 3, 4, 3, 5};

    vector<int> ct(n), tat(n), wt(n), st(n), done(n, 0);

    vector<int> gantt_pid;
    vector<int> gantt_time;

    int completed = 0;
    int time = 0;

    while (completed < n) {

        int idx = -1;

        for (int i = 0; i < n; i++) {

            if (at[i] <= time && done[i] == 0) {

                // ✔ HIGHER VALUE = HIGHER PRIORITY
                if (idx == -1 ||
                    pr[i] > pr[idx] ||
                    (pr[i] == pr[idx] && at[i] < at[idx])) {

                    idx = i;
                }
            }
        }

        // CPU idle
        if (idx == -1) {
            time++;
            continue;
        }

        st[idx] = time;
        ct[idx] = time + bt[idx];

        gantt_pid.push_back(pid[idx]);
        gantt_time.push_back(time);

        time = ct[idx];
        done[idx] = 1;
        completed++;
    }

    gantt_time.push_back(time);

    // ---------------- GANTT CHART ----------------
    cout << "\nGantt Chart:\n";
    cout << "-------------------------------------------------\n|";

    for (int i = 0; i < gantt_pid.size(); i++) {
        cout << " P" << gantt_pid[i] << " |";
    }

    cout << "\n-------------------------------------------------\n";

    for (int i = 0; i < gantt_time.size(); i++) {
        cout << gantt_time[i] << " ";
    }

    cout << "\n\n";

    // ---------------- TABLE ----------------
    float total_wt = 0, total_tat = 0;

    cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n";

    for (int i = 0; i < n; i++) {

        tat[i] = ct[i] - at[i];
        wt[i]  = tat[i] - bt[i];

        total_wt += wt[i];
        total_tat += tat[i];

        cout << pid[i] << "\t"
             << at[i] << "\t"
             << bt[i] << "\t"
             << pr[i] << "\t"
             << ct[i] << "\t"
             << tat[i] << "\t"
             << wt[i] << "\n";
    }

    cout << "\nAverage Waiting Time = " << total_wt / n;
    cout << "\nAverage Turnaround Time = " << total_tat / n << endl;

    return 0;
}

