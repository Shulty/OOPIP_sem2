#include "Parapharmaceutical.h"
#include <iomanip>

Parapharmaceutical::Parapharmaceutical()
	: SubstanceItem(), category(), hypoallergenic(false) {
}

Parapharmaceutical::Parapharmaceutical(const std::string& name, const Money& price, const Date& releaseDate,
	const std::string& activeSubstance,
	const std::string& category, bool hypoallergenic, int amount)
	: SubstanceItem(name, price, releaseDate, activeSubstance, amount),
	category(category), hypoallergenic(hypoallergenic) {
}

const std::string& Parapharmaceutical::getCategory() const { return category; }
bool Parapharmaceutical::isHypoallergenic() const { return hypoallergenic; }

void Parapharmaceutical::setCategory(const std::string& c) { category = c; }
void Parapharmaceutical::setHypoallergenic(bool v) { hypoallergenic = v; }

int Parapharmaceutical::type() const { return 4; }
std::string Parapharmaceutical::getTypeName() const {
	return "Парафармацевтический";
}

void Parapharmaceutical::print(std::ostream& os) const {
	SubstanceItem::print(os);
	os << std::left
		<< std::setw(20) << category << " | "
		<< std::setw(12) << (hypoallergenic ? "Гипоаллер" : "Обычный") << " | ";
}

std::ostream& operator<<(std::ostream& os, const Parapharmaceutical& p) {
	p.print(os);
	return os;
}

void Parapharmaceutical::read(std::istream& is) {
	SubstanceItem::read(is);
	if (is.fail()) return;

	std::cout << "Категория: ";
	std::getline(is, category);
	if (is.fail()) return;

	std::cout << "Гипоаллергенное (0/1): ";
	is >> hypoallergenic;
	if (is.fail()) {
		is.clear();
		is.ignore(99999, '\n');
		is.setstate(std::ios::failbit);
		return;
	}
	is.ignore(99999, '\n');
}

void Parapharmaceutical::write(std::ostream& os) const {
	SubstanceItem::write(os);
	writeString(os, category);
	os.write(reinterpret_cast<const char*>(&hypoallergenic), sizeof(hypoallergenic));
}

void Parapharmaceutical::readBin(std::istream& is) {
	SubstanceItem::readBin(is);
	if (is.fail()) return;
	readString(is, category);
	if (is.fail()) return;
	is.read(reinterpret_cast<char*>(&hypoallergenic), sizeof(hypoallergenic));
	if (is.fail()) is.setstate(std::ios::failbit);
}

Item* Parapharmaceutical::clone() const {
	return new Parapharmaceutical(*this);
}
