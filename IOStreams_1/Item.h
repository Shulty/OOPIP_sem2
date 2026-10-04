#pragma once
#include <string>
#include <iostream>
#include "Date.h"

class Item {
protected:
    std::string name;
    double price;
    Date releaseDate;

public:
    Item();
    Item(const std::string& name, double price, const Date& releaseDate);
    virtual ~Item() = default;

    const std::string& getName() const;
    double getPrice() const;
    Date getReleaseDate() const;

    void setName(const std::string& name);
    void setPrice(double price);
    void setReleaseDate(const Date& releaseDate);

    virtual int type() const = 0;
    virtual std::string getTypeName() const = 0;
    virtual void print(std::ostream& os) const;
    virtual void read(std::istream& is);        

    virtual Item* clone() const = 0;             

    friend std::istream& operator>>(std::istream& is, Item& s);
    friend std::ostream& operator<<(std::ostream& os, const Item& s);
};