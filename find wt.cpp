#include<bits/stdc++.h>
using namespace std;

struct process {
    int PID;
    int AT;
    int BT;
    int CT;
    int TT;
    int WT;
};

void findCT(process proc[], int n) {
    proc[0].CT = proc[0].AT + proc[0].BT;
    for (int i = 1; i < n; i++) {
        proc[i].CT = max(proc[i].AT, proc[i - 1].CT) + proc[i].BT;
    }
}

void findTT_WT(process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].TT = proc[i].CT - proc[i].AT;
        proc[i].WT = proc[i].TT - proc[i].BT;
    }
}

void findFCFS(process proc[], int n) {
    findCT(proc, n);
    findTT_WT(proc, n);
}

void printFCFS(process proc[], int n) {
    cout << "FCFS SCHEDULE: " << endl;
    cout << "PID\t AT\t BT\t CT\t TT\t WT" << endl;
    for (int i = 0; i < n; i++) {
        cout << proc[i].PID << "\t" << proc[i].AT << "\t" << proc[i].BT << "\t" 
             << proc[i].CT << "\t" << proc[i].TT << "\t" << proc[i].WT << endl;
    }
}

int main() {
    int n = 5;
    process proc[n] = {{1, 0, 5}, {2, 1, 3}, {3, 2, 2}, {4, 3, 4}, {5, 4, 1}};
    findFCFS(proc, n);
    printFCFS(proc, n);
    return 0;
}
