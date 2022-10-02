#include <iostream>
#include <vector>

using namespace std;

void Reverse(vector <int> & v)
{
    vector <int> c;
    for (int i = v.size()-1; i >= 0; i--)
        c.push_back(v[i]);
    v = c;
}

int main()
{
    vector<int> numbers = {1, 5, 3, 4, 2};
    Reverse(numbers);
    for (int i = 0; i < numbers.size(); i++)
        cout << numbers[i] << " ";
}
