#include <iostream>
#include <map>

using namespace std;



int main()
{
    int N;
    cin >> N;
    string com, country, new_c ;
    map <string, string> countries;
    for (int i = 0; i<N; i++)
    {
        cin >> com;
        if (com == "CHANGE_CAPITAL")
        {
            cin >> country;
            cin >> new_c;
            if(countries.find(country) == countries.end())
            {
                countries[country] = new_c;
                cout << "Introduce new country " << country <<  " with capital " <<  new_c << endl;
            }
            else if(countries[country] == new_c)
                cout << "Country " <<  country << " hasn't changed its capital" << endl;
            else
            {
                cout << "Country " << country << " has changed its capital from " << countries[country]
                << " to " << new_c << endl;
                countries[country] = new_c;
            }
        }
        if (com == "RENAME")
        {
            cin >> country;
            cin >> new_c;
            if(countries.find(country) == countries.end() ||
                countries.find(new_c) != countries.end()|| country == new_c)
                cout << "Incorrect rename, skip" << endl;
            else
            {
                cout << "Country " << country << " with capital " << countries[country] <<
                " has been renamed to " << new_c << endl;
                countries[new_c] = countries[country];
                countries.erase(country);
            }
        }
        if (com == "ABOUT")
        {
            cin >> country;
            if (countries.find(country) == countries.end())
                cout << "Country " << country << " doesn't exist" << endl;
            else
                cout << "Country " << country << " has capital " << countries[country] << endl;
        }
        if (com == "DUMP")
        {
            if (countries.empty())
                cout << "There are no countries in the world" << endl;
            else
            {
                for (auto& item : countries)
                    cout << item.first << "/" << item.second << endl;
            }
        }
    }
}
