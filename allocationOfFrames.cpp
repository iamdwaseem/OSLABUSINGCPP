#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Fixed Allocation Function
void fixed(vector<int> p, int f) {
    int n = p.size();
    vector<string> fr(f, "E");  // Initialize all frames as "E" (empty)
    int framesPerProcess = f / n;
    int index = 0;

    for (int i = 0; i < n; i++) {
        int alloc = min(framesPerProcess, p[i]);
        for (int j = 0; j < alloc && index < f; j++) {
            fr[index++] = "P" + to_string(i + 1); // Allocate frame to process
        }
        index += (framesPerProcess - alloc); // Skip if not enough allocation
    }

    cout << "Fixed Allocation:\n";
    for (int i = 0; i < f; i++) {
        cout << fr[i] << " ";
    }
    cout << "\n\n";
}

// Proportional Allocation Function
void proportional(vector<int> p, int f) {
    int n = p.size();
    vector<string> fr(f, "E");
    int sum = 0;

    for (int size : p) {
        sum += size;
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        int alloc = round(((double)p[i] / sum) * f);
        alloc = min(alloc, p[i]);  // Don't allocate more than needed
        for (int j = 0; j < alloc && index < f; j++) {
            fr[index++] = "P" + to_string(i + 1);
        }
    }

    cout << "Proportional Allocation:\n";
    for (int i = 0; i < f; i++) {
        cout << fr[i] << " ";
    }
    cout << "\n\n";
}

// Main Function
int main() {
    int n;
    cout << "Enter number of processes:\n";
    cin >> n;

    vector<int> p(n);
    cout << "Enter size of each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    int f;
    cout << "Enter total number of frames:\n";
    cin >> f;

    int op;
    do {
        cout << "Enter option:\n1. Fixed Allocation\n2. Proportional Allocation\n3. Exit\n";
        cin >> op;

        switch (op) {
            case 1:
                fixed(p, f);
                break;
            case 2:
                proportional(p, f);
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (op != 3);

    return 0;
}
