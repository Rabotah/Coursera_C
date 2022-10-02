#include <iostream>

using namespace std;

struct  Specialization
{
    string spec;
    explicit Specialization (string m)
    {
        spec = m;
    }
};

struct Course
{
    string cou;
    explicit Course (string m)
    {
        cou = m;
    }
};

struct Week
{
    string wee;
    explicit Week (string m)
    {
        wee = m;
    }
};

struct LectureTitle {
    string specialization;
    string course;
    string week;
    LectureTitle (Specialization m, Course c, Week w)
    {
        specialization = m.spec;
        course = c.cou;
        week = w.wee;
    }
};



int main()
{
    LectureTitle title(
            Specialization("C++"),
            Course("White belt"),
            Week("4th")
    );
    cout << title.specialization << " " << title.course << " " << title.week;
}
