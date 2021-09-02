#include <bits/stdc++.h>
using namespace std;

#define MAX_SIZE = 100000
template <typename T>
void merge(T *a, int start, int mid, int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;
    T b1[n1], b2[n2];
    for (int i = 0; i < n1; i++)
    {
        b1[i] = a[start + i];
    }
    for (int i = 0; i < n2; i++)
    {
        b2[i] = a[mid + 1 + i];
    }
    int i, j, k;
    i = j = 0, k = start;
    while (i < n1 && j < n2)
    {
        if (b1[i] < b2[j])
        {
            a[k] = b1[i];
            i++;
        }
        else
        {
            a[k] = b2[j];
            j++;
        }
        k++;
    }
    while (i < n1)
    {
        a[k] = b1[i];
        k++, i++;
    }
    while (j < n2)
    {
        a[k] = b2[j];
        k++, j++;
    }
}

template <typename T>
void merge_sort(T *a, int start, int end)
{
    if (start >= end)
    {
        return;
    }
    int mid = (start + end) / 2;
    merge_sort(a, start, mid);
    merge_sort(a, mid + 1, end);
    merge(a, start, mid, end);
}

int main()
{
    int a[] = {2, 5, 1, 4, 3};
    merge_sort(a, 0, 4);
    double b[] = {1.2, 3.5, 1.1};
    for (int i = 0; i < 5; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
    merge_sort(b, 0, 2);
    for (int i = 0; i < 3; i++)
    {
        cout << b[i] << " ";
    }
}