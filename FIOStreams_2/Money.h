#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

class Money {
private:
    long long kopecks;

public:
    Money();
    explicit Money(long long kopecks);
    static Money fromRubles(double rub);

    long long getKopecks() const;
    double    toRubles()   const;
    bool      isOk()       const;

    Money  operator+(const Money& other) const;
    Money  operator-(const Money& other) const;
    Money  operator*(long long k)        const;
    Money  operator/(long long k)        const;
    Money& operator+=(const Money& other);
    Money& operator-=(const Money& other);

    friend bool operator==(const Money& a, const Money& b);
    friend bool operator!=(const Money& a, const Money& b);
    friend bool operator< (const Money& a, const Money& b);
    friend bool operator> (const Money& a, const Money& b);
    friend bool operator<=(const Money& a, const Money& b);
    friend bool operator>=(const Money& a, const Money& b);

    friend std::ostream& operator<<(std::ostream& os, const Money& m);
    friend std::istream& operator>>(std::istream& is, Money& m);

    void write(std::ostream& os) const;
    void read(std::istream& is);

    static constexpr std::size_t binarySize = sizeof(long long);
};