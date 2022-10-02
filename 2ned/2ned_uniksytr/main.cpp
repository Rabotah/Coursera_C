#include <iostream>
#include <set>

using namespace std;

int main()
{
    int N;
    string s;
    cin >> N;
    set<string> str;
    for (int i = 0; i < N; i++)
    {
        cin >> s;
        str.insert(s);
    }
    cout << str.size();
}
