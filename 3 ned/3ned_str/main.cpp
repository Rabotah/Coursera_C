#include <iostream>

using namespace std;

class ReversibleString
        {
private:
            string str;
public:
    ReversibleString () {};
    ReversibleString (string s)
    {
        str = s;
    }
    void Reverse()
    {
        string s("");
        for (int i = str.size()-1; i >= 0; i--)
            s += str[i];
        str = s;
    }
    string ToString() const
    {
        return str;
    }
        };

int main()
{
    ReversibleString s("live");
    s.Reverse();
    cout << s.ToString() << endl;
    s.Reverse();
    const ReversibleString& s_ref = s;
    string tmp = s_ref.ToString();
    cout << tmp << endl;
    ReversibleString empty;
    cout << '"' << empty.ToString() << '"' << endl;

    return 0;
}
