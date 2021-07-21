#include<iostream>
#include<map>
#include<cstring>
using namespace std;

int main(){
    map<string,int> m;
    m.insert(pair<string,int>("aa",1));
    m.insert(pair<string,int>("b",1));
    string str;
    cin >> str;
    if (m.find(str)!=m.end())
    {
        cout<<"存在"<<endl;
    }else
    {
        cout<<"不存在"<<endl;
    }
    
    
}
