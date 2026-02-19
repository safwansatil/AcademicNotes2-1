#include <bits/stdc++.h>
using namespace std;

int table[1000][1000];
int a[1000];

int query(int L, int R)
{
    int window = R - L + 1;
    int j = log(window);
    return min(table[L][j], table[R - (1 << j) + 1][j]);
}

int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        table[i][0] = a[i];
    }

    for (int j = 1; j < log(n); j++)
    {
        for (int i = 0; i + (1 << j) - 1 < n; i++)
        {
            table[i][j] = min(table[i][j - 1], table[i + (1 << j - 1)][j - 1]);
        }
    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int L, R;
        cin >> L >> R;
        cout << query(L, R) << endl;
    }
}
