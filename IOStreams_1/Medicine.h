#pragma once
#include "Item.h"

class Medicine : public Item {
protected:
    std::string activeSubstance;
    bool prescriptionRequired;

public:
    Medicine();
    Medicine(const std::string& name, double price, const Date& releaseDate,
        const std::string& activeSubstance, bool prescriptionRequired);
    ~Medicine() override = default;

    const std::string& getActiveSubstance() const;
    bool isPrescriptionRequired() const;

    void setActiveSubstance(const std::string& s);
    void setPrescriptionRequired(bool v);

    int type() const = 0;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    friend std::istream& operator>>(std::istream& is, Medicine& m);
    friend std::ostream& operator<<(std::ostream& os, const Medicine& m);
};