#include <iostream>
using namespace std;

int main() {
    int n = 5; // প্রসেসের সংখ্যা

    // ইনপুট ডাটা (হার্ডকোডেড, চাইলে পরিবর্তন করতে পারো)
    int at[10] = {3, 1, 4, 0, 2}; // Arrival Time
    int bt[10] = {1, 4, 2, 6, 3}; // Burst Time

    int rt[10]; // Remaining Time ট্র্যাক করার জন্য
    for(int i=0; i<n; i++) rt[i] = bt[i]; // শুরুতে Remaining Time = Burst Time

    int ct[10], tat[10], wt[10];
    bool completed[10] = {false};

    int time = 0;
    int completed_count = 0;
    int total_wt = 0, total_tat = 0;

    cout << "Gantt Chart:\n";
    cout << time; // শুরু সময়

    while(completed_count < n) {
        int idx = -1;
        int min_rt = 100000;

        // সবচেয়ে কম Remaining Time এর প্রসেস খুঁজুন
        for(int i=0; i<n; i++) {
            if(at[i] <= time && !completed[i]) {
                if(rt[i] < min_rt) {
                    min_rt = rt[i];
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            // প্রসেস পাওয়া গেছে

            // গ্যান্ট চার্টে প্রসেস নাম প্রিন্ট (প্রতি ১ ইউনিট সময়ে)
            // নোট: SRTF এ প্রসেস মাঝপথে থামতে পারে, তাই আমরা প্রতি ধাপে প্রিন্ট করব
            // কিন্তু সুন্দর দেখানোর জন্য আমরা শেষে একসাথে প্রিন্ট করব বা এখানে সরাসরি প্রিন্ট করব

            // এখানে আমরা ১ ইউনিট সময় এগিয়ে নেব এবং Remaining Time কমাবো
            rt[idx]--;
            time++;

            // যদি প্রসেসটি সম্পূর্ণ শেষ হয়ে যায়
            if(rt[idx] == 0) {
                completed[idx] = true;
                ct[idx] = time;
                tat[idx] = ct[idx] - at[idx];
                wt[idx] = tat[idx] - bt[idx];

                total_wt += wt[idx];
                total_tat += tat[idx];

                completed_count++;
            }

        } else {
            // CPU Idle
            cout << " -- Idle -- " << (time + 1);
            time++;
        }

    }

    for(int i=0; i<n; i++) rt[i] = bt[i];
    for(int i=0; i<n; i++) completed[i] = false;
    time = 0;
    completed_count = 0;

    cout << "\n\nFinal Gantt Chart:\n";
    cout << "0";

    int last_process = -1; // আগের প্রসেস ট্র্যাক করার জন্য

    while(completed_count < n) {
        int idx = -1;
        int min_rt = 100000;

        for(int i=0; i<n; i++) {
            if(at[i] <= time && !completed[i]) {
                if(rt[i] < min_rt) {
                    min_rt = rt[i];
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            // যদি আগের প্রসেস আর বর্তমান প্রসেস একই না হয়, তবে নতুন ব্লক শুরু
            if(last_process != idx) {
                cout << " -- P" << (idx+1);
                last_process = idx;
            }

            rt[idx]--;
            time++;

            if(rt[idx] == 0) {
                completed[idx] = true;
                completed_count++;
                cout << " -- " << time; // প্রসেস শেষ হওয়ার সময়
                last_process = -1; // পরবর্তী প্রসেসের জন্য রিসেট
            }
        } else {
            cout << " -- Idle -- " << (time + 1);
            time++;
            last_process = -1;
        }
    }

    // Output Table
    cout << "\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i=0; i<n; i++) {
        cout << "P" << (i+1) << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << (float)total_wt / n << endl;
    cout << "Average Turnaround Time: " << (float)total_tat / n << endl;

    return 0;
}
