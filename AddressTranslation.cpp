#include <iostream>
#include <vector>
using namespace std;

int main() {
    int numberOfPages, pageSize, logicalAddress;
    vector<int> pageTable(100, -1); // Max 100 pages, default -1 (not in memory)

    cout << "Enter number of pages (max 100): ";
    cin >> numberOfPages;

    cout << "Enter page size (in bytes): ";
    cin >> pageSize;

    cout << "Enter the frame number for each page (-1 if page not in memory):\n";
    for (int page = 0; page < numberOfPages; page++) {
        cout << "Page " << page << " -> Frame: ";
        cin >> pageTable[page];
    }

    cout << "Enter a logical address (0 - " << (numberOfPages * pageSize - 1) << "): ";
    cin >> logicalAddress;

    int pageNumber = logicalAddress / pageSize;
    int offset = logicalAddress % pageSize;

    if (pageNumber >= numberOfPages) {
        cout << "Invalid logical address! Page number " << pageNumber << " is out of bounds." << endl;
        return 0;
    }

    if (pageTable[pageNumber] == -1) {
        cout << "Page fault! Page " << pageNumber << " is not in memory." << endl;
        return 0;
    }

    int frameNumber = pageTable[pageNumber];
    int physicalAddress = frameNumber * pageSize + offset;

    cout << "\n--- Address Translation ---" << endl;
    cout << "Logical Address: " << logicalAddress << endl;
    cout << "Page Number: " << pageNumber << endl;
    cout << "Offset: " << offset << endl;
    cout << "Mapped to Frame: " << frameNumber << endl;
    cout << "Physical Address: " << physicalAddress << endl;

    return 0;
}
