#include "Tablets.h"
#include <iomanip>

Tablets::Tablets()
    : Medicine(), dosageMg(0.0), countInPack(0) {
}

Tablets::Tablets(const std::string& name, double price, const Date& releaseDate,
    const std::string& activeSubstance, bool prescriptionRequired,
    double dosageMg, int countInPack)
    : Medicine(name, price, releaseDate, activeSubstance, prescriptionRequired),
    dosageMg(dosageMg), countInPack(countInPack) {
}

double Tablets::getDosageMg() const { return dosageMg; }
int    Tablets::getCountInPack() const { return countInPack; }

void Tablets::setDosageMg(double v) { dosageMg = v; }
void Tablets::setCountInPack(int v) { countInPack = v; }

int Tablets::type() const { return 1; }
std::string Tablets::getTypeName() const {
    return "Tablets";
};

void Tablets::print(std::ostream& os) const {
    Medicine::print(os);
    os << std::left
        << std::setw(10) << dosageMg << " mg | "
        << std::setw(15) << countInPack << " tbls | ";
}

std::ostream& operator<<(std::ostream& os, const Tablets& t) {
    t.print(os);
    return os;
}
void Tablets::read(std::istream& is) {
    Medicine::read(is);
    if (is.fail()) return;

    std::cout << "Dosage (mg): ";
    is >> dosageMg;
    if (is.fail() || dosageMg < 0) {
        is.clear(); is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }

    std::cout << "Count in pack: ";
    is >> countInPack;
    if (is.fail() || countInPack < 0) {
        is.clear(); is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }
    is.ignore(99999, '\n');
}

Item* Tablets::clone() const {
    return new Tablets(*this);
}