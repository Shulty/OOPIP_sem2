#include "Date.h"
#include <cstdlib>
#include <iomanip>
#include <chrono>

Date::Date() {
    day = month = year = 0;
}

Date::Date(ushort day, ushort month, ushort year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(const Date& other)
    : day(other.day), month(other.month), year(other.year) {
}

ushort Date::getDay() const {
    return day;
}

ushort Date::getMonth() const {
    return month;
}

ushort Date::getYear() const {
    return year;
}

void Date::setDay(ushort day) {
    this->day = day;
}

void Date::setMonth(ushort month) {
    this->month = month;
}

void Date::setYear(ushort year) {
    this->year = year;
}

bool Date::isOk() {
    return (day > 0 && day < 32) && (month > 0 && month < 13) && (year > 0);
}

int Date::operator-(const Date& other) const {
    int result = day - other.day
        + month * 30 - other.month * 30
        + year * 365 - other.year * 365;
    return abs(result);
}

Date& Date::operator=(const Date& other) {
    if (this != &other) {
        day = other.day;
        month = other.month;
        year = other.year;
    }
    return *this;
}

bool operator<(const Date& first, const Date& second) {
    return (first.year * 365 + first.month * 30 + first.day) <
        (second.year * 365 + second.month * 30 + second.day);
}

bool operator>(const Date& first, const Date& second) {
    return (first.year * 365 + first.month * 30 + first.day) >
        (second.year * 365 + second.month * 30 + second.day);
}

bool operator<=(const Date& first, const Date& second) {
    return !(first > second);
}

bool operator>=(const Date& first, const Date& second) {
    return !(first < second);
}

std::istream& operator>>(std::istream& is, Date& d) {
    ushort day, month, year;
    char dot1 = 0, dot2 = 0;

    is >> day;
    if (is.fail()) {
        is.clear();
        is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return is;
    }
    is >> dot1 >> month;
    if (is.fail()) {
        is.clear();
        is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return is;
    }
    is >> dot2 >> year;
    if (is.fail() || dot1 != '.' || dot2 != '.') {
        is.clear();
        is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return is;
    }
    Date temp(day, month, year);
    if (!temp.isOk()) {
        is.setstate(std::ios::failbit);
        return is;
    }
    d = temp;
    return is;
}

std::ostream& operator<<(std::ostream& os, const Date& date) {
    std::ios::fmtflags oldFlags = os.flags();
    char oldFill = os.fill();

    os << std::setfill('0') << std::setiosflags(std::ios::right)
        << std::setw(2) << date.day << "."
        << std::setw(2) << date.month << "."
        << std::setw(4) << date.year;

    os.flags(oldFlags);
    os.fill(oldFill);

    return os;
}

Date Date::now() {
    using namespace std::chrono;

    auto tp = system_clock::now();
    zoned_time zt{ "Europe/Moscow", tp };
    auto localDays = floor<days>(zt.get_local_time());
    year_month_day ymd{ localDays };

    if (!ymd.ok()) {
        return Date(10, 4, 2026);
    }

    return Date(
        static_cast<ushort>(static_cast<unsigned>(ymd.day())),
        static_cast<ushort>(static_cast<unsigned>(ymd.month())),
        static_cast<int>(ymd.year())
    );
}

void Date::write(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&day), sizeof(day));
    os.write(reinterpret_cast<const char*>(&month), sizeof(month));
    os.write(reinterpret_cast<const char*>(&year), sizeof(year));
}

void Date::read(std::istream& is) {
    is.read(reinterpret_cast<char*>(&day), sizeof(day));
    is.read(reinterpret_cast<char*>(&month), sizeof(month));
    is.read(reinterpret_cast<char*>(&year), sizeof(year));
    if (is.fail() || !isOk()) is.setstate(std::ios::failbit);
}