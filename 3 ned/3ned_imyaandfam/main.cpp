#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

int find_it (vector<int> v, int year)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == year)
            return i;
    }
}
int find_min(vector<int> v, int year)
{
    int t = -1;
    for (int i = 0; i < v.size(); i++)
        if (v[i] < year && (v[i] > v[t] && t != -1 || t == -1))
            t = i;
    return t;
}

int find_last (vector<string> v, vector<int> y, int year)
{
    int t(-1);
    for (int i = 0; i < v.size(); i++) {
        if (v[i] != "no" && v[i] != "" && y[i] <= year && (y[i] > y[t] && t != -1 || t == -1))
            t = i;
    }
    return t;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name)
    {
        y.push_back(year);
        name.push_back(first_name);
        if(surname.empty() || surname.back() == "")
            surname.push_back("");
        else
            surname.push_back("no");
    }
    void ChangeLastName(int year, const string& last_name)
    {
        y.push_back(year);
        surname.push_back(last_name);
        if (name.empty() || name.back() == "")
            name.push_back("");
        else
            name.push_back("no");
    }
    string GetFullName(int year)
    {
        int t;
        if (find(y.begin(), y.end(), year) == y.end())
        {
            t = find_min(y, year);
            if (t == -1)
                return "Incognito";
        }
        else
            t = find_it(y, year);
        if (name[t] == "")
            return surname[t] + " with unknown first name";
        else if (name[t] == "no") {
            int s = find_last(name, y, year);
            if (s == -1)
                return surname[t] + " with unknown first name";
            return name[s] + " " + surname[t];
        }
        else if (surname[t] == "")
            return name[t] + " with unknown last name";
        else if (surname[t] == "no")
        {
            int s = find_last(surname, y, year);
            if (s == -1)
                return name[t] + " with unknown last name";
            return name[t] + " " + surname[s];
        }
        else
            return name[t] + " " + surname[t];

    }
private:
    vector<int> y;
    vector <string> name;
    vector <string> surname;
};

int main() {
    Person person;

    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1967, "Sergeeva");
    for (int year : {1900, 1965, 1990}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    person.ChangeLastName(1968, "Volkova");
    for (int year : {1969, 1970}) {
        cout << person.GetFullName(year) << endl;
    }

    return 0;
}