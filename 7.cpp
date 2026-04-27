#include <bits/stdc++.h>
using namespace std;

struct Process{
    int pid, at, bt, rt, ct, tat, wt;
};

struct Gantt{
    string name;
    int start, end;
};

void input(vector<Process> &p){
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    p.resize(n);

    for(int i=0;i<n;i++){
        p[i].pid = i+1;

        cout << "AT of P" << p[i].pid << ": ";
        cin >> p[i].at;

        cout << "BT of P" << p[i].pid << ": ";
        cin >> p[i].bt;

        p[i].rt = p[i].bt;
    }
}

void RoundRobin(vector<Process> &p, int tq, vector<Gantt> &g){
    int time = 0, done = 0;
    int n = p.size();
    queue<int> q;
    vector<bool> inQueue(n,false);

    while(done < n){

        // add processes to queue
        for(int i=0;i<n;i++){
            if(!inQueue[i] && p[i].at <= time && p[i].rt > 0){
                q.push(i);
                inQueue[i] = true;
            }
        }

        // idle condition
        if(q.empty()){
            int next = INT_MAX;

            for(int i=0;i<n;i++){
                if(p[i].rt > 0)
                    next = min(next, p[i].at);
            }

            if(next == INT_MAX) break;

            if(time < next){
                g.push_back({"Idle", time, next});
                time = next;
            }
            continue;
        }

        int idx = q.front();
        q.pop();
        inQueue[idx] = false;

        int start = time;
        int run = min(tq, p[idx].rt);

        time += run;
        p[idx].rt -= run;

        g.push_back({"P" + to_string(p[idx].pid), start, time});

        // add newly arrived processes
        for(int i=0;i<n;i++){
            if(!inQueue[i] && p[i].at <= time && p[i].rt > 0){
                q.push(i);
                inQueue[i] = true;
            }
        }

        // requeue or finish
        if(p[idx].rt > 0){
            q.push(idx);
            inQueue[idx] = true;
        }
        else{
            done++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
        }
    }
}

void printGantt(vector<Gantt> &g){
    cout << "\nGantt Chart:\n";

    for(auto x : g)
        cout << "| " << x.name << " ";

    cout << "|\n";

    if(!g.empty()){
        cout << g[0].start;
        for(auto x : g)
            cout << setw(6) << x.end;
        cout << "\n";
    }
}

void printResult(vector<Process> &p){
    double wt = 0, tat = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for(auto x : p){
        cout << x.pid << "\t"
             << x.at << "\t"
             << x.bt << "\t"
             << x.ct << "\t"
             << x.tat << "\t"
             << x.wt << "\n";

        wt += x.wt;
        tat += x.tat;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage WT = " << wt / p.size();
    cout << "\nAverage TAT = " << tat / p.size() << "\n";
}

int main(){
    vector<Process> p;
    vector<Gantt> g;
    int tq;

    input(p);

    cout << "Enter time quantum: ";
    cin >> tq;

    RoundRobin(p, tq, g);
    printGantt(g);
    printResult(p);

    return 0;
}
