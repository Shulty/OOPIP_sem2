#pragma once
#include "Medicine.h"

class Tablets : public Medicine {
private:
    double dosageMg;
    int countInPack;

public:
    Tablets();
    Tablets(const std::string& name, const Money& price, const Date& releaseDate,
        const std::string& activeSubstance, bool prescriptionRequired,
        double dosageMg, int countInPack, int amount = 0);
    ~Tablets() override = default;

    double getDosageMg() const;
    int    getCountInPack() const;

    void setDosageMg(double v);
    void setCountInPack(int v);

    int type() const override;
    std::string getTypeName() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    void write(std::ostream& os) const override;
    void readBin(std::istream& is) override;
    Item* clone() const override;

    friend std::ostream& operator<<(std::ostream& os, const Tablets& t);
};