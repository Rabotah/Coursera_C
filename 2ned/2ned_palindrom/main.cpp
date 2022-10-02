#include <iostream>
#include <vector>
#include <string>

using namespace std;

//палиндром

vector <string> PalindromFilter (vector <string> words, int minLength)
{
    vector<string> ret = {};
    string w = "";
    bool p;
    for (int i = 0; i < words.size(); i++)
    {
        p = true;
        w = words[i];
        if (w.size() >=  minLength)
        {
            for (int j = 0; j < w.size() / 2; ++j)
            {
                if (w[j] != w[w.size() - j - 1])
                    p = false;
            }
            if (p)
                ret.push_back(w);
        }
    }
    return ret;
}

int main()
{
    vector<string> words = {"weew", "bro",  "code",  "4"};
    int minlength = 4;
    words = PalindromFilter(words, minlength);
    for (int i = 0; i < words.size(); i++) {
        cout << words[i] << " ";
    }
}