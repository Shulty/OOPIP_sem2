#pragma once
#include "SubstanceItem.h"

class Parapharmaceutical : public SubstanceItem {
private:
    std::string category;
    bool hypoallergenic;

public:
    Parapharmaceutical();
    Parapharmaceutical(const std::string& name, const Money& price, const Date& releaseDate,
        const std::string& activeSubstance,
        const std::string& category, bool hypoallergenic, int amount = 0);
    ~Parapharmaceutical() override = default;

    const std::string& getCategory() const;
    bool isHypoallergenic() const;

    void setCategory(const std::string& c);
    void setHypoallergenic(bool v);

    int type() const override;
    std::string getTypeName() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    void write(std::ostream& os) const override;
    void readBin(std::istream& is) override;
    Item* clone() const override;

    friend std::ostream& operator<<(std::ostream& os, const Parapharmaceutical& p);
};