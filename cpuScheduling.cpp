#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Process {
    int pid, at, bt, wt, tat, st, ct, rt, priority;
};

// Utility to sort by arrival time
bool cmpAT(const Process &a, const Process &b) {
    return a.at < b.at;
}

// FCFS
void fcfs(vector<Process> p) {
    sort(p.begin(), p.end(), cmpAT);
    int time = 0;
    cout << "\nFCFS Scheduling:\n";
    cout << "PID\tAT\tBT\tWT\tTAT\n";

    for (auto &proc : p) {
        proc.st = max(time, proc.at);
        proc.wt = proc.st - proc.at;
        proc.ct = proc.st + proc.bt;
        proc.tat = proc.ct - proc.at;
        time = proc.ct;
        cout << "P" << proc.pid << "\t" << proc.at << "\t" << proc.bt << "\t" << proc.wt << "\t" << proc.tat << "\n";
    }

    cout << "Gantt Chart:\n";
    for (auto &proc : p)
        cout << "| P" << proc.pid << " ";
    cout << "|\n";
}

// SJF Non-Preemptive
void sjf_np(vector<Process> p) {
    int n = p.size();
    vector<bool> done(n, false);
    int completed = 0, time = 0;
    cout << "\nSJF Non-Preemptive Scheduling:\n";
    cout << "PID\tAT\tBT\tWT\tTAT\n";

    while (completed < n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; ++i) {
            if (!done[i] && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            p[idx].st = time;
            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            time = p[idx].ct;
            done[idx] = true;
            completed++;
            cout << "P" << p[idx].pid << "\t" << p[idx].at << "\t" << p[idx].bt << "\t" << p[idx].wt << "\t" << p[idx].tat << "\n";
        }
    }
}

// SJF Preemptive
void sjf_p(vector<Process> p) {
    int n = p.size();
    vector<int> rt(n);
    for (int i = 0; i < n; ++i) rt[i] = p[i].bt;

    int completed = 0, time = 0;
    vector<bool> started(n, false);
    cout << "\nSJF Preemptive Scheduling:\n";
    cout << "PID\tAT\tBT\tWT\tTAT\n";

    while (completed < n) {
        int idx = -1, min_bt = 1e9;
        for (int i = 0; i < n; ++i) {
            if (p[i].at <= time && rt[i] > 0 && rt[i] < min_bt) {
                min_bt = rt[i];
                idx = i;
            }
        }
        if (idx != -1) {
            if (!started[idx]) {
                p[idx].st = time;
                started[idx] = true;
            }
            rt[idx]--;
            if (rt[idx] == 0) {
                p[idx].ct = time + 1;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        }
        time++;
    }

    for (int i = 0; i < n; ++i) {
        cout << "P" << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].wt << "\t" << p[i].tat << "\n";
    }
}

// Priority Non-Preemptive
void priority_np(vector<Process> p) {
    int n = p.size();
    vector<bool> done(n, false);
    int completed = 0, time = 0;
    cout << "\nPriority Non-Preemptive Scheduling:\n";
    cout << "PID\tAT\tBT\tPR\tWT\tTAT\n";

    while (completed < n) {
        int idx = -1, best = 1e9;
        for (int i = 0; i < n; ++i) {
            if (!done[i] && p[i].at <= time && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }
        if (idx == -1) time++;
        else {
            p[idx].st = time;
            p[idx].ct = time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            time = p[idx].ct;
            done[idx] = true;
            completed++;
            cout << "P" << p[idx].pid << "\t" << p[idx].at << "\t" << p[idx].bt << "\t" << p[idx].priority << "\t" << p[idx].wt << "\t" << p[idx].tat << "\n";
        }
    }
}

// Priority Preemptive
void priority_p(vector<Process> p) {
    int n = p.size();
    vector<int> rt(n);
    for (int i = 0; i < n; ++i) rt[i] = p[i].bt;

    int completed = 0, time = 0;
    vector<bool> started(n, false);
    cout << "\nPriority Preemptive Scheduling:\n";
    cout << "PID\tAT\tBT\tPR\tWT\tTAT\n";

    while (completed < n) {
        int idx = -1, best = 1e9;
        for (int i = 0; i < n; ++i) {
            if (p[i].at <= time && rt[i] > 0 && p[i].priority < best) {
                best = p[i].priority;
                idx = i;
            }
        }
        if (idx != -1) {
            if (!started[idx]) {
                p[idx].st = time;
                started[idx] = true;
            }
            rt[idx]--;
            if (rt[idx] == 0) {
                p[idx].ct = time + 1;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                completed++;
            }
        }
        time++;
    }

    for (int i = 0; i < n; ++i) {
        cout << "P" << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].priority << "\t" << p[i].wt << "\t" << p[i].tat << "\n";
    }
}

// Round Robin Scheduling
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Process {
    int pid, at, bt, st, ct, tat, wt;
};

void round_robin(vector<Process>& p, int quantum) {
    int n = p.size();
    vector<int> rt(n);                     // Remaining time
    for (int i = 0; i < n; ++i)
        rt[i] = p[i].bt;

    queue<int> q;
    vector<bool> in_queue(n, false);
    vector<bool> started(n, false);
    int time = 0, completed = 0;

    cout << "\nRound Robin Scheduling (Quantum = " << quantum << "):\n";
    cout << "PID\tAT\tBT\tWT\tTAT\n";

    while (completed < n) {
        // Add arrived processes to queue
        for (int i = 0; i < n; ++i)
            if (p[i].at <= time && rt[i] > 0 && !in_queue[i])
                q.push(i), in_queue[i] = true;

        if (q.empty()) {
            time++;  // If no process is ready, move time forward
            continue;
        }

        int i = q.front(); q.pop();

        if (!started[i])
            p[i].st = time, started[i] = true;

        int run_time = min(quantum, rt[i]);
        rt[i] -= run_time;
        time += run_time;

        // Add new processes that have arrived during this time
        for (int j = 0; j < n; ++j)
            if (p[j].at <= time && rt[j] > 0 && !in_queue[j])
                q.push(j), in_queue[j] = true;

        if (rt[i] > 0)
            q.push(i);  // Not done yet, put back
        else {
            p[i].ct = time;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = p[i].tat - p[i].bt;
            completed++;
        }
    }

    // Print results
    for (auto& pr : p)
        cout << "P" << pr.pid << "\t" << pr.at << "\t" << pr.bt << "\t" << pr.wt << "\t" << pr.tat << "\n";
}


int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    srand(time(0));
    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].pid = i + 1;
        p[i].bt = rand() % 10 + 1;
        p[i].at = rand() % 6;
        p[i].priority = rand() % 5 + 1;
    }

    fcfs(p);
    sjf_np(p);
    sjf_p(p);
    priority_np(p);
    priority_p(p);
    round_robin(p, 3); // Quantum can be modified here

    return 0;
}
