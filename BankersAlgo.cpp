#include<iostream>
using namespace std;
const int P = 5;const int R = 3;
void calculateNeed(int need[P][R], int maxm[P][R], int allot[P][R])
{   for (int i = 0 ; i < P ; i++)
        for (int j = 0 ; j < R ; j++)
            need[i][j] = maxm[i][j] - allot[i][j];
}
bool isSafe(int processes[], int avail[], int maxm[][R], int allot[][R])
{   int need[P][R], safeSeq[P], work[R];
    calculateNeed(need, maxm, allot);
    bool finish[P] = {false};
    for (int i = 0; i < R ; i++)
        work[i] = avail[i];
    for (int i = 0; i < R ; i++)
        cout<<work[i];
    cout<<"\n";
    int count = 0;
    while (count < P)
    {
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            if (finish[p] == false)
            {
                int j;
                for (j = 0; j < R; j++){
                    if (need[p][j] > work[j]){
                        break;
                    }
                }
                if (j == R)
                {
                    for (int k = 0 ; k < R ; k++)
                        work[k] += allot[p][k];

                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (found == false)
        {
            cout << "System is not in safe state";
            return false;
        }
    }
    cout << "System is in safe state.\nSafe sequence is: ";
    for (int i = 0; i < P ; i++)
        cout << safeSeq[i] << " ";
    cout << endl;
    return true;
}
void resourceRequest(int processes[], int avail[], int maxm[][R], int allot[][R], int need[][R], int request[], int p)
{
    int i = 0, j = 0;
    for (; i < R; i++)
        if (request[i] > need[p][i])
            break;
    if (i == R){
        for (i = 0; i < R; i++)
            if (request[i] > avail[i])
                break;
        if (i == R){
            for (i = 0; i < R; i++){
                avail[i] -= request[i];
                allot[p][i] += request[i];
                need[p][i] -= request[i];
            }
            if (isSafe(processes, avail, maxm, allot)){
                //print allot need avail
                cout << "Process\tAllocation\tMax\t\tNeed\t\tAvailable" << endl;
                cout << "\tR1 R2 R3 \tR1 R2 R3\t R1 R2 R3\t R1 R2 R3" << endl;
                cout << "0\t " << allot[0][0] << "  " << allot[0][1] << "  " << allot[0][2] << "\t " << maxm[0][0] << "  " << maxm[0][1] << "  " << maxm[0][2] << "\t " << need[0][0] << "  " << need[0][1] << "  " << need[0][2] << "\t " << avail[0] << "  " << avail[1] << "  " << avail[2] << "\n";
                for (i = 1; i < P; i++){
                    cout << i << "\t " << allot[i][0] << "  " << allot[i][1] << "  " << allot[i][2] << "\t " << maxm[i][0] << "  " << maxm[i][1] << "  " << maxm[i][2] << "\t " << need[i][0] << "  " << need[i][1] << "  " << need[i][2] << endl;
                }
            }
            else{
                cout << "\nThe new state is unsafe, process must wait." << endl;
                for (i = 0; i < R; i++){
                    avail[i] += request[i];
                    allot[p][i] += request[i];
                    need[p][i] -= request[i];
                }
            }
        }
        else{
            cout << "Process " << p << " must wait, since the resources are not available." << endl;
        }
    }
    else{
        cout << "Process has exceeded its maximum claim." << endl;
    }
}
int main()
{
    int i = 0, j = 0;
    int processes[] = {0, 1, 2, 3, 4};
    cout << "Enter the available instances of resources: " << endl;
    int avail[R];
    cin >> avail[0] >> avail[1] >> avail[2];
    cout << "Enter the maximum resource that can be allocated to processes: " << endl;
    int maxm[P][R];
    for(i = 0; i < P; i++){
        cin >> maxm[i][0] >> maxm[i][1] >> maxm[i][2];
    }
    cout << "Enter the resources allocated to processes: " << endl;
    int allot[P][R];
    for(i = 0; i < P; i++){
        cin >> allot[i][0] >> allot[i][1] >> allot[i][2];
    }
    int need[P][R];
    for(i = 0; i < P; i++)
        for(j = 0; j < R; j++)
            need[i][j] = maxm[i][j] - allot[i][j];
    if(isSafe(processes, avail, maxm, allot))
    {
        int need[P][R], request[R], p;
        calculateNeed(need, maxm, allot);
        cout << "Choose a process: " << endl;
        cin >> p;
        cout << "Enter the request for resources for process chosen: " << endl;
        cin >> request[0] >> request[1] >> request[2];
        resourceRequest(processes, avail, maxm, allot, need, request, p);
    }
    return 0;
}
