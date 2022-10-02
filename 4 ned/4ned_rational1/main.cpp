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
    int k(0), d(0);
    char m(' ');
    n >> k;
    if (!n.operator bool())
    {
        r1 = Rational();
        return n;
    }
    n >>  m;
    if (m!= '/' )
    {
        r1 = Rational();
        return n;
    }
    n >> d;
    if (d == 0)
    {
        r1 = Rational();
        return n;
    }
    r1 = Rational(k, d);
    return n;
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
    {
        ostringstream output;
        output << Rational(-6, 8);
        if (output.str() != "-3/4") {
            cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
            return 1;
        }
    }

    {
        istringstream input("5/7");
        Rational r;
        input >> r;
        bool equal = r == Rational(5, 7);
        if (!equal) {
            cout << "5/7 is incorrectly read as " << r << endl;
            return 2;
        }
    }

    {
        istringstream input("7");
        Rational r;
        bool correct = !(input >> r);
        if (!correct) {
            cout << "Read from empty stream works incorrectly" << endl;
            return 3;
        }
    }

    {
        istringstream input("5/7 10/8");
        Rational r1, r2;
        input >> r1 >> r2;
        bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
            return 4;
        }

        input >> r1;
        input >> r2;
        correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
        if (!correct) {
            cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
            return 5;
        }
    }

    {
        istringstream input1("1*2"), input2("1/"), input3("/4");
        Rational r1, r2, r3;
        input1 >> r1;
        input2 >> r2;
        input3 >> r3;
        bool correct = r1 == Rational() && r2 == Rational() && r3 == Rational();
        if (!correct) {
            cout << "Reading of incorrectly formatted rationals shouldn't change arguments: "
                 << r1 << " " << r2 << " " << r3 << endl;

            return 6;
        }
    }

    cout << "OK" << endl;
    return 0;
}