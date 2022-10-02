#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, kol, worry(0);
    string com;
    cin >> N;
    vector <int> people = {};
    for (int i = 0; i< N; i++)
    {
        cin >> com;
        if (com != "WORRY_COUNT")
            cin >> kol;
        if (com == "COME" && kol > 0)
            people.resize(people.size() + kol, 0);
        if (com == "COME" && kol < 0)
            people.resize(people.size() + kol);
        if (com == "WORRY")
            people[kol] = 1;
        if (com == "QUIET")
            people[kol] = 0;
        if (com == "WORRY_COUNT")
        {
            for (auto const & v : people)
                if (v == 1) worry += 1;
            cout << worry << endl;
            worry = 0;
        }
    }
}
