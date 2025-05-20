#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void fifoPageReplacement(vector<int> pages, int capacity) {
    queue<int> memory;
    vector<bool> present(100, false); // Assuming page numbers <= 99
    int faults = 0;

    for (int page : pages) {
        if (!present[page]) {
            if (memory.size() == capacity) {
                int old = memory.front();
                memory.pop();
                present[old] = false;
            }
            memory.push(page);
            present[page] = true;
            faults++;
        }
    }

    cout << "Total Page Faults (FIFO): " << faults << endl;
}

void lruPageReplacement(vector<int> pages, int capacity) {
    list<int> memory;
    int faults = 0;

    for (int page : pages) {
        auto it = find(memory.begin(), memory.end(), page);
        if (it == memory.end()) {
            if (memory.size() == capacity) {
                memory.pop_back();
            }
            faults++;
        } else {
            memory.erase(it);
        }
        memory.push_front(page);
    }

    cout << "Total Page Faults (LRU): " << faults << endl;
}

int predict(vector<int> pages, unordered_set<int> &frames, int index) {
    int farthest = index, res = -1;

    for (int page : frames) {
        int i;
        for (i = index; i < pages.size(); i++) {
            if (pages[i] == page) {
                if (i > farthest) {
                    farthest = i;
                    res = page;
                }
                break;
            }
        }
        if (i == pages.size()) return page; // Not used again
    }
    return res;
}

void optimalPageReplacement(vector<int> pages, int capacity) {
    unordered_set<int> frames;
    int faults = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (frames.find(pages[i]) == frames.end()) {
            if (frames.size() == capacity) {
                int pageToReplace = predict(pages, frames, i + 1);
                frames.erase(pageToReplace);
            }
            frames.insert(pages[i]);
            faults++;
        }
    }

    cout << "Total Page Faults (Optimal): " << faults << endl;
}

int main() {
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3}; // Sample reference string
    int capacity = 3;

    fifoPageReplacement(pages, capacity);
    lruPageReplacement(pages, capacity);
    optimalPageReplacement(pages, capacity);

    return 0;
}
