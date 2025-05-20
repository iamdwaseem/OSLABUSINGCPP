#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, m;
    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter number of resources: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<vector<int>> need(n, vector<int>(m));
    vector<int> totalInstances(m);
    vector<int> available(m);

    // Input total instances of each resource
    cout << "\nEnter total instances of each resource:\n";
    for (int j = 0; j < m; j++) {
        cout << "Resource " << j << ": ";
        cin >> totalInstances[j];
    }

    // Input Allocation Matrix
    cout << "\nEnter Allocation Matrix (process-wise):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    // Input Max Matrix and compute Need Matrix
    cout << "\nEnter Max Need Matrix (process-wise):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Calculate Available = Total - Allocated
    for (int j = 0; j < m; j++) {
        int allocatedSum = 0;
        for (int i = 0; i < n; i++) {
            allocatedSum += allocation[i][j];
        }
        available[j] = totalInstances[j] - allocatedSum;
    }

    // Display Need Matrix
    cout << "\nNeed Matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < m; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    // Safety Algorithm
    vector<bool> finished(n, false);
    vector<int> work = available;
    vector<int> safeSequence;

    cout << "\nAvailable Resources at start: ";
    for (int j = 0; j < m; j++) {
        cout << work[j] << " ";
    }
    cout << endl;

    while (safeSequence.size() < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finished[i]) {
                bool canExecute = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence.push_back(i);
                    finished[i] = true;
                    found = true;

                    cout << "Process P" << i << " has finished. Available: [";
                    for (int j = 0; j < m; j++) {
                        cout << work[j];
                        if (j < m - 1) cout << ", ";
                    }
                    cout << "]" << endl;
                }
            }
        }
        if (!found) break;
    }

    // Final Safe Sequence Output
    if (safeSequence.size() == n) {
        cout << "\nSystem is in SAFE state.\nSafe Sequence: ";
        for (int i = 0; i < n; i++) {
            cout << "P" << safeSequence[i];
            if (i < n - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "\nSystem is NOT in a safe state." << endl;
    }

    return 0;
}
