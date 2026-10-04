#pragma once
#include "Item.h"
#include "Tablets.h"
#include "LiquidMedicine.h"
#include "MedicalDevice.h"
#include "Parapharmaceutical.h"

class ItemFabric {
public:
    static Item* create(int type) {
        switch (type) {
        case 1: return new Tablets();
        case 2: return new LiquidMedicine();
        case 3: return new MedicalDevice();
        case 4: return new Parapharmaceutical();
        default: return nullptr;
        }
    }
};