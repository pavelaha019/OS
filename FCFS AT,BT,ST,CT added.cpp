#include<bits/stdc++.h>
using namespace std;

struct Process {
    int id, at, bt, st, ct;
};

bool comp(struct Process p1, struct Process p2) {
    return p1.at < p2.at;
}

void printProcess(struct Process p[], int n) {
    cout << "ID\tAT\tBT\n";
    for(int i=0; i<n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << endl;
    }
}

void printTable(struct Process p[], int n) {
    cout << "ID\tAT\tBT\tST\tCT" << endl;
    for(int i=0; i<n; i++) {
        cout << p[i].id << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].st << "\t" << p[i].ct << endl;
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    int n; // Assuming 'n' is defined and read from input
    cin >> n;
    struct Process p[n]; // Assuming 'p' is defined and read from input

    // Sorting processes based on arrival time
    sort(p, p + n, comp);

    // Printing the process details
    printProcess(p, n);

    /**
     * Calculating GANTT chart
    */
    for(int i=0; i<n; i++) {
        if(i == 0) {
            p[i].st = p[i].at;
            p[i].ct = p[i].st + p[i].bt;
        } else {
            p[i].st = max(p[i-1].ct, p[i].at);
            p[i].ct = p[i].st + p[i].bt;
        }
    }

    // Printing the table
    printTable(p, n);

    return 0;
}
