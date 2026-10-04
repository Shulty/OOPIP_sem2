#pragma once
#include "Medicine.h"

class LiquidMedicine : public Medicine {
private:
    double volumeMl;
    std::string form;

public:
    LiquidMedicine();
    LiquidMedicine(const std::string& name, const Money& price, const Date& releaseDate,
        const std::string& activeSubstance, bool prescriptionRequired,
        double volumeMl, const std::string& form, int amount = 0);
    ~LiquidMedicine() override = default;

    double getVolumeMl() const;
    const std::string& getForm() const;

    void setVolumeMl(double v);
    void setForm(const std::string& f);

    int type() const override;
    std::string getTypeName() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    void write(std::ostream& os) const override;
    void readBin(std::istream& is) override;
    Item* clone() const override;

    friend std::istream& operator>>(std::istream& is, LiquidMedicine& l);
    friend std::ostream& operator<<(std::ostream& os, const LiquidMedicine& l);
};