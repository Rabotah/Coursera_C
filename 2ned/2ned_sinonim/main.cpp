#include <iostream>
#include <set>
#include <map>

using namespace std;

int main() {
    int N;
    cin >> N;
    string com, s1, s2;
    map <string, set <string>> sin;
    for (int i = 0; i<N; i++)
    {
        cin >> com;
        if (com == "ADD")
        {
            cin >> s1;
            cin >> s2;
            sin[s1].insert(s2);
            sin[s2].insert(s1);
        }
        if (com == "COUNT")
        {
            cin >> s1;
            cout << sin[s1].size() << endl;
        }
        if (com == "CHECK")
        {
            cin >> s1;
            cin >> s2;
            if (sin[s1].find(s2) == sin[s1].end())
                cout << "NO" << endl;
            else
                cout << "YES" << endl;
        }
    }
}
