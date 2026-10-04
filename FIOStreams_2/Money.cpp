#include "Money.h"
#include <iomanip>

Money::Money()
    : kopecks(0) {
}

Money::Money(long long kopecks)
    : kopecks(kopecks) {
}

Money Money::fromRubles(double rub) {
    return Money(static_cast<long long>(std::llround(rub * 100.0)));
}

long long Money::getKopecks() const { return kopecks; }
double    Money::toRubles()   const { return kopecks / 100.0; }
bool      Money::isOk()       const { return kopecks >= 0; }

Money Money::operator+(const Money& other) const {
    return Money(kopecks + other.kopecks);
}

Money Money::operator-(const Money& other) const {
    return Money(kopecks - other.kopecks);
}

Money Money::operator*(long long k) const {
    return Money(kopecks * k);
}

Money Money::operator/(long long k) const {
    if (k == 0) return Money(0);
    return Money(kopecks / k);
}

Money& Money::operator+=(const Money& other) {
    kopecks += other.kopecks;
    return *this;
}

Money& Money::operator-=(const Money& other) {
    kopecks -= other.kopecks;
    return *this;
}

bool operator==(const Money& a, const Money& b) { return a.kopecks == b.kopecks; }
bool operator!=(const Money& a, const Money& b) { return a.kopecks != b.kopecks; }
bool operator< (const Money& a, const Money& b) { return a.kopecks < b.kopecks; }
bool operator> (const Money& a, const Money& b) { return a.kopecks > b.kopecks; }
bool operator<=(const Money& a, const Money& b) { return a.kopecks <= b.kopecks; }
bool operator>=(const Money& a, const Money& b) { return a.kopecks >= b.kopecks; }

std::ostream& operator<<(std::ostream& os, const Money& m) {
    long long rub = m.kopecks / 100;
    long long kop = std::llabs(m.kopecks % 100);

    std::ios::fmtflags oldFlags = os.flags();
    char oldFill = os.fill();

    os << rub << '.'
        << std::setw(2) << std::setfill('0') << kop;

    os.flags(oldFlags);
    os.fill(oldFill);
    return os;
}

std::istream& operator>>(std::istream& is, Money& m) {
    std::string s;
    is >> s;
    if (is.fail()) return is;

    std::size_t dot = s.find('.');
    std::string rubPart = (dot == std::string::npos) ? s : s.substr(0, dot);
    std::string kopPart = (dot == std::string::npos) ? "" : s.substr(dot + 1);

    if (rubPart.empty() && kopPart.empty()) {
        is.setstate(std::ios::failbit);
        return is;
    }

    if (kopPart.size() == 1) kopPart += '0';
    else if (kopPart.size() > 2) kopPart = kopPart.substr(0, 2);
    else if (kopPart.empty()) kopPart = "00";

    long long rub = 0, kop = 0;
    std::size_t i = 0;
    bool negative = false;
    if (!rubPart.empty() && (rubPart[0] == '-' || rubPart[0] == '+')) {
        negative = (rubPart[0] == '-');
        i = 1;
    }
    for (; i < rubPart.size(); ++i) {
        if (!std::isdigit(static_cast<unsigned char>(rubPart[i]))) {
            is.setstate(std::ios::failbit);
            return is;
        }
        rub = rub * 10 + (rubPart[i] - '0');
    }
    for (std::size_t j = 0; j < kopPart.size(); ++j) {
        if (!std::isdigit(static_cast<unsigned char>(kopPart[j]))) {
            is.setstate(std::ios::failbit);
            return is;
        }
        kop = kop * 10 + (kopPart[j] - '0');
    }

    long long total = rub * 100 + kop;
    if (negative) total = -total;

    m = Money(total);
    return is;
}

void Money::write(std::ostream& os) const {
    os.write(reinterpret_cast<const char*>(&kopecks), sizeof(kopecks));
}

void Money::read(std::istream& is) {
    is.read(reinterpret_cast<char*>(&kopecks), sizeof(kopecks));
    if (is.fail() || !isOk()) {
        is.setstate(std::ios::failbit);
    }
}