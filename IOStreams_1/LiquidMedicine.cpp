#include "LiquidMedicine.h"
#include <iomanip>

LiquidMedicine::LiquidMedicine()
    : Medicine(), volumeMl(0.0), form() {
}

LiquidMedicine::LiquidMedicine(const std::string& name, double price, const Date& releaseDate,
    const std::string& activeSubstance, bool prescriptionRequired,
    double volumeMl, const std::string& form)
    : Medicine(name, price, releaseDate, activeSubstance, prescriptionRequired),
    volumeMl(volumeMl), form(form) {
}

double LiquidMedicine::getVolumeMl() const { return volumeMl; }
const std::string& LiquidMedicine::getForm() const { return form; }

void LiquidMedicine::setVolumeMl(double v) { volumeMl = v; }
void LiquidMedicine::setForm(const std::string& f) { form = f; }

int LiquidMedicine::type() const { return 2; }
std::string LiquidMedicine::getTypeName() const {
    return "Liquid Medicine";
};
void LiquidMedicine::print(std::ostream& os) const {
    Medicine::print(os);
    os << std::left
        << std::setw(10) << volumeMl << " ml | "
        <<"form: " << std::setw(15) << form << "| ";
}

std::ostream& operator<<(std::ostream& os, const LiquidMedicine& l) {
    l.print(os);
    return os;
}
void LiquidMedicine::read(std::istream& is) {
    Medicine::read(is);
    if (is.fail()) return;

    std::cout << "Volume (ml): ";
    is >> volumeMl;
    if (is.fail() || volumeMl < 0) {
        is.clear(); is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }
    is.ignore(99999, '\n');

    std::cout << "Form: ";
    std::cin.ignore(99999, '\n');
    std::getline(is, form);
}

Item* LiquidMedicine::clone() const {
    return new LiquidMedicine(*this);
}