#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    int N, kol, numb(1);
    map<vector <string>, int> bs;
    vector <string> st;
    string stop;
    cin >> N;
    for (int i = 0; i<N; i++)
    {
        cin >> kol;
        for (int t = 0; t<kol; t++)
        {
            cin >> stop;
            st.push_back(stop);
        }
            if (bs.find(st) == bs.end()) {
                cout << "New bus " << numb << endl;
                bs[st] = numb;
                numb++;
            } else
                cout << "Already exists for " << bs[st] << endl;
            st.clear();
    }
}
