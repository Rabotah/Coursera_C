#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <string>

using namespace std;

int check_it(const vector<int>& v, const int & year)
{
    int t(0), s(0);
    for (int i : v)
    {
        if (i <= year && i >= s)
            s = i;
    }
    for (int i : v)
    {
        if (i == s)
            t++;
    }
    return t;
}

pair <int, int> find_pair (const vector<int>& v, const int year)
{
    int s(-1);
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == year) {
            if (s == -1)
                s = i;
            else
                return make_pair(s, i);
        }
    }
}

pair <int, int> find_minp(const vector<int>& v, const int year)
{
    int t, s = -1;
    for (int i = 0; i < v.size(); i++)
        if (v[i] < year && (v[i] > v[t] && t != -1 || t == -1))
            t = i;
    for (int i = 0; i < v.size(); i++)
        if (v[i] < year && t != i && (v[i] > v[s] && s != -1 || s == -1))
            s = i;
    return make_pair(t,s);
}

int find_min(const vector<int>& v, const int year)
{
    int t = -1;
    for (int i = 0; i < v.size(); i++)
        if (v[i] <= year && (v[i] > v[t] && t != -1 || t == -1))
            t = i;
    return t;
}

int find_last (const vector<string>& v, const vector<int>& y, const int year)
{
    int t(-1);
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != "no" && v[i] != "" && y[i] <= year && (y[i] > y[t] && t != -1 || t == -1))
            t = i;
    }
    return t;
}

string history (const vector<int> &y, const vector<string> &item, string & ret, const int & year)
{
    string past(ret);
    bool s(true);
    int maxi(-1), it_m(-1), pr(year), del(-1);
    vector<int> y2, it;
    for (int i = 0; i < y.size(); i++)
    {
        if (y[i] <= year)
        {
            y2.push_back(y[i]);
            it.push_back(i);
        }
    }
    for (auto i = 0; i < y2.size(); i++)
    {
        if (item[it[i]] == "no" || item[it[i]] == "") {
            y2.erase(y2.begin() + i);
            it.erase(it.begin() + i);
            i = -1;
        }
    }
    while (true)
    {
        for (auto i = 0; i < y2.size(); i++)
        {
            if (y2[i] < pr && y2[i] > maxi && item[it[i]] != past)
            {
                maxi = y2[i];
                it_m = it[i];
                del = i;
            }
        }
        if (maxi == -1)
            break;
        y2.erase(y2.begin() + del);
        it.erase(it.begin() + del);
        if (maxi == year)
        {
            ret += "-" + item[it_m];
            past = item[it_m];
        }
        if (ret.find(" (") == string::npos)
        {
            ret += " (" + item[it_m];
            past = item[it_m];
            s = false;
        }
        else
        {
            ret += ", " + item[it_m];
            past = item[it_m];
        }
        pr = maxi;
        maxi = -1;
        del = -1;
    }
    if (ret.find('(') != string::npos)
        ret += ")";
    return ret;
}

class Person {
public:
    void ChangeFirstName(const int & year, const string& first_name)
    {
        if (find(yn.begin(), yn.end(), year) != yn.end())
        {
            for (int i = 0; i < y.size(); i++)
            {
                if (y[i] == year && name[i] != "" && name[i] != "no")
                {
                    name[i] = first_name;
                    break;
                }
            }
        }
        else
        {
            yn.push_back(year);
            y.push_back(year);
            name.push_back(first_name);
            if (surname.empty() || surname.back() == "")
                surname.push_back("");
            else
                surname.push_back("no");
        }

    }
    void ChangeLastName(const int & year, const string& last_name)
    {
        if (find(yf.begin(), yf.end(), year) != yf.end())
        {
            for (int i = 0; i < y.size(); i++) {
                if (y[i] == year && surname[i] != "" && surname[i] != "no") {
                    surname[i] = last_name;
                    break;
                }
            }
        }
        else {
            yf.push_back(year);
            y.push_back(year);
            surname.push_back(last_name);
            if (name.empty() || name.back() == "")
                name.push_back("");
            else
                name.push_back("no");
        }

    }
    string GetFullName(const int & year)
    {
        int t(-1), s(0);
        s = check_it(y, year);
        if (s == 0)
        {
            t = find_min(y, year);
            if (t == -1)
                return "Incognito";
        }
        else if (s == 1) {
            t = find_min(y, year);
            if (name[t] == "")
                return surname[t] + " with unknown first name";
            else if (name[t] == "no") {
                int s = find_last(name, y, year);
                if (s == -1)
                    return surname[t] + " with unknown first name";
                return name[s] + " " + surname[t];
            } else if (surname[t] == "")
                return name[t] + " with unknown last name";
            else if (surname[t] == "no") {
                int s = find_last(surname, y, year);
                if (s == -1)
                    return name[t] + " with unknown last name";
                return name[t] + " " + surname[s];
            }
        }
        else if(s == 2)
        {
            pair<int, int> k;
            if (find(y.begin(), y.end(), year) != y.end())
                k = find_pair(y, year);
            else
                k = find_minp(y, year);
            if (name[k.first] != "no" && name[k.first] != "")
                return name[k.first] + " " + surname[k.second];
            else
                return name[k.second] + " " + surname[k.first];
        }

    }
    string GetFullNameWithHistory(const int& year)
    {
        string now = GetFullName(year);
        if (now == "Incognito")
            return now;
        if (now.find(" with unknown first name") != string::npos)
        {
            size_t it = now.find(" with unknown first name") + 1;
            string ret = now.substr(0, it);
            ret = history(y, surname, ret, year);
            return  ret + " with unknown first name";
        }
        if (now.find(" with unknown last name") != string::npos)
        {
            size_t it = now.find(" with unknown last name") + 1;
            string ret = now.substr(0, it);
            ret = history(y, name, ret, year);
            return  ret + " with unknown last name";
        }
        else
        {
            size_t it = now.find(' ') + 1;
            size_t it2 = now.size() - now.find(' ');
            string ret = now.substr(0, it-1);
            string ret2 = now.substr(it, it2);
            ret = history(y, name, ret, year);
            ret2 = history(y, surname, ret2, year);
            return ret + " " + ret2;
        }
    }
private:
    vector<int> y;
    vector<int> yn;
    vector<int> yf;
    vector <string> name;
    vector <string> surname;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeFirstName(1990, "Polina");
    person.ChangeLastName(1990, "Volkova-Sergeeva");
    cout << person.GetFullNameWithHistory(1990) << endl;

    person.ChangeFirstName(1966, "Pauline");
    cout << person.GetFullNameWithHistory(1966) << endl;

    person.ChangeLastName(1960, "Sergeeva");
    for (int year : {1960, 1967}) {
        cout << person.GetFullNameWithHistory(year) << endl;
    }

    person.ChangeLastName(1961, "Ivanova");
    cout << person.GetFullNameWithHistory(1967) << endl;

    return 0;
}
