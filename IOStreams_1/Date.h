#pragma once
#include <iostream>

typedef unsigned short ushort;

class Date {
public:
    static Date now();
private:
    ushort day;
    ushort month;
    ushort year;

public:
    Date();
    Date(ushort day, ushort month, ushort year);
    Date(const Date& other);

    ushort getDay() const;
    ushort getMonth() const;
    ushort getYear() const;

    void setDay(ushort day);
    void setMonth(ushort month);
    void setYear(ushort year);

    bool isOk();

    int operator-(const Date& other) const;
    Date& operator=(const Date& other);

    friend bool operator<(const Date& first, const Date& second);
    friend bool operator>(const Date& first, const Date& second);
    friend bool operator<=(const Date& first, const Date& second);
    friend bool operator>=(const Date& first, const Date& second);

    friend std::istream& operator>>(std::istream& is, Date& d);
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};
