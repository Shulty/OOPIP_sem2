#include "Item.h"
#include <iomanip>

Item::Item()
    : name(), price(Money::fromRubles(0.0)), releaseDate(), amount(0) {
}

Item::Item(const std::string& name, const Money& price, const Date& releaseDate, int amount)
    : name(name), price(price), releaseDate(releaseDate), amount(amount) {
    if (this->amount < 0) this->amount = 0;
}


const std::string& Item::getName() const { return name; }
Money             Item::getPrice() const { return price; }
Date               Item::getReleaseDate() const { return releaseDate; }
int                Item::getAmount() const { return amount; }

void Item::setName(const std::string& name) { this->name = name; }

void Item::setPrice(const Money& price) { this->price = price; }

void Item::setReleaseDate(const Date& releaseDate) {
    this->releaseDate = releaseDate;
}

void Item::setAmount(int amount) {
    if (amount < 0) return;
    this->amount = amount;
}


void Item::print(std::ostream& os) const {
    os.setf(std::ios::showpoint);
    os << std::left
        << std::setw(30) << getTypeName() << " | "
        << std::setw(30) << name << " | "
        <<std::right<< std::setw(9) << price << " | "
        <<std::left<< std::setw(12) << releaseDate << " | "
        << std::setw(6) << amount << " шт | ";
    os.unsetf(std::ios::showpoint);
}


void Item::read(std::istream& is) {
    std::cout << "Название: \n";
    //std::cin.ignore(99999, '\n');
    std::getline(is, name);
    if (is.fail()) return;

    std::cout << "Цена: ";
    is >> price;
    if (is.fail() || !price.isOk()) {
        is.clear();
        is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }
    is.ignore(99999, '\n');

    std::cout << "Дата выпуска (дд.мм.гггг): ";
    is >> releaseDate;
    if (is.fail()) return;

    std::cout << "Количество: ";
    is >> amount;
    if (is.fail() || amount < 0) {
        is.clear();
        is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }
    is.ignore(99999, '\n');
}


std::istream& operator>>(std::istream& is, Item& s) {
    s.read(is);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Item& s) {
    s.print(os);
    return os;
}

void Item::writeString(std::ostream& os, const std::string& s) {
    int len = static_cast<int>(s.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    os.write(s.data(), len);
}

void Item::readString(std::istream& is, std::string& s) {
    int len = 0;
    is.read(reinterpret_cast<char*>(&len), sizeof(len));
    if (is.fail() || len < 0 || len > 100000) { is.setstate(std::ios::failbit); return; }
    s.resize(len);
    is.read(&s[0], len);
    if (is.fail()) is.setstate(std::ios::failbit);
}

void Item::writeBase(std::ostream& os) const {
    writeString(os, name);
    price.write(os);
    releaseDate.write(os);
    os.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
}

void Item::readBase(std::istream& is) {
    readString(is, name);
    if (is.fail()) return;
    price.read(is);
    if (is.fail()) return;
    releaseDate.read(is);
    if (is.fail()) return;
    is.read(reinterpret_cast<char*>(&amount), sizeof(amount));
    if (is.fail() || amount < 0) is.setstate(std::ios::failbit);
}