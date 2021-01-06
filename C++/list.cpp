#include <iostream>
#include <list>
using namespace std;
int main()
{
	//rectangle r(1, 2);
	///*printf("%d", r.size());*/
	list<int> l;
	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(3);
	l.push_back(4);
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
    l.erase(remove(l.begin(), l.end(), 3), l.end());
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		if (*it == 3)
		{
			l.erase(it);
			break;
		}
	}
	for (list<int>::iterator it = l.begin(); it != l.end(); it++)
	{
		cout << *it << " ";
	}
	
	// vector<int> vec;
	// vec.push_back(0);
	// vec.push_back(1);
	// vec.push_back(2);
	// vec.push_back(2);
	// vec.push_back(3);
	// for (int i = 0; i < vec.size(); i++)
	// {
	// 	cout<<vec[i]<<" ";
	// }
	// cout<<endl;
	// for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++)
	// {
	// 	if(*it==2)
	// 	{
	// 		vec.erase(it);
	// 		break;
	// 	}
	// }
	// for (int i = 0; i < vec.size(); i++)
	// {
	// 	cout<<vec[i]<<" ";
	// }
	// cout<<endl;
	// return 0;
}