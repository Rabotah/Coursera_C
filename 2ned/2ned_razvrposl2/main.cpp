#include <iostream>
#include <vector>

using namespace std;

vector<int> Reversed(const vector<int>& v)
{
    vector <int> c;
    for (int i = v.size()-1; i >= 0; i--)
        c.push_back(v[i]);
    return c;
}

int main() {
    vector<int> numbers = {1, 5, 3, 4, 2};
    vector<int> c = Reversed(numbers);
    for (int i = 0; i < numbers.size(); i++)
        cout << numbers[i] << " ";
    for (int i = 0; i < c.size(); i++)
        cout << c[i] << " ";
}
