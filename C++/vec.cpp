#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main()
{
    vector<int> vec[3];
    for (int i = 0; i < 3; i++)
    {
       for (int j = 0; j < 8; j++)
       {
           vec[i].push_back(i*j);
       }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < vec[i].size(); j++)
        {
            cout<<vec[i][j]<<" ";
        }
        cout<<endl;
    }
    vec[1].erase(remove(vec[1].begin(),vec[1].end(),3),vec[1].end());
    for (int i = 0; i < vec[1].size(); i++)
    {
        cout<<vec[1][i]<<" ";
    }
    cout<<endl;
    cout<<*vec[1];
}