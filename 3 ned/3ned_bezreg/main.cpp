#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

bool cmp(const string &i, const string& j)
{
    for (int t = 0; t < min(i.size(), j.size()); t++)
    {
        if (tolower(i[t]) <  tolower(j[t]))
            return true;
        if (tolower(i[t]) >  tolower(j[t]))
            return false;
    }
    if (i.size() < j.size())
        return true;
    return false;
}

int main()
{
    int N;
    cin >> N;
    string a[N];
    for (int i = 0; i < N; i++)
        cin >> a[i];
    sort(a+0,a+N, cmp);
    for (const auto& v: a)
        cout << v << " ";
}
