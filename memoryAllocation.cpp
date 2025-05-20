#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Block {
    int totalSize;
    int freeSpace;
    vector<int> pIds;  // IDs of processes
    bool isFree;
};

// Global variables
vector<Block> blocks;
int pIdCounter = 1;

void createBlocks(int numBlocks) {
    srand(time(0));  // Seed for randomness
    for (int i = 0; i < numBlocks; ++i) {
        int size = rand() % 150 + 50;  // Block size between 50 and 199
        Block b;
        b.totalSize = size;
        b.freeSpace = size;
        b.isFree = rand() % 3 != 0;  // 1 in 3 blocks are unavailable
        blocks.push_back(b);
    }
}

void displayBlocks() {
    cout << "\nMemory Blocks:\n";
    for (auto &b : blocks) {
        cout << "| ";
        if (b.pIds.empty())
            cout << "Free ";
        else
            for (int pid : b.pIds) cout << "P" << pid << " ";
        cout << "(Total: " << b.totalSize << ", Free: " << b.freeSpace << ", Available: " << (b.isFree ? "Yes" : "No") << ") ";
    }
    cout << "\n";
}

bool canFit(Block &b, int pSize) {
    return b.freeSpace >= pSize && b.isFree;
}

void allocateProcess(Block &b, int pSize) {
    b.pIds.push_back(pIdCounter++);
    b.freeSpace -= pSize;
}

void firstFit(int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        int pSize = rand() % 101 + 50;  // Process size 50-150
        cout << "Allocating Process " << pIdCounter << " of size " << pSize << endl;
        bool allocated = false;
        for (auto &b : blocks) {
            if (canFit(b, pSize)) {
                allocateProcess(b, pSize);
                cout << "Process allocated.\n";
                allocated = true;
                break;
            }
        }
        if (!allocated)
            cout << "No suitable block found!\n";
    }
    displayBlocks();
}

void bestFit(int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        int pSize = rand() % 101 + 50;
        cout << "Allocating Process " << pIdCounter << " of size " << pSize << endl;
        int bestIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (canFit(blocks[j], pSize)) {
                if (bestIdx == -1 || blocks[j].freeSpace < blocks[bestIdx].freeSpace) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocateProcess(blocks[bestIdx], pSize);
            cout << "Process allocated.\n";
        } else {
            cout << "No suitable block found!\n";
        }
    }
    displayBlocks();
}

void worstFit(int numProcesses) {
    for (int i = 0; i < numProcesses; i++) {
        int pSize = rand() % 101 + 50;
        cout << "Allocating Process " << pIdCounter << " of size " << pSize << endl;
        int worstIdx = -1;
        for (int j = 0; j < blocks.size(); j++) {
            if (canFit(blocks[j], pSize)) {
                if (worstIdx == -1 || blocks[j].freeSpace > blocks[worstIdx].freeSpace) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocateProcess(blocks[worstIdx], pSize);
            cout << "Process allocated.\n";
        } else {
            cout << "No suitable block found!\n";
        }
    }
    displayBlocks();
}

int main() {
    int numBlocks;
    cout << "Enter number of memory blocks: ";
    cin >> numBlocks;

    createBlocks(numBlocks);
    displayBlocks();

    while (true) {
        cout << "\n--- Memory Allocation Menu ---\n";
        cout << "1. First Fit\n";
        cout << "2. Best Fit\n";
        cout << "3. Worst Fit\n";
        cout << "4. Display Blocks\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        int choice;
        cin >> choice;

        if (choice == 5) {
            cout << "Exiting...\n";
            break;
        }

        int numProcesses;
        switch (choice) {
            case 1:
                cout << "Enter number of processes: ";
                cin >> numProcesses;
                firstFit(numProcesses);
                break;
            case 2:
                cout << "Enter number of processes: ";
                cin >> numProcesses;
                bestFit(numProcesses);
                break;
            case 3:
                cout << "Enter number of processes: ";
                cin >> numProcesses;
                worstFit(numProcesses);
                break;
            case 4:
                displayBlocks();
                break;
            default:
                cout << "Invalid choice!\n";
        }
    }

    return 0;
}
\