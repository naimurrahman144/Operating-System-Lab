#include <bits/stdc++.h>
using namespace std;

struct Process {
    int pid, at, bt, ct, tat, wt;
    bool done = false;
};

struct Gantt {
    string name;
    int start, end;
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
    }
}

void SJF(vector<Process> &p, vector<Gantt> &g, double &avgWT, double &avgTAT) {
    int time = 0, completed = 0;
    int n = p.size();
    int totalWT = 0, totalTAT = 0;

    while (completed < n) {
        int idx = -1;

        // 👉 find shortest job
        for (int i = 0; i < n; i++) {
            if (!p[i].done && p[i].at <= time) {
                if (idx == -1 || p[i].bt < p[idx].bt)
                    idx = i;
            }
        }

        // 👉 idle case
        if (idx == -1) {
            int next = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!p[i].done)
                    next = min(next, p[i].at);
            }
            g.push_back({"Idle", time, next});
            time = next;
            continue;
        }

        int start = time;
        int end = start + p[idx].bt;

        p[idx].ct = end;
        p[idx].tat = end - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].done = true;

        g.push_back({"P" + to_string(p[idx].pid), start, end});

        totalWT += p[idx].wt;
        totalTAT += p[idx].tat;

        time = end;
        completed++;
    }

    avgWT = (double) totalWT / n;
    avgTAT = (double) totalTAT / n;
}

void printGantt(vector<Gantt> &g) {
    cout << "\nGantt Chart:\n";

    for (auto x : g)
        cout << "| " << x.name << " ";
    cout << "|\n";

    cout << g[0].start;
    for (auto x : g)
        cout << setw(6) << x.end;
    cout << endl;
}

void printTable(vector<Process> &p, double avgWT, double avgTAT) {
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for (auto x : p) {
        cout << x.pid << "\t"
             << x.at << "\t"
             << x.bt << "\t"
             << x.ct << "\t"
             << x.tat << "\t"
             << x.wt << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage WT = " << avgWT << endl;
    cout << "Average TAT = " << avgTAT << endl;
}

int main() {
    vector<Process> p;
    vector<Gantt> g;
    double avgWT = 0, avgTAT = 0;

    input(p);
    SJF(p, g, avgWT, avgTAT);
    printGantt(g);
    printTable(p, avgWT, avgTAT);

    return 0;
}
