#include <iostream>
using namespace std;

int main() {
    int n, frames;

    cout << "Enter number of pages: ";
    cin >> n;

    int pages[n];

    cout << "Enter reference string: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> frames;

    int memory[frames];
    int lastUsed[frames];

    for (int i = 0; i < frames; i++) {
        memory[i] = -1;
        lastUsed[i] = -1;
    }

    int pageFaults = 0, hits = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool found = false;

        // Check hit
        for (int j = 0; j < frames; j++) {
            if (memory[j] == page) {
                found = true;
                hits++;
                lastUsed[j] = i;
                break;
            }
        }

        // If miss
        if (!found) {
            pageFaults++;

            int replaceIndex = -1;

            // Check empty frame first
            for (int j = 0; j < frames; j++) {
                if (memory[j] == -1) {
                    replaceIndex = j;
                    break;
                }
            }

            // If no empty frame, find least recently used
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
