#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, sum(0), el, kol(0);
    vector<int> days, t;
    cin >> N;
    for (int i = 0; i< N; i++)
    {
        cin >> el;
        days.push_back(el);
        sum += el;
    }
    for (int i = 0; i< N; i++)
    {
        if (days[i]>sum/N)
            t.push_back(i);
    }
    cout << t.size() << endl;
    for (auto & v: t)
        cout << v << " ";
}
