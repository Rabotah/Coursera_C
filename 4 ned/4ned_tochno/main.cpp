#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    ifstream input("C:\\Projects\\4ned_tochno\\input.txt");
    double line;
    cout << fixed << setprecision(3);
    while (input >> line)
        cout  << line << endl;
    return 0;
}
