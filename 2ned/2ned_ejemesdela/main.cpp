#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int N, k, mes(1);
    vector <vector<string>> dela(31);
    string com, s;
    cin >> N;
    for (int i = 0; i< N; i++)
    {
        cin >> com;
        if (com == "ADD")
        {
            cin >> k;
            cin >> s;
            dela[k-1].push_back(s);
        }
        if (com == "DUMP")
        {
            cin >> k;
            cout << dela[k-1].size() << " ";
            for(auto  const& d : dela[k-1])
                cout << d << " ";
            cout << endl;
        }
        if (com == "NEXT")
        {
            if (mes == 12)
                mes = 0;
            mes++;
            if (mes == 2)
            {
                vector<vector<string>> dela1(3);
                for (int t = 28; t < 31; ++t)
                    dela1[t-28].insert(end(dela1[t-28]), begin(dela[t]), end(dela[t]));
                dela.resize(28);
                for (int t = 0; t < 3; ++t)
                    dela[27].insert(end(dela[27]), begin(dela1[t]), end(dela1[t]));
            }
            else if (mes % 2 == 0 && mes < 7 || mes % 2 != 0 && mes > 7)
            {
                vector<string> dela1 = dela[30];
                dela.resize(30);
                dela[29].insert(end(dela[29]), begin(dela1), end(dela1));
            }
            else
                dela.resize(31);
        }
    }
}
