#pragma once
#include "Item.h"

class SubstanceItem : public Item {
protected:
    std::string activeSubstance;

public:
    SubstanceItem();
    SubstanceItem(const std::string& name, const Money& price, const Date& releaseDate,
        const std::string& activeSubstance, int amount = 0);
    ~SubstanceItem() override = default;

    const std::string& getActiveSubstance() const;
    void setActiveSubstance(const std::string& s);

    void print(std::ostream& os) const override;
    void read(std::istream& is) override;

    void write(std::ostream& os) const override;
    void readBin(std::istream& is) override;
};