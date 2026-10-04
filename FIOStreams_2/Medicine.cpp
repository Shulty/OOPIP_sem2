#include "Medicine.h"
#include <iomanip>

Medicine::Medicine()
	: SubstanceItem(), prescriptionRequired(false) {
}

Medicine::Medicine(const std::string& name, const Money& price, const Date& releaseDate,
	const std::string& activeSubstance, bool prescriptionRequired, int amount)
	: SubstanceItem(name, price, releaseDate, activeSubstance, amount),
	prescriptionRequired(prescriptionRequired) {
}

bool Medicine::isPrescriptionRequired() const { return prescriptionRequired; }
void Medicine::setPrescriptionRequired(bool v) { prescriptionRequired = v; }

void Medicine::print(std::ostream& os) const {
	SubstanceItem::print(os);
	os << std::left
		<< std::setw(15) << (prescriptionRequired ? "Нужен рецепт" : "Без рецепта") << " | ";
}

std::ostream& operator<<(std::ostream& os, const Medicine& m) {
	m.print(os);
	return os;
}

void Medicine::read(std::istream& is) {
	SubstanceItem::read(is);
	if (is.fail()) return;

	std::cout << "Требует рецепт (0/1): ";
	is >> prescriptionRequired;
	if (is.fail()) {
		is.clear();
		is.ignore(99999, '\n');
		is.setstate(std::ios::failbit);
		return;
	}
	is.ignore(99999, '\n');
}

void Medicine::write(std::ostream& os) const {
	SubstanceItem::write(os);
	os.write(reinterpret_cast<const char*>(&prescriptionRequired), sizeof(prescriptionRequired));
}

void Medicine::readBin(std::istream& is) {
	SubstanceItem::readBin(is);
	if (is.fail()) return;
	is.read(reinterpret_cast<char*>(&prescriptionRequired), sizeof(prescriptionRequired));
	if (is.fail()) is.setstate(std::ios::failbit);
}
