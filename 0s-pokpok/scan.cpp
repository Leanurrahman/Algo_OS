#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n, head, diskSize;
    char direction;

    cout << "Enter number of disk requests: ";
    cin >> n;

    vector<int> requests(n);

    cout << "Enter disk requests:\n";
    for (int i = 0; i < n; i++) {
        cin >> requests[i];
    }

    cout << "Enter initial head position: ";
    cin >> head;

    cout << "Enter disk size (maximum cylinder): ";
    cin >> diskSize;

    cout << "Enter direction (L for Left, R for Right): ";
    cin >> direction;

    vector<int> left, right, sequence;

    for (int req : requests) {
        if (req < head)
            left.push_back(req);
        else
            right.push_back(req);
    }

    if (direction == 'L' || direction == 'l')
        left.push_back(0);
    else
        right.push_back(diskSize - 1);

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int seekCount = 0;
    int current = head;

    if (direction == 'R' || direction == 'r') {
        for (int req : right) {
            sequence.push_back(req);
            seekCount += abs(current - req);
            current = req;
        }

        for (int i = left.size() - 1; i >= 0; i--) {
            sequence.push_back(left[i]);
            seekCount += abs(current - left[i]);
            current = left[i];
        }
    }
    else {
        for (int i = left.size() - 1; i >= 0; i--) {
            sequence.push_back(left[i]);
            seekCount += abs(current - left[i]);
            current = left[i];
        }

        for (int req : right) {
            sequence.push_back(req);
            seekCount += abs(current - req);
            current = req;
        }
    }

    cout << "\nSeek Sequence:\n";
    cout << head;

    for (int x : sequence) {
        cout << " -> " << x;
    }

    cout << "\n\nTotal Seek Distance = " << seekCount << endl;
    cout << "Average Seek Distance = " << (float)seekCount / n << endl;

    return 0;
}
