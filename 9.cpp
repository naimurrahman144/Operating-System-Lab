#include <bits/stdc++.h>
using namespace std;

void input(vector<vector<int>> &a, int n, int m, string name)
{
    cout << "Enter " << name << " matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> a[i][j];
}

bool isSafe(vector<vector<int>> &alloc, vector<vector<int>> &mx,
            vector<int> avail, vector<int> &safe)
{
    int n = alloc.size();
    int m = avail.size();

    vector<vector<int>> need(n, vector<int>(m));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = mx[i][j] - alloc[i][j];

    vector<bool> finish(n, false);
    safe.clear();

    int count = 0;

    while (count < n)
    {
        bool found = false;

        for (int i = 0; i < n; i++)
        {
            if (finish[i]) continue;

            bool ok = true;

            for (int j = 0; j < m; j++)
            {
                if (need[i][j] > avail[j])
                {
                    ok = false;
                    break;
                }
            }

            if (ok)
            {
                for (int j = 0; j < m; j++)
                    avail[j] += alloc[i][j];

                safe.push_back(i);
                finish[i] = true;
                found = true;
                count++;
            }
        }

        if (!found)
            return false;
    }

    return true;
}

int main()
{
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> mx(n, vector<int>(m));
    vector<int> avail(m), safe;

    input(alloc, n, m, "Allocation");
    input(mx, n, m, "Maximum");

    cout << "Enter Available resources:\n";
    for (int i = 0; i < m; i++)
        cin >> avail[i];

    if (isSafe(alloc, mx, avail, safe))
    {
        cout << "\nSystem is SAFE\nSafe sequence: ";

        for (int i = 0; i < safe.size(); i++)
        {
            cout << "P" << safe[i];
            if (i != safe.size() - 1)
                cout << " -> ";
        }
        cout << "\n";
    }
    else
    {
        cout << "\nSystem is NOT SAFE\n";
    }

    return 0;
}
