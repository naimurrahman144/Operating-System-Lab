#include <bits/stdc++.h>
using namespace std;

struct Process
{
    int pid;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

// Input Function (Updated)
void inputProcesses(vector<Process> &processes)
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    processes.resize(n);

    for (int i = 0; i < n; i++)
    {
        processes[i].pid = i + 1;
    }

    // 👉 First take all Arrival Times
    cout << "Enter Arrival Times:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << processes[i].pid << ": ";
        cin >> processes[i].arrivalTime;
    }

    // 👉 Then take all Burst Times
    cout << "Enter Burst Times:\n";
    for (int i = 0; i < n; i++)
    {
        cout << "P" << processes[i].pid << ": ";
        cin >> processes[i].burstTime;
    }
}

// Sort
void sortByArrivalTime(vector<Process> &processes)
{
    sort(processes.begin(), processes.end(), [](Process a, Process b)
    {
        if (a.arrivalTime == b.arrivalTime)
            return a.pid < b.pid;
        return a.arrivalTime < b.arrivalTime;
    });
}

// FCFS
void calculateFCFS(vector<Process> &processes, float &avgWT, float &avgTAT)
{
    int currentTime = 0;
    int totalWT = 0, totalTAT = 0;

    for (int i = 0; i < processes.size(); i++)
    {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;

        currentTime = processes[i].completionTime;

        totalWT += processes[i].waitingTime;
        totalTAT += processes[i].turnaroundTime;
    }

    avgWT = (float) totalWT / processes.size();
    avgTAT = (float) totalTAT / processes.size();
}

// Output
void displayResults(const vector<Process> &processes, float avgWT, float avgTAT)
{
    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";

    for (auto p : processes)
    {
        cout << "P" << p.pid << "\t"
             << p.arrivalTime << "\t"
             << p.burstTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << endl;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << avgWT << endl;
    cout << "Average Turnaround Time: " << avgTAT << endl;
}

int main()
{
    vector<Process> processes;
    float avgWT = 0, avgTAT = 0;

    inputProcesses(processes);
    sortByArrivalTime(processes);
    calculateFCFS(processes, avgWT, avgTAT);
    displayResults(processes, avgWT, avgTAT);

    return 0;
}
