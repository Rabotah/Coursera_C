#include <iostream>
#include <set>
#include <map>

using namespace std;

set <string> BuildMapValuesSet(map<int, string> slv)
{
    set <string> val;
    for (auto & v : slv)
        val.insert(v.second);
    return val;
}

int main()
{
    set<string> values = BuildMapValuesSet({
       {1, "odd"},
       {2, "even"},
       {3, "odd"},
       {4, "even"},
       {5, "odd"}});

    for (const string& value : values) {
        cout << value << endl;
    }
}
