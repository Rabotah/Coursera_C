#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("C:\\Projects\\4ned_tabl\\input.txt");
    int a, b, line;
    input >> a >> b;
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            input >> line;
            input.ignore(1);
            cout << setw(10) << line ;
            if (j != b-1)
                cout << " ";
        }
        if (i != a-1)
            cout << endl;
    }
    return 0;
}
