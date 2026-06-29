#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n, head, diskSize;
    char direction;

    cout << "Enter number of disk requests: ";
    cin >> n;

    int request[100], left[100], right[100], sequence[200];
    int l = 0, r = 0, s = 0;

    cout << "Enter disk requests:\n";
    for (int i = 0; i < n; i++) {
        cin >> request[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter disk size (maximum cylinder): ";
    cin >> diskSize;

    cout << "Enter direction (L for Left, R for Right): ";
    cin >> direction;

    for (int i = 0; i < n; i++) {
        if (request[i] < head)
            left[l++] = request[i];
        else
            right[r++] = request[i];
    }

    if (direction == 'L' || direction == 'l')
        left[l++] = 0;
    else
        right[r++] = diskSize - 1;

    sort(left, left + l);
    sort(right, right + r);

    int current = head;
    int seekCount = 0;

    if (direction == 'R' || direction == 'r') {
        for (int i = 0; i < r; i++) {
            sequence[s++] = right[i];
            seekCount += abs(current - right[i]);
            current = right[i];
        }

        for (int i = l - 1; i >= 0; i--) {
            sequence[s++] = left[i];
            seekCount += abs(current - left[i]);
            current = left[i];
        }
    }
    else {
        for (int i = l - 1; i >= 0; i--) {
            sequence[s++] = left[i];
            seekCount += abs(current - left[i]);
            current = left[i];
        }

        for (int i = 0; i < r; i++) {
            sequence[s++] = right[i];
            seekCount += abs(current - right[i]);
            current = right[i];
        }
    }

    cout << "\nSeek Sequence:\n";
    cout << head;

    for (int i = 0; i < s; i++) {
        cout << " -> " << sequence[i];
    }

    cout << "\n\nTotal Seek Distance = " << seekCount << endl;
    cout << "Average Seek Distance = " << (float)seekCount / n << endl;

    return 0;
}




//8
//98 183 37 122 14 124 65 67
//53
///200
//R
