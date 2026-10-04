#include "MedicalDevice.h"
#include <iomanip>

MedicalDevice::MedicalDevice()
	: Item(), material(), sterile(false), reusable(false) {
}

MedicalDevice::MedicalDevice(const std::string& name, const Money& price, const Date& releaseDate,
	const std::string& material, bool sterile, bool reusable, int amount)
	: Item(name, price, releaseDate, amount),
	material(material), sterile(sterile), reusable(reusable) {
}

const std::string& MedicalDevice::getMaterial() const { return material; }
bool MedicalDevice::isSterile() const { return sterile; }
bool MedicalDevice::isReusable() const { return reusable; }

void MedicalDevice::setMaterial(const std::string& m) { material = m; }
void MedicalDevice::setSterile(bool v) { sterile = v; }
void MedicalDevice::setReusable(bool v) { reusable = v; }

int MedicalDevice::type() const { return 3; }
std::string MedicalDevice::getTypeName() const {
	return "Медицинское изделие";
}

void MedicalDevice::print(std::ostream& os) const {
	Item::print(os);
	os << std::left
		<< std::setw(15) << material << " | "
		<< std::setw(10) << (sterile ? "Стерил" : "Нестерил") << " | "
		<< std::setw(12) << (reusable ? "Многорас" : "Однораз") << " | ";
}

std::istream& operator>>(std::istream& is, MedicalDevice& d) {
	d.read(is);
	return is;
}

std::ostream& operator<<(std::ostream& os, const MedicalDevice& d) {
	d.print(os);
	return os;
}

void MedicalDevice::read(std::istream& is) {
	Item::read(is);
	if (is.fail()) return;

	std::cout << "Материал: ";
	std::getline(is, material);
	if (is.fail()) return;

	std::cout << "Стерильное (0/1): ";
	is >> sterile;
	if (is.fail()) {
		is.clear();
		is.ignore(99999, '\n');
		is.setstate(std::ios::failbit);
		return;
	}
	is.ignore(99999, '\n');

	std::cout << "Многоразовое (0/1): ";
	is >> reusable;
	if (is.fail()) {
		is.clear();
		is.ignore(99999, '\n');
		is.setstate(std::ios::failbit);
		return;
	}
	is.ignore(99999, '\n');
}

void MedicalDevice::write(std::ostream& os) const {
	Item::writeBase(os);
	writeString(os, material);
	os.write(reinterpret_cast<const char*>(&sterile), sizeof(sterile));
	os.write(reinterpret_cast<const char*>(&reusable), sizeof(reusable));
}

void MedicalDevice::readBin(std::istream& is) {
	Item::readBase(is);
	if (is.fail()) return;
	readString(is, material);
	if (is.fail()) return;
	is.read(reinterpret_cast<char*>(&sterile), sizeof(sterile));
	is.read(reinterpret_cast<char*>(&reusable), sizeof(reusable));
	if (is.fail()) is.setstate(std::ios::failbit);
}

Item* MedicalDevice::clone() const {
	return new MedicalDevice(*this);
}
