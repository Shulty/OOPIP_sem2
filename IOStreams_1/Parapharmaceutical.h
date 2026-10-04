#pragma once
#include "Item.h"

class Parapharmaceutical : public Item {
private:
    std::string category;
    bool hypoallergenic;

public:
    Parapharmaceutical();
    Parapharmaceutical(const std::string& name, double price, const Date& releaseDate,
        const std::string& category, bool hypoallergenic);
    ~Parapharmaceutical() override = default;

    const std::string& getCategory() const;
    bool isHypoallergenic() const;

    void setCategory(const std::string& c);
    void setHypoallergenic(bool v);

    int type() const override;
    std::string getTypeName() const override;
    void print(std::ostream& os) const override;
    void read(std::istream& is) override;
    Item* clone() const override;
    friend std::ostream& operator<<(std::ostream& os, const Parapharmaceutical& p);
};