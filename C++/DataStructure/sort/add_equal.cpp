//查找数列a[]中是否存在和为x的两个数，时间复杂度为nlogn
#include <bits/stdc++.h>
using namespace std;

template <typename T>
void merge(T *a, int start, int mid, int end)
{
    int n1 = mid - start + 1;
    int n2 = end - mid;
    T L[n1], R[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = a[start + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = a[mid + 1 + i];
    }
    int i, j, k;
    i = j = 0, k = start;
    while (i < n1 && j < n2)
    {
        if (L[i] > R[j])
        {
            a[k++] = R[j++];
        }
        else
        {
            a[k++] = L[i++];
        }
    }
    while (i < n1)
    {
        a[k++] = L[i++];
    }
    while (j < n2)
    {
        a[k++] = R[j++];
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

template <typename T>
bool find_add_equal(T *a, int start, int end, T add)
{
    int start_ptr = start;
    int end_ptr = end;
    while (start_ptr < end_ptr)
    {
        if (a[start_ptr] + a[end_ptr] == add)
        {
            return true;
        }
        else
        {
            if (a[start_ptr] + a[end_ptr] > add)
            {
                end_ptr--;
            }
            else
            {
                start_ptr++;
            }
        }
    }
    return false;
}

int main()
{
    int a[] = {1, 3, 4, 2, 5};
    merge_sort(a, 0, 4);
    int x;
    cin >> x;
    if (find_add_equal(a, 0, 4, x))
    {
        cout << "find"
             << " " << x << ":" << 1 << endl;
    }
    else
    {
        cout << "find"
             << " " << x << ":" << 0 << endl;
    }
}