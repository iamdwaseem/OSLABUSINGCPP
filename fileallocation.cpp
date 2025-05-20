#include <iostream>
#include <vector>
#include <cstdlib>  // For rand()
#include <ctime>    // For time()

using namespace std;

vector<int> memory;  // Global memory vector to hold block status (0=free, 1=occupied)

void printMemory() {
    cout << "Current Memory Blocks (0=free, 1=occupied):" << endl;
    for (int i = 0; i < (int)memory.size(); i++) {
        cout << memory[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;  // Print 10 blocks per line for readability
    }
    cout << endl;
}

void contiguousAllocation(int startBlock, int length) {
    int n = memory.size();

    cout << "\nTrying Contiguous Allocation from block " << startBlock << " of length " << length << "...\n";

    if (startBlock + length > n) {
        cout << "Allocation failed: exceeds memory size." << endl;
        return;
    }

    // Check if blocks are free
    for (int i = startBlock; i < startBlock + length; i++) {
        if (memory[i] == 1) {
            cout << "Allocation failed: Block " << i << " already occupied." << endl;
            return;
        }
    }

    // Allocate blocks
    for (int i = startBlock; i < startBlock + length; i++) {
        memory[i] = 1;
    }
    cout << "Allocation successful (Contiguous)!" << endl;
}

void linkedAllocation(const vector<int>& blocks) {
    cout << "\nTrying Linked Allocation for blocks: ";
    for (auto b : blocks) cout << b << " ";
    cout << endl;

    int n = memory.size();

    for (int block : blocks) {
        if (block >= n) {
            cout << "Allocation failed: Block " << block << " out of memory range." << endl;
            return;
        }
        if (memory[block] == 1) {
            cout << "Allocation failed: Block " << block << " already occupied." << endl;
            return;
        }
    }

    // Allocate blocks
    for (int block : blocks) {
        memory[block] = 1;
    }

    cout << "Allocation successful (Linked)!" << endl;
}

void indexedAllocation(int indexBlock, const vector<int>& fileBlocks) {
    int n = memory.size();

    cout << "\nTrying Indexed Allocation with index block " << indexBlock << " and file blocks: ";
    for (auto b : fileBlocks) cout << b << " ";
    cout << endl;

    if (indexBlock >= n) {
        cout << "Allocation failed: Index block out of memory range." << endl;
        return;
    }
    if (memory[indexBlock] == 1) {
        cout << "Allocation failed: Index block already occupied." << endl;
        return;
    }

    for (int block : fileBlocks) {
        if (block >= n) {
            cout << "Allocation failed: Block " << block << " out of memory range." << endl;
            return;
        }
        if (memory[block] == 1) {
            cout << "Allocation failed: Block " << block << " already occupied." << endl;
            return;
        }
    }

    // Allocate index block and file blocks
    memory[indexBlock] = 1;
    for (int block : fileBlocks) {
        memory[block] = 1;
    }

    cout << "Allocation successful (Indexed)!" << endl;
}

int main() {
    srand(time(0));  // Seed random number generator

    int maxBlocks;
    cout << "Enter maximum number of memory blocks: ";
    cin >> maxBlocks;

    if (maxBlocks <= 0) {
        cout << "Memory size must be positive!" << endl;
        return 1;
    }

    // Initialize memory vector with random 0s and 1s (about 30% occupied)
    memory.resize(maxBlocks);
    for (int i = 0; i < maxBlocks; i++) {
        memory[i] = (rand() % 10 < 3) ? 1 : 0;  // ~30% chance occupied
    }

    printMemory();

    int choice;
    do {
        cout << "Choose file allocation method:\n";
        cout << "1. Contiguous Allocation\n2. Linked Allocation\n3. Indexed Allocation\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int startBlock, length;
            cout << "Enter start block and length of file: ";
            cin >> startBlock >> length;
            contiguousAllocation(startBlock, length);
            printMemory();
        }
        else if (choice == 2) {
            int numBlocks;
            cout << "Enter number of blocks for file: ";
            cin >> numBlocks;
            vector<int> blocks(numBlocks);
            cout << "Enter block numbers separated by space: ";
            for (int i = 0; i < numBlocks; i++) cin >> blocks[i];
            linkedAllocation(blocks);
            printMemory();
        }
        else if (choice == 3) {
            int indexBlock, numBlocks;
            cout << "Enter index block: ";
            cin >> indexBlock;
            cout << "Enter number of file blocks: ";
            cin >> numBlocks;
            vector<int> fileBlocks(numBlocks);
            cout << "Enter file block numbers separated by space: ";
            for (int i = 0; i < numBlocks; i++) cin >> fileBlocks[i];
            indexedAllocation(indexBlock, fileBlocks);
            printMemory();
        }
        else if (choice == 4) {
            cout << "Exiting program..." << endl;
        }
        else {
            cout << "Invalid choice, try again." << endl;
        }

    } while (choice != 4);

    return 0;
}
