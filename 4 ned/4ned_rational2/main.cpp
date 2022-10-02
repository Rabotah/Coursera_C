#include <iostream>
#include <sstream>

using namespace std;

int GCD(int u, int v) {             //функция поиска НОД
    int r(1);
    while ( v != 0)
    {
        r = abs(u % v);
        u = v;
        v = r;
    }
    return u;
}

class Rational {                    //класс, хранящий рациональные числа (дроби)
    //в виде 3/4, -4/4 итд
public:
    int numerator;                  // числитель
    int denominator;                // знаменатель (уводить в приват их не нужно)
    Rational()
    {
        numerator = 0;
        denominator = 1;
    }
    Rational(int numerator1, int denominator1)
    {
        if (denominator1 == 0)
            throw invalid_argument("Invalid argument");
        if (numerator1 < 0 && denominator1 < 0 || numerator1 > 0 && denominator1 < 0)
        {
            numerator1 *= -1;              //-2/-3 = 2/3;   -2/3 = 2/-3 = -2/3
            denominator1 *= -1;            //-2/-3 = 2/3;   0/15 = 0/1
        }                                  //дроби с делением на 0 не предусматриваются
        if (numerator1 == 0)
            denominator1 = 1;
        else
        {
            int t = GCD(numerator1, denominator1);    // тут я их сокращаю
            numerator1 /= t;
            denominator1 /= t;
        }
        numerator = numerator1;
        denominator = denominator1;
    }

    int Numerator() const
    {
        return numerator;
    }
    int Denominator() const
    {
        return denominator;
    }
};

Rational operator+ (const Rational & r1, const Rational & r2)
{
    int n1, n2, d;
    n1 = r1.Numerator()*r2.Denominator()/GCD(r1.Denominator(), r2.Denominator());
    n2 = r1.Denominator()*r2.Numerator()/GCD(r1.Denominator(), r2.Denominator());
    d = r1.Denominator() * r2.Denominator()/ GCD(r1.Denominator(), r2.Denominator());
    return {n1+n2, d};
}

Rational operator- (const Rational & r1, const Rational & r2)
{
    int n1, n2, d;
    n1 = r1.Numerator()*r2.Denominator()/GCD(r1.Denominator(), r2.Denominator());
    n2 = r1.Denominator()*r2.Numerator()/GCD(r1.Denominator(), r2.Denominator());
    d = r1.Denominator() * r2.Denominator()/ GCD(r1.Denominator(), r2.Denominator());
    return {n1-n2, d};
}

Rational operator* (const Rational & r1, const Rational & r2)
{
    return {r1.Numerator()*r2.Numerator(), r1.Denominator()*r2.Denominator()};
}

Rational operator/ (const Rational & r1, const Rational & r2)
{
    if (r1.denominator == 0 || r2.numerator == 0 || r2.denominator == 0)
        throw domain_error("Division by zero");
    return {r1.Numerator()*r2.Denominator(), r1.Denominator()*r2.Numerator()};
}

ostream& operator << (ostream & n, const Rational & r1)
{
    n << r1.Numerator() << "/" << r1.Denominator();
    return n;
}

istream &operator>>(istream & n, Rational & r1)   //пишет ошибку тут
{                                                 //Read from empty stream works incorrectly
    if (n.eof())
        return n;
    int k(' '), d(' ');
    char m(' ');
    n >> k;
    n >>  m;
    n >> d;
    if (m!= '/' || d == ' ' || k == ' ')
        r1 = Rational();
    else if (d == 0)
        throw invalid_argument("Invalid argument");
    else
        r1 = Rational(k, d);
    return n;
}

Rational Do (Rational& r1, Rational& r2, char op)
{
    if (op == '+')
        return r1 + r2;
    if (op == '-')
        return r1 - r2;
    if (op == '*')
        return r1 * r2;
    if (op == '/')
        return r1 / r2;
}

bool operator== (const Rational & r1, const Rational & r2)
{
    if (r1.Numerator()== r2.Numerator() && r1.Denominator() == r2.Denominator())
        return true;
    else
        return false;
}

bool operator< (const Rational & r1, const Rational & r2) {
    int n1, n2;
    n1 = r1.Numerator() * r2.Denominator() / GCD(r1.Denominator(), r2.Denominator());
    n2 = r1.Denominator() * r2.Numerator() / GCD(r1.Denominator(), r2.Denominator());
    return n1 < n2;
}

int main()
{
    try {

        Rational r1, r2;
        char op;
        cin >> r1;
        cin >> op;
        cin >> r2;
        cout << Do(r1, r2, op);
    }
    catch (exception& e)
    {
        cout << e.what();
    }
    return 0;
}