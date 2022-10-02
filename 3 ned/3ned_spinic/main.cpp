#include <iostream>

using namespace std;

class Incognizable
{
private:
    int a;
    int b;
public:
    Incognizable(){};
    Incognizable(int s)
    {
        a = s;
        b = 0;
    };
    Incognizable(int s, int t)
    {
        a = s;
        b = t;
    };



};

int main() {
    Incognizable a;
    Incognizable b = {};
    Incognizable c = {0};
    Incognizable d = {0, 1};
    return 0;
}
