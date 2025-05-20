
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void fcfs(vector<int> requests, int head) {
    cout << "\nFCFS Disk Scheduling:\n";
    int seek = 0;
    for (int r : requests) {
        seek += abs(r - head);
        head = r;
    }
    cout << "Total Seek Time: " << seek << "\n";
}

void sstf(vector<int> requests, int head) {
    cout << "\nSSTF Disk Scheduling:\n";
    int seek = 0;
    vector<bool> visited(requests.size(), false);

    for (int i = 0; i < requests.size(); ++i) {
        int idx = -1, min_dist = 1e9;
        for (int j = 0; j < requests.size(); ++j) {
            if (!visited[j] && abs(requests[j] - head) < min_dist) {
                min_dist = abs(requests[j] - head);
                idx = j;
            }
        }
        seek += min_dist;
        head = requests[idx];
        visited[idx] = true;
    }

    cout << "Total Seek Time: " << seek << "\n";
}

void scan(vector<int> requests, int head, int max_cyl, bool direction_up) {
    cout << "\nSCAN Disk Scheduling:\n";
    int seek = 0;
    vector<int> left, right;

    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    if (direction_up) {
        for (int r : right) {
            seek += abs(head - r);
            head = r;
        }
        seek += abs(head - max_cyl);
        head = max_cyl;
        for (int i = left.size() - 1; i >= 0; --i) {
            seek += abs(head - left[i]);
            head = left[i];
        }
    } else {
        for (int i = left.size() - 1; i >= 0; --i) {
            seek += abs(head - left[i]);
            head = left[i];
        }
        seek += abs(head - 0);
        head = 0;
        for (int r : right) {
            seek += abs(head - r);
            head = r;
        }
    }

    cout << "Total Seek Time: " << seek << "\n";
}

void cscan(vector<int> requests, int head, int max_cyl) {
    cout << "\nC-SCAN Disk Scheduling:\n";
    int seek = 0;
    vector<int> left, right;

    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) {
        seek += abs(head - r);
        head = r;
    }

    if (!left.empty()) {
        seek += abs(head - max_cyl);
        seek += max_cyl;
        head = 0;
        for (int r : left) {
            seek += abs(head - r);
            head = r;
        }
    }

    cout << "Total Seek Time: " << seek << "\n";
}

void look(vector<int> requests, int head, bool direction_up) {
    cout << "\nLOOK Disk Scheduling:\n";
    int seek = 0;
    vector<int> left, right;

    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }
    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    if (direction_up) {
        for (int r : right) {
            seek += abs(head - r);
            head = r;
        }
        for (int i = left.size() - 1; i >= 0; --i) {
            seek += abs(head - left[i]);
            head = left[i];
        }
    } else {
        for (int i = left.size() - 1; i >= 0; --i) {
            seek += abs(head - left[i]);
            head = left[i];
        }
        for (int r : right) {
            seek += abs(head - r);
            head = r;
        }
    }

    cout << "Total Seek Time: " << seek << "\n";
}

void clook(vector<int> requests, int head) {
    cout << "\nC-LOOK Disk Scheduling:\n";
    int seek = 0;
    vector<int> left, right;

    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    for (int r : right) {
        seek += abs(head - r);
        head = r;
    }

    if (!left.empty()) {
        seek += abs(head - left[0]);
        head = left[0];
        for (int i = 1; i < left.size(); ++i) {
            seek += abs(head - left[i]);
            head = left[i];
        }
    }

    cout << "Total Seek Time: " << seek << "\n";
}

int main() {
    vector<int> requests = {98, 183, 37, 122, 14, 124, 65, 67};
    int head = 53, max_cyl = 199;

    fcfs(requests, head);
    sstf(requests, head);
    scan(requests, head, max_cyl, true);
    cscan(requests, head, max_cyl);
    look(requests, head, true);
    clook(requests, head);
    return 0;
}
