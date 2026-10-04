#pragma once
#include"ItemArray.h"

#include "Tablets.h"          
#include "LiquidMedicine.h"      
#include "MedicalDevice.h"      
#include "Parapharmaceutical.h" 

#include "ItemFabric.h"
 
class Service {
    ItemArray& allPharma;
    ItemArray& cart;
public:
    Service(ItemArray& all, ItemArray& mine)
        : allPharma(all), cart(mine) {
    }
    void viewAll(bool isCart) const;
    void sort(int type) const;
    bool deleteItem(int num, bool isCart) const;
    bool editItem(int num, bool isCart) const;

    std::string searchItem(std::string name,bool isCart);
    bool add();
};