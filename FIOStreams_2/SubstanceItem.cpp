#include "SubstanceItem.h"
#include <iomanip>

SubstanceItem::SubstanceItem()
	: Item(), activeSubstance() {
}

SubstanceItem::SubstanceItem(const std::string& name, const Money& price, const Date& releaseDate,
	const std::string& activeSubstance, int amount)
	: Item(name, price, releaseDate, amount),
	activeSubstance(activeSubstance) {
}

const std::string& SubstanceItem::getActiveSubstance() const { return activeSubstance; }
void SubstanceItem::setActiveSubstance(const std::string& s) { activeSubstance = s; }

void SubstanceItem::print(std::ostream& os) const {
	Item::print(os);
	os << std::left << std::setw(25) << activeSubstance << " | ";
}

void SubstanceItem::read(std::istream& is) {
	Item::read(is);
	if (is.fail()) return;

	std::cout << "Введите основное вещество: \n";
	std::getline(is, activeSubstance);
}

void SubstanceItem::write(std::ostream& os) const {
	Item::writeBase(os);
	writeString(os, activeSubstance);
}

void SubstanceItem::readBin(std::istream& is) {
	Item::readBase(is);
	if (is.fail()) return;
	readString(is, activeSubstance);
}
