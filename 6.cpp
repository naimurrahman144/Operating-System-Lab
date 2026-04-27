#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid, at, bt, rt, ct, tat, wt;
    bool done = false;
};

void input(vector<Process> &p) {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    p.resize(n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        cout << "AT of P" << p[i].pid << ": ";
        cin >> p[i].at;

        cout << "BT of P" << p[i].pid << ": ";
        cin >> p[i].bt;

        p[i].rt = p[i].bt;
    }
}

int getShortest(vector<Process> &p, int t) {
    int idx = -1;
    int mn = INT_MAX;

    for (int i = 0; i < p.size(); i++) {
        if (p[i].at <= t && p[i].rt > 0) {
            if (p[i].rt < mn) {
                mn = p[i].rt;
                idx = i;
            }
            else if (p[i].rt == mn && p[i].at < p[idx].at) {
                idx = i;
            }
        }
    }

    return idx;
}

void SRTF(vector<Process> &p) {
    int time = 0, done = 0;
    int n = p.size();

    while (done < n) {

        int idx = getShortest(p, time);

        if (idx == -1) {
            time++;   // CPU idle
            continue;
        }

        p[idx].rt--; // 1 unit execute
        time++;

        if (p[idx].rt == 0) {
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            done++;
        }
    }
}

void print(vector<Process> &p) {
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for (auto x : p) {
        cout << x.pid << "\t"
             << x.at << "\t"
             << x.bt << "\t"
             << x.ct << "\t"
             << x.tat << "\t"
             << x.wt << endl;
    }
}

int main() {
    vector<Process> p;

    input(p);
    SRTF(p);
    print(p);

    return 0;
}
