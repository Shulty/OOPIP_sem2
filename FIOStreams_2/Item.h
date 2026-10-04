#pragma once
#include <string>
#include <iostream>
#include "Date.h"
#include "Money.h"

class Item {
protected:
    std::string name;
    Money price;
    Date releaseDate;
    int amount;

public:
    Item();
    Item(const std::string& name, const Money& price, const Date& releaseDate, int amount = 0);
    virtual ~Item() = default;

    const std::string& getName() const;
    Money getPrice() const;
    Date getReleaseDate() const;
    int getAmount() const;

    void setName(const std::string& name);
    void setPrice(const Money& price);
    void setReleaseDate(const Date& releaseDate);
    void setAmount(int amount);

    virtual int type() const = 0;
    virtual std::string getTypeName() const = 0;
    virtual void print(std::ostream& os) const;
    virtual void read(std::istream& is);

    virtual void write(std::ostream& os) const = 0;
    virtual void readBin(std::istream& is) = 0;

    virtual Item* clone() const = 0;

    friend std::istream& operator>>(std::istream& is, Item& s);
    friend std::ostream& operator<<(std::ostream& os, const Item& s);

protected:
    static void writeString(std::ostream& os, const std::string& s);
    static void readString(std::istream& is, std::string& s);
    void writeBase(std::ostream& os) const;
    void readBase(std::istream& is);
};