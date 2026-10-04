#include "Item.h"
#include <iomanip>

Item::Item()
    : name(), price(0.0), releaseDate() {
}

Item::Item(const std::string& name, double price, const Date& releaseDate)
    : name(name), price(price), releaseDate(releaseDate) {
}

const std::string& Item::getName() const { return name; }
double Item::getPrice() const { return price; }
Date Item::getReleaseDate() const { return releaseDate; }

void Item::setName(const std::string& name) { this->name = name; }
void Item::setPrice(double price) { this->price = price; }
void Item::setReleaseDate(const Date& releaseDate) { this->releaseDate = releaseDate; }

void Item::print(std::ostream& os) const {
    os.setf(std::ios::showpoint);
    os << std::left
        << std::setw(30) << getTypeName() << " | "
        << std::setw(30) << name << " | "
        << '$' << std::setw(9)<<std::fixed<<std::setprecision(2) << price << " | "
        << std::setw(12) << releaseDate << " | ";
    os.unsetf(std::ios::showpoint);
}

void Item::read(std::istream& is) {
    std::cout << "Name: \n";
    std::cin.ignore(99999, '\n');
    std::getline(is, name);
    if (is.fail()) return;

    std::cout << "Price: ";
    is >> price;
    if (is.fail() || price < 0) {
        is.clear();
        is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }
    is.ignore(99999, '\n');

    std::cout << "Release date (dd.mm.yyyy): ";
    is >> releaseDate;
}

std::istream& operator>>(std::istream& is, Item& s) {
    s.read(is);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Item& s) {
    s.print(os);
    return os;
}