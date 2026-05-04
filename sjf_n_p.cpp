#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    int at[10], bt[10], ct[10], tat[10], wt[10];
    bool done[10] = {false}; // কোন প্রসেস শেষ হয়েছে তা ট্র্যাক করার জন্য

    // Input
    for(int i = 0; i < n; i++) {
        cout << "\nEnter Arrival Time for P" << (i+1) << ": ";
        cin >> at[i];
        cout << "Enter Burst Time for P" << (i+1) << ": ";
        cin >> bt[i];
    }

    int time = 0;       // বর্তমান সময়
    int completed = 0;  // কতগুলো প্রসেস শেষ হয়েছে
    int total_wt = 0, total_tat = 0;

    cout << "\nGantt Chart:\n";
    cout << time; // শুরু সময় (সাধারণত 0)

    while(completed < n) {
        int idx = -1;         // কোন প্রসেস নেওয়া হবে
        int min_bt = 100000;  // সবচেয়ে কম বাস্ট টাইম খুঁজার জন্য

        // রেডি কিউ থেকে shortest job খুঁজুন
        for(int i = 0; i < n; i++) {
            if(at[i] <= time && !done[i]) {
                if(bt[i] < min_bt) {
                    min_bt = bt[i];
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            // প্রসেস এক্সিকিউট করুন
            cout << " -- P" << (idx+1) << " -- ";

            time += bt[idx];      // সময় বাড়ান
            ct[idx] = time;       // Completion Time
            tat[idx] = ct[idx] - at[idx]; // Turnaround Time
            wt[idx] = tat[idx] - bt[idx]; // Waiting Time

            total_wt += wt[idx];
            total_tat += tat[idx];

            done[idx] = true;     // প্রসেস শেষ হিসেবে চিহ্নিত করুন
            completed++;

            cout << time;         // শেষ সময় প্রিন্ট করুন
        }
        else {
            // CPU Idle
            cout << " -- Idle -- ";
            time++;               // সময় ১ ইউনিট বাড়ান
            cout << time;         // নতুন সময় প্রিন্ট করুন
        }
    }

    // Output Table
    cout << "\n\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << (i+1) << "\t" << at[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    // Average Times
    cout << "\nAverage Waiting Time: " << (float)total_wt / n << endl;
    cout << "Average Turnaround Time: " << (float)total_tat / n << endl;

    return 0;
}
