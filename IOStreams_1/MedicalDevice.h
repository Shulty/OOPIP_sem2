#pragma once
#include "Item.h"

class MedicalDevice : public Item {
private:
    std::string material;
    bool        sterile;
    bool        reusable;

public:
    MedicalDevice();
    MedicalDevice(const std::string& name, double price, const Date& releaseDate,
        const std::string& material, bool sterile, bool reusable);
    ~MedicalDevice() override = default;

    const std::string& getMaterial() const;
    bool isSterile() const;
    bool isReusable() const;

    void setMaterial(const std::string& m);
    void setSterile(bool v);
    void setReusable(bool v);

    int type() const override;
    std::string getTypeName() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Item* clone() const override;

    friend std::istream& operator>>(std::istream& is, MedicalDevice& d);
    friend std::ostream& operator<<(std::ostream& os, const MedicalDevice& d);
};