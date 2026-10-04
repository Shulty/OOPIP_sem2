#include "Parapharmaceutical.h"
#include <iomanip>

Parapharmaceutical::Parapharmaceutical()
    : Item(), category(), hypoallergenic(false) {
}

Parapharmaceutical::Parapharmaceutical(const std::string& name, double price, const Date& releaseDate,
    const std::string& category, bool hypoallergenic)
    : Item(name, price, releaseDate),
    category(category), hypoallergenic(hypoallergenic) {
}

const std::string& Parapharmaceutical::getCategory() const { return category; }
bool Parapharmaceutical::isHypoallergenic() const { return hypoallergenic; }

void Parapharmaceutical::setCategory(const std::string& c) { category = c; }
void Parapharmaceutical::setHypoallergenic(bool v) { hypoallergenic = v; }

int Parapharmaceutical::type() const { return 4; }
std::string Parapharmaceutical::getTypeName() const {
    return "Parapharmaceutica";
};
void Parapharmaceutical::print(std::ostream& os) const {
    Item::print(os);
    os << std::left
        << std::setw(25) << category << " | "
        << std::setw(54) << (hypoallergenic ? "hypoallergenic" : "default") << " | ";
}

std::ostream& operator<<(std::ostream& os, const Parapharmaceutical& p) {
    p.print(os);
    return os;
}
void Parapharmaceutical::read(std::istream& is) {
    Item::read(is);
    if (is.fail()) return;

    std::cout << "Category: ";
    std::cin.ignore(99999, '\n');
    std::getline(is, category);

    std::cout << "Hypoallergenic (0/1): ";
    is >> hypoallergenic;
    if (is.fail()) {
        is.clear(); is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }
    is.ignore(99999, '\n');
}

Item* Parapharmaceutical::clone() const {
    return new Parapharmaceutical(*this);
}