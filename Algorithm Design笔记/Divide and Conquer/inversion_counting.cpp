#include <bits/stdc++.h>
using namespace std;

template <typename T>
int merge(T *a, int start, int mid, int end)
{
    int reverse_num = 0; //用于记录逆序对的个数
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
            reverse_num += n1 - i; //R[j]将和后面L[i……n1-1]都构成逆序对，所以加上n1-i
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
    return reverse_num;
}
template <typename T>
int merge_sort(T *a, int start, int end)
{
    if (start >= end)
    {
        return 0;
    }
    int mid = (start + end) / 2;
    return merge_sort(a, start, mid) + merge_sort(a, mid + 1, end) + merge(a, start, mid, end);
}

int main()
{
    int a[] = {1, 2, 1, 4, 5};
    cout << "the reverse num is: " << merge_sort(a, 0, 4) << endl;
}