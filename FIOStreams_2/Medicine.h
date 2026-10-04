#pragma once
#include "SubstanceItem.h"

class Medicine : public SubstanceItem {
protected:
    bool prescriptionRequired;

public:
    Medicine();
    Medicine(const std::string& name, const Money& price, const Date& releaseDate,
        const std::string& activeSubstance, bool prescriptionRequired, int amount = 0);
    ~Medicine() override = default;

    bool isPrescriptionRequired() const;
    void setPrescriptionRequired(bool v);

    int type() const = 0;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    void write(std::ostream& os) const override;
    void readBin(std::istream& is) override;

    friend std::ostream& operator<<(std::ostream& os, const Medicine& m);
};