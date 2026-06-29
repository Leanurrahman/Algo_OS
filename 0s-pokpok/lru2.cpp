#include <iostream>
using namespace std;

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int n = 20;
    int frames = 3;

    int memory[3] = {-1, -1, -1};
    int lastUsed[3] = {-1, -1, -1};

    int pageFaults = 0, hits = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        // Check Hit
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = true;
                hits++;
                lastUsed[j] = i;
                break;
            }
        }

        // If Miss
        if (!found) {
            pageFaults++;

            int replaceIndex = -1;

            // Empty frame check
            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            // If no empty frame, replace least recently used page
            if (replaceIndex == -1) {
                int minTime = lastUsed[0];
                replaceIndex = 0;

                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < minTime) {
                        minTime = lastUsed[j];
                        replaceIndex = j;
                    }
                }
            }

            memory[replaceIndex] = page;
            lastUsed[replaceIndex] = i;
        }

        cout << "Page " << page << " -> ";

        for (int j = 0; j < frames; j++) {
            if (memory[j] == -1)
                cout << "- ";
            else
                cout << memory[j] << " ";
        }

        if (found)
            cout << " Hit";
        else
            cout << " Miss";

        cout << endl;
    }

    cout << "\nTotal Page Faults = " << pageFaults << endl;
    cout << "Total Hits = " << hits << endl;
    cout << "Hit Ratio = " << (float)hits / n << endl;
    cout << "Page Fault Ratio = " << (float)pageFaults / n << endl;

    return 0;
}
