#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id, at, rt, bt, st = -1, ct, wt = 0, tt, idle_t;
    bool pushed = false;
};

void printProcess(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        cout << p[i].id << " " << p[i].at << " " << p[i].bt << endl;
    }
}

void printTable(struct Process p[], int n, int id) {
    cout << "ID\tAT\tBT\tST\tCT\tWT\tTT" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].st << "\t" << p[i].ct << "\t" << p[i].wt << "\t" << p[i].tt << endl;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        cin >> p[i].id >> p[i].at >> p[i].bt;
        p[i].rt = p[i].bt;
    }
    printProcess(p, n);

    // ROUND ROBIN IMPLEMENTATION
    int tq = 5; // Time Quantum
    int minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].at < p[minIndex].at)
            minIndex = i;
    }
    vector<struct Process *> ready_queue;
    ready_queue.push_back(&p[minIndex]);
    p[minIndex].pushed = true;
    int t = p[minIndex].at, count = 0;
    while (count != n) {
        struct Process *selected = ready_queue.front();
        ready_queue.erase(ready_queue.begin());
        if (selected->rt <= tq) { // when bt <= tq
                                  // Execute till completion
            if (selected->st == -1) {
                selected->st = t;
            }
            selected->ct = t + selected->rt;
            selected->wt += (t - selected->st); // Update waiting time
            t = selected->ct;
            count++;
        } else { // rt > tq
                 // Execute for time quantum
            if (selected->st == -1) {
                selected->st = t;
            }
            selected->ct = t + tq;
            selected->rt -= tq; // present remaining time
            selected->wt += (t - selected->st); // Update waiting time
            t = selected->ct;

            // Push processes that have arrived and not pushed into the ready queue
            for (int i = 0; i < n; i++) {
                if (!p[i].pushed && p[i].at <= t) {
                    ready_queue.push_back(&p[i]);
                    p[i].pushed = true;
                }
            }

            if (selected->rt > 0) {
                // Push the current process back to the ready queue
                ready_queue.push_back(selected);
            } else {
                count++;
            }
        }
    }

    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        p[i].tt = p[i].ct - p[i].at;
    }

    printTable(p, n, 0);

    return 0;
}
