#include <iostream>
using namespace std;

int main() {
    int n = 5; // processes
    int m = 3; // resources A, B, C

    int allocation[5][3] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int maxNeed[5][3] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int available[3] = {3, 3, 2};

    int need[5][3];

    // Need = Max - Allocation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }

    bool finish[5] = {false};
    int safeSeq[5];
    int count = 0;

    while (count < n) {
        bool found = false;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canRun = true;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {
                        canRun = false;
                        break;
                    }
                }

                if (canRun) {
                    for (int j = 0; j < m; j++) {
                        available[j] += allocation[i][j];
                    }

                    safeSeq[count] = i;
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "System is not in safe state." << endl;
            return 0;
        }
    }

    cout << "System is in safe state." << endl;
    cout << "Safe Sequence: ";

    for (int i = 0; i < n; i++) {
        cout << "T" << safeSeq[i];
        if (i != n - 1) cout << " -> ";
    }

    return 0;
}

//Safe Sequence: T1 -> T3 -> T4 -> T0 -> T2
