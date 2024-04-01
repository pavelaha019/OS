#include<iostream>
using namespace std;

int main()
{
    int n = 5; // Number of processes
    int r = 3; // Number of resource types

    // Allocation matrix
    int alloc[5][3] = {{0, 0, 1},
                       {3, 0, 0},
                       {1, 0, 1},
                       {2, 3, 2},
                       {0, 0, 3}};

    // Maximum matrix
    int max[5][3] = {{7, 6, 3},
                     {3, 2, 2},
                     {8, 0, 2},
                     {2, 1, 2},
                     {5, 2, 3}};

    // Available resources
    int avail[3] = {2, 3, 2};

    // Need matrix
    int need[n][r];
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize finish array
    int f[n];
    for(int i = 0; i < n; i++) {
        f[i] = 0;
    }

    // Initialize ans array for safe sequence
    int ans[n], ind = 0;

    // Find safe sequence
    for(int k = 0; k < n; k++) {
        for(int i = 0; i < n; i++) {
            if(f[i] == 0) {
                int flag = 0;
                for(int j = 0; j < r; j++) {
                    if(need[i][j] > avail[j]) {
                        flag = 1;
                        break;
                    }
                }
                if(flag == 0) {
                    ans[ind++] = i; // Store process number in ans
                    for(int y = 0; y < r; y++) {
                        avail[y] += alloc[i][y];
                    }
                    f[i] = 1;
                }
            }
        }
    }

    // Print the safe sequence
    cout << "The safe sequence is: ";
    for(int i = 0; i < n; i++) {
        cout << "p" << ans[i];
        if(i != n - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    return 0;
}
