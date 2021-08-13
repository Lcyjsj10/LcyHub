#include <bits/stdc++.h>
using namespace std;

int m, n;
void file_input(string file_path);
int main()
{
    string file_path;
    cin >> file_path;
    file_input(file_path);
}

void file_input(string file_path)
{
    ifstream fin;
    fin.open(file_path);
    while (true)
    {
        fin >> n >> m;
        cout << n << " " << m << endl;
        if (fin.eof())
        {
            break;
        }
    }

    fin.close();
}