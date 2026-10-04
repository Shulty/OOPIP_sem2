#include "MedicalDevice.h"
#include <iomanip>

MedicalDevice::MedicalDevice()
    : Item(), material(), sterile(false), reusable(false) {
}

MedicalDevice::MedicalDevice(const std::string& name, double price, const Date& releaseDate,
    const std::string& material, bool sterile, bool reusable)
    : Item(name, price, releaseDate),
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
    return "Medical Device";
};
void MedicalDevice::print(std::ostream& os) const {
    Item::print(os);
    os << std::left
        << std::setw(25) << material << " | "
        << std::setw(15
        ) << (sterile ? "sterile" : "not sterile") << " | "
        << std::setw(36) << (reusable ? "reusable" : "unreusable") << " | ";
}


std::ostream& operator<<(std::ostream& os, const MedicalDevice& d) {
    d.print(os);
    return os;
}
void MedicalDevice::read(std::istream& is) {
    Item::read(is);
    if (is.fail()) return;

    std::cout << "Material: ";
    std::cin.ignore(99999, '\n');
    std::getline(is, material);

    std::cout << "Sterile (0/1): ";
    is >> sterile;
    if (is.fail()) {
        is.clear(); is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }

    std::cout << "Reusable (0/1): ";
    is >> reusable;
    if (is.fail()) {
        is.clear(); is.ignore(99999, '\n');
        is.setstate(std::ios::failbit);
        return;
    }
    is.ignore(99999, '\n');
}

Item* MedicalDevice::clone() const {
    return new MedicalDevice(*this);
}