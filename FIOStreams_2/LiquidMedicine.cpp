#include "LiquidMedicine.h"
#include <iomanip>

LiquidMedicine::LiquidMedicine()
	: Medicine(), volumeMl(0.0), form() {
}

LiquidMedicine::LiquidMedicine(const std::string& name, const Money& price, const Date& releaseDate,
	const std::string& activeSubstance, bool prescriptionRequired,
	double volumeMl, const std::string& form, int amount)
	: Medicine(name, price, releaseDate, activeSubstance, prescriptionRequired, amount),
	volumeMl(volumeMl), form(form) {
}

double LiquidMedicine::getVolumeMl() const { return volumeMl; }
const std::string& LiquidMedicine::getForm() const { return form; }

void LiquidMedicine::setVolumeMl(double v) { volumeMl = v; }
void LiquidMedicine::setForm(const std::string& f) { form = f; }

int LiquidMedicine::type() const { return 2; }
std::string LiquidMedicine::getTypeName() const {
	return "Жидкое лекарство";
}

void LiquidMedicine::print(std::ostream& os) const {
	Medicine::print(os);
	os << std::left
		<< std::setw(10) << volumeMl << " ml | "
		<< std::setw(15) << form << " | ";
}

std::istream& operator>>(std::istream& is, LiquidMedicine& l) {
	l.read(is);
	return is;
}

std::ostream& operator<<(std::ostream& os, const LiquidMedicine& l) {
	l.print(os);
	return os;
}

void LiquidMedicine::read(std::istream& is) {
	Medicine::read(is);
	if (is.fail()) return;

	std::cout << "Объем (мл): ";
	is >> volumeMl;
	if (is.fail() || volumeMl < 0) {
		is.clear();
		is.ignore(99999, '\n');
		is.setstate(std::ios::failbit);
		return;
	}
	is.ignore(99999, '\n');

	std::cout << "Форма: ";
	std::getline(is, form);
	if (is.fail()) is.setstate(std::ios::failbit);
}

void LiquidMedicine::write(std::ostream& os) const {
	Medicine::write(os);
	os.write(reinterpret_cast<const char*>(&volumeMl), sizeof(volumeMl));
	writeString(os, form);
}

void LiquidMedicine::readBin(std::istream& is) {
	Medicine::readBin(is);
	if (is.fail()) return;
	is.read(reinterpret_cast<char*>(&volumeMl), sizeof(volumeMl));
	if (is.fail() || volumeMl < 0) { is.setstate(std::ios::failbit); return; }
	readString(is, form);
}

Item* LiquidMedicine::clone() const {
	return new LiquidMedicine(*this);
}
