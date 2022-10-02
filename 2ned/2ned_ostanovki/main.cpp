#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
    int N, kol;
    map<string, vector<string>> bs, st;
    cin >> N;
    string com, bus, stop;
    for (int i = 0; i<N; i++)
    {
        cin >> com;
        if (com == "NEW_BUS")
        {
            cin >> bus;
            cin >> kol;
            for (int t = 0; t < kol; t++)
            {
                cin >> stop;
                bs[bus].push_back(stop);
                st[stop].push_back(bus);
            }
        }
        if (com == "BUSES_FOR_STOP")
        {
            cin >> stop;
            if (st[stop].size() == 0)
                cout << "No stop";
            else
            {
                for (int t = 0; t < st[stop].size(); t++)
                    cout << st[stop][t] << " ";
            }
            cout << endl;
        }
        if (com == "STOPS_FOR_BUS")
        {
            cin >> bus;
            if (bs.find(bus) == bs.end())
                cout << "No bus";
            else {
                for (int t = 0; t < bs[bus].size(); t++) {
                    cout << "Stop " << bs[bus][t] << ": ";
                    if (st[bs[bus][t]].size() == 1)
                        cout << "no interchange";
                    else
                        for (int f = 0; f < st[bs[bus][t]].size(); f++)
                            if (st[bs[bus][t]][f] != bus)
                                cout << st[bs[bus][t]][f] << " ";
                    cout << endl;
                }
            }
            cout << endl;
        }
        if (com == "ALL_BUSES")
        {
            if (bs.size() == 0)
                cout << "No buses";
            else
            {
                for (const auto &v: bs) {
                    cout << "Bus " << v.first << ": ";
                    for (const auto &s: v.second)
                        cout << s << " ";
                    cout << endl;
                }
            }
            cout << endl;
        }
    }
}