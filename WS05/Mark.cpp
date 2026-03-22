/***********************************************************************
// OOP244 Workshop 5: Mark Module
//
// File	Mark.cpp
// Version 1.0
// Date	2025/06/12
// Author	partially done by Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name            Date            Reason
//
/////////////////////////////////////////////////////////////////
***********************************************************************/
#include <iostream>
#include <cmath> // for round function
#include "Mark.h"
using namespace std;
namespace seneca {
    bool Mark::isValid()const {
        return  (m_value >= 0 && m_value <= 100);
    }
    Mark::Mark(int value, char type) {
        *this = type;
        m_value = double(value);
    }

    Mark::Mark(double value) {
        m_type = MARK;
        m_value = value;
    }

    Mark& Mark::operator+=(const Mark& M) {
        m_value += M.m_value;
        return *this;
    }

    Mark& Mark::operator-=(const Mark& M) {
        m_value -= M.m_value;
        return *this;
    }

    Mark& Mark::operator/=(int other) {
        m_value = m_value / other;
        return *this;
    }

    Mark Mark::operator/(int other) const {
        return Mark(m_value / other);
    }

    Mark& Mark::operator=(int value) {
        m_value = value;
        return *this;
    }

    Mark& Mark::operator=(char type) {
        m_type = MARK;
        if (type == GRADE || type == GPA) {
            m_type = type;
        }
        return *this;
    }

    double Mark::raw() const {
        return m_value;
    }

    Mark::operator int() const {
        int value = -1;
        if (isValid()) {
            value = int(std::round(m_value < 0 ? 0 : m_value));
        }
        return value;
    }
    Mark::operator bool() const {
        return isValid();
    }


    // returns the GPA not the m_value!!!
    Mark::operator double() const {
        double gpa = 0;
        if (!isValid()) gpa = -1;
        else gpa = m_value * 0.04;
        return gpa;
    }

    Mark::operator const char* () const {
        // removes the constantness of m_grade!
        // You will learn this at the end of the semester.
        char* grade = const_cast<char*>(m_grade);

        int value = int(*this);
        grade[1] = grade[2] = '\0';
        if (value < 0 || value > 100) grade[0] = 'X';
        else if (value >= 90) grade[0] = 'A', grade[1] = '+';
        else if (value >= 80) grade[0] = 'A';
        else if (value >= 75) grade[0] = 'B', grade[1] = '+';
        else if (value >= 70) grade[0] = 'B';
        else if (value >= 65) grade[0] = 'C', grade[1] = '+';
        else if (value >= 60) grade[0] = 'C';
        else if (value >= 55) grade[0] = 'D', grade[1] = '+';
        else if (value >= 50) grade[0] = 'D';
        else grade[0] = 'F';
        return m_grade;
    }

    // student helper function implementations go here
    std::ostream& Mark::display(std::ostream& os)
    {
        if (!isValid())
        {
            if (m_type == GRADE)
            {
                os << "**";
            }

            else
                os << "***";

        }

        if (m_type == GPA)
        {
            double markDoubleCast = static_cast<double>(*this);
            os.setf(std::ios::left);
            os.fill('_');
            os.width(3);
            os << markDoubleCast;
        }

        if (m_type == MARK)
        {
            os.fill('_');
            os.width(3);
            os.setf(std::ios::right);
            os << int(*this);
        }

        if (m_type == GRADE)
        {
            os.width(3);
            os.setf(std::ios::left);
            os.fill('_');
            os << (const char*)(*this);
        }
        return os;
    }

    std::ostream& display(const Mark& obj,char dispType, std::ostream& os)
    {
        Mark temp = obj;

        temp = MARK;
        temp.display(os);

        if (dispType != MARK)
        {
            os << ': ';
            temp = dispType;
            temp.display(os);
        }
        return os;
    }

    std::ostream& operator<<(std::ostream& os, Mark& m)
    {
        
        return m.display(os);
    }

    std::istream& operator >> (std::istream& is, Mark& m) {
        Mark temp = m;
        int val;
        bool check = false;

        do {
            std::cout << "Please enter the mark:\n> ";
            is >> val;
            if (val <= 0)
                std::cout << "Invalid integer, try again.\n> ";

            char ch = is.get();

            if (ch != '\n') {
                std::cout << "Invalid trailing characters, try again.\n> ";
                is.ignore(10000, '\n'); //Apparently this is the flush operator to clear the string buffer, a concept that escapes me always...
            }

            if (val < 0 || val > 100)
            {
                std::cout << "Invalid mark.  Enter a value between 0 and 100.\n> ";
            }
            m = val;
            check = true;
        } while (!check);

        std::cout << "You entered: " << m << endl;
        return is;
    }

    std::ifstream& operator>> (std::ifstream& is, Mark& m) { 
        Mark temp = m;

        char c;
        int val;
        char type;

        is >> val;
        is >> c;
        is >> type;

        if (is) {
            m = val;
            m = type;
        }
        

        return is;
    }

    double operator+(double value, const Mark& m)  {
        return value + m.raw();
    }
    int operator+(int value, const Mark& m)  {
        return value + int(m);
    }

    double operator-(double value, const Mark& m) {
        return value - m.raw();
    }

    int operator-(int value, const Mark& m) {
        return value - int(m);
    }

    double operator/(double other, const Mark& m) {
        return other / int(m.m_value);
    }

    int operator/(int value, const Mark& m) {
        int round = int(std::round(m.m_value));
        return value / round;
    }
}