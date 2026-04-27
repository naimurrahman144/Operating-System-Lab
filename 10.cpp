#include <bits/stdc++.h>
using namespace std;

void inputMatrix(vector<vector<int>> &a, int n, int m, string name){
    cout << "Enter " << name << " matrix:\n";
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> a[i][j];
        }
    }
}

void inputVector(vector<int> &v, string name){
    cout << "Enter " << name << " vector:\n";
    for(int i=0;i<v.size();i++){
        cin >> v[i];
    }
}

void detect(vector<vector<int>> &alloc, vector<vector<int>> &req, vector<int> avail){
    int n = alloc.size();
    int m = avail.size();

    vector<bool> finish(n,false);
    vector<int> work = avail;

    // jader allocation nai tader finish true
    for(int i=0;i<n;i++){
        bool zero = true;
        for(int j=0;j<m;j++){
            if(alloc[i][j] != 0){
                zero = false;
                break;
            }
        }
        if(zero) finish[i] = true;
    }

    while(true){
        bool found = false;

        for(int i=0;i<n;i++){
            if(finish[i]) continue;

            bool ok = true;
            for(int j=0;j<m;j++){
                if(req[i][j] > work[j]){
                    ok = false;
                    break;
                }
            }

            if(ok){
                for(int j=0;j<m;j++){
                    work[j] += alloc[i][j];
                }
                finish[i] = true;
                found = true;
            }
        }

        if(!found) break;
    }

    // deadlock check
    vector<int> dead;

    for(int i=0;i<n;i++){
        if(!finish[i]){
            dead.push_back(i);
        }
    }

    if(dead.empty()){
        cout << "\nNo deadlock detected.\n";
    }else{
        cout << "\nDeadlock detected in processes: ";
        for(int i=0;i<dead.size();i++){
            cout << "P" << dead[i];
            if(i != dead.size()-1)
                cout << ", ";
        }
        cout << "\n";
    }
}

int main(){
    int n,m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    vector<vector<int>> alloc(n, vector<int>(m));
    vector<vector<int>> req(n, vector<int>(m));
    vector<int> avail(m);

    inputMatrix(alloc,n,m,"Allocation");
    inputMatrix(req,n,m,"Request");
    inputVector(avail,"Available");

    detect(alloc,req,avail);

    return 0;
}
