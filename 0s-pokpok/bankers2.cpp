#include <iostream>
using namespace std;

int main()
{
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    int allocation[n][m], maxNeed[n][m], need[n][m];
    int available[m];

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> allocation[i][j];
        }
    }

    cout << "\nEnter Max Matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> maxNeed[i][j];
        }
    }

    cout << "\nEnter Available Resources:\n";
    for (int i = 0; i < m; i++)
    {
        cin >> available[i];
    }

    // Need Matrix
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = maxNeed[i][j] - allocation[i][j];
        }
    }

    bool finish[n] = {false};
    int safeSeq[n];
    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool possible = true;

                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        possible = false;
                        break;
                    }
                }

                if (possible)
                {
                    for (int j = 0; j < m; j++)
                        available[j] += allocation[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
        {
            cout << "\nSystem is NOT in Safe State.\n";
            return 0;
        }
    }

    cout << "\nSystem is in Safe State.\n";
    cout << "Safe Sequence: ";

    for (int i = 0; i < n; i++)
    {
        cout << "P" << safeSeq[i];
        if (i != n - 1)
            cout << " -> ";
    }

    cout << endl;

    return 0;
}
