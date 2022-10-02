#include <iostream>
#include <algorithm>

using namespace std;

bool cmd(int &i, int& j) {return (abs(i)<abs(j));}

int main()
{
    int N;
    cin >> N;
    int a[N];
    for (int i = 0; i < N; i++)
        cin >> a[i];
    sort(a,a+N, cmd);
    for (const auto& v: a)
        cout << v << " ";
}
