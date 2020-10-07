#include <iostream>
#include <map>
#include<vector>
#include<math.h>
#define testPrint
using namespace std;
bool testing = false;
void arrInput(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int el;
        cin >> el;
        arr[i] = el;
    }
}

map<int, float> firstInfection(int index, int arr[], int n, int remaining[])
{
    map<int, float> infected;
    int remIndex = 0;
    for (int i = 0; i < index; i++)
    {
        float relVel = arr[i] - arr[index];
        if (relVel != 0)
        {
            float time = abs(float(index - i)) / relVel;
            if (time >= 0)
            {
                infected[i] = time;
            }
            else
            {
                remaining[remIndex] = i;
                remIndex++;
            }
        }
        else
        {
            remaining[remIndex] = i;
            remIndex++;
        }
    }
    for (int i = index + 1; i < n; i++)
    {
        float relVel = arr[index] - arr[i];
        if (relVel != 0)
        {
            float time = abs(float(index - i)) / relVel;
            if (time >= 0)
            {
                infected[i] = time;
            }
            else
            {
                remaining[remIndex] = i;
                remIndex++;
            }
        }
        else
        {
            remaining[remIndex] = i;
            remIndex++;
        }
    }
    // cout<<"infected = > "<< infected.size()<<endl;
    return infected;
}

void printMap(map<int, float> infected[], int n, string message = "printing map function")
{
    if (testing)
    {
        cout << message << " "
             << "new print" << endl
             << endl;

        for (int i = 0; i < n; i++)
        {
            cout << endl
                 << "map " << i << " " << endl;
            for (auto j = infected[i].begin(); j != infected[i].end(); j++)
            {
                cout << j->first << " " << j->second << endl;
            }
        }
        cout << endl;
    }
}

void printArray(int n, int arr[],string message = "printing array")
{
    if (testing)
    { cout<<message<<" ";
        for (int j = 0; j < n; j++)
        {
            cout << arr[j] << " ";
        }
    }
}

void solve()
{
    int n;
    cin >> n;
    int arr[n];
    map<int, float> infected[n];
    arrInput(arr, n);
    int remaining[n][n];
    ///******************************
    for (int i = 0; i < n; i++)   //*
    {                             //*
        for(int j = 0;j<n;j++){   //*
            remaining[i][j] = -1; //*
        }                         //*
    }                             //*
    //******************************/
    for (int i = 0; i < n; i++)
    {

        infected[i] = firstInfection(i, arr, n, remaining[i]);
        printMap(infected, n);
    }
    int maxCount = infected[0].size() + 1;
    int minCount = infected[0].size() + 1;
    for (int i = 0; i < n; i++)
    { // for each athelete
        int count = infected[i].size() + 1;
        if(testing){
                 cout<<"count =>"<<count<<endl;
                 }
        if (count > 0)
        {
            for (int index = 0; index < i; index++)
            { // for each map to check if the particular map has the infected index or not
                if (infected[i].find(index) != infected[i].end())
                {
                    int remIndex = 0;                    
                    while ( remIndex < n)// while (remaining[i][remIndex] != -1 && remIndex < n)
                    {
                        int isPresent = remaining[i][remIndex];
                        if (infected[index].find(isPresent) != infected[index].end())
                        {
                            if (infected[index][isPresent] >= infected[i][index])
                            {
                                if(testing){
                                    cout<<infected[index][isPresent]<<" "<<infected[i][index]<<" "<<i<<" "<<index<<" "<<index<<endl;
                                }
                                remaining[i][remIndex] = -1;
                                count++;
                            }
                        }
                        remIndex++;
                    }
                }
            }

            for (int index = i + 1; index < n; index++)
            {
                // for each map to check if the particular map has the infected index or not
                if (infected[i].find(index) != infected[i].end())
                {
                    int remIndex = 0;
                    while ( remIndex < n)// while (remaining[i][remIndex] != -1 && remIndex < n)
                    {
                        int isPresent = remaining[i][remIndex];
                        if (infected[index].find(isPresent) != infected[index].end())
                        {
                            printMap(infected, n, "checking map from linkng loop");
                            if (infected[index][isPresent] >= infected[i][index])
                            {
                                if(testing){
                                    cout<<infected[index][isPresent]<<" "<<infected[i][index]<<" "<<i<<" "<<index<<" "<<index<<endl;
                                }
                                remaining[i][remIndex] = -1;
                                count++;
                            }
                        }
                        remIndex++;
                    }
                }
            }
        }
        maxCount = max(maxCount, count);
        minCount = min(minCount, count);
    }
    cout << minCount << " " << maxCount << endl;
}

int main(int arg, char **args)
{
    if (arg > 1)
        *args[1] == 'd' ? testing = true : testing = false;
    int t;
    cin >> t;
    while (t-- > 0)
    {
        solve();
    }
    return 0;
}