#include "Medicine.h"
#include <iomanip>

Medicine::Medicine()
    : Item(), activeSubstance(), prescriptionRequired(false) {
}

Medicine::Medicine(const std::string& name, double price, const Date& releaseDate,
    const std::string& activeSubstance, bool prescriptionRequired)
    : Item(name, price, releaseDate),
    activeSubstance(activeSubstance),
    prescriptionRequired(prescriptionRequired) {
}

const std::string& Medicine::getActiveSubstance() const { return activeSubstance; }
bool Medicine::isPrescriptionRequired() const { return prescriptionRequired; }

void Medicine::setActiveSubstance(const std::string& s) { activeSubstance = s; }
void Medicine::setPrescriptionRequired(bool v) { prescriptionRequired = v; }

void Medicine::print(std::ostream& os) const {
    Item::print(os);
    os << std::left
        << std::setw(25) << activeSubstance << " | "
        << std::setw(15) << (prescriptionRequired ? "Prescription" : "no Prescription") << " | ";
}

std::ostream& operator<<(std::ostream& os, const Medicine& m) {
    m.print(os);
    return os;
}
void Medicine::read(std::istream& is) {
    Item::read(is);                    
    if (is.fail()) return;

    std::cout << "Active substance: ";
    std::cin.ignore(99999, '\n');
    std::getline(is, activeSubstance);

    std::cout << "Prescription required (0/1): ";
    is >> prescriptionRequired;
    if (is.fail()) {
        is.clear();
        is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }
    is.ignore(99999, '\n');
}