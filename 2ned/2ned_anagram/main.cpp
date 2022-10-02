#include <iostream>
#include <map>

using namespace std;

map <int, string> BuildCharCounters (map<int, pair<string, string>> words)
{
    map <int, string> res;
    map <char, int> fir, sec;
    pair<string, string> item;
    for (int i = 0; i < words.size(); i++)
    {
        item = words[i];
        for (auto & word : item.first)
            fir[word]++;
        for (auto & word : item.second)
            sec[word]++;
        if (fir == sec)
            res[i] = "YES";
        else
            res[i] = "NO";
        fir.clear();
        sec.clear();
    }
    return res;
}

int main()
{
    int N;
    string s1, s2;
    cin >> N;
    map<int, pair<string, string>> words;
    for (int i = 0; i < N; i++)
    {
        cin >> s1;
        cin >> s2;
        words[i] = make_pair(s1, s2);
    }
    for (auto & item :BuildCharCounters(words))
        cout << item.second << endl;
}
