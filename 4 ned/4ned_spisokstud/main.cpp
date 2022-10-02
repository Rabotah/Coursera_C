#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

struct Student
{
    string name;
    string surname;
    int day;
    int month;
    int year;
};

using namespace std;

int main() {
    vector <Student> info;
    int kol, n, day, month, year;
    string com, name, surname;
    cin >> kol;
    for (int i = 0; i < kol; i++)
    {
        cin >> name;
        cin >> surname;
        cin >> day;
        cin >> month;
        cin >> year;
        info.push_back({name, surname, day, month, year});
    }
    cin >> kol;
    for (int i = 0; i < kol; i++)
    {
        cin >> com;
        cin >> n;
        if (com == "name" && n > 0 && n <= info.size())
            cout << info[n-1].name << " " << info[n-1].surname;
        else if (com == "date" && n > 0 && n <= info.size())
            cout << info[n-1].day << "." << info[n-1].month << "." << info[n-1].year;
        else
            cout << "bad request";
        cout << endl;
    }
    return 0;
}