#pragma once
#include "ItemFabric.h"
#include "ItemArray.h"
#include "Tablets.h"
#include "LiquidMedicine.h"
#include "MedicalDevice.h"
#include "Parapharmaceutical.h"

inline void fill(ItemArray& arr) {
    // ================= Tablets (5) =================
    arr.add(new Tablets("Aspirin", 150.0, Date(1, 1, 2027),
        "Acetylsalicylic acid", false, 500.0, 20));

    arr.add(new Tablets("Paracetamol", 90.0, Date(15, 6, 2026),
        "Paracetamol", false, 500.0, 10));

    arr.add(new Tablets("Amoxicillin", 320.0, Date(1, 3, 2027),
        "Amoxicillin", true, 250.0, 16));

    arr.add(new Tablets("Analgin", 70.0, Date(10, 10, 2026),
        "Metamizole sodium", false, 500.0, 20));

    arr.add(new Tablets("Loratadine", 180.0, Date(1, 5, 2028),
        "Loratadine", false, 10.0, 30));

    // ================= LiquidMedicine (5) =================
    arr.add(new LiquidMedicine("Pertussin", 200.0, Date(1, 6, 2026),
        "Thyme", false, 100.0, "syrup"));

    arr.add(new LiquidMedicine("Corvalol", 120.0, Date(1, 12, 2027),
        "Phenobarbital", false, 25.0, "drops"));

    arr.add(new LiquidMedicine("Nazol", 250.0, Date(1, 9, 2026),
        "Oxymetazoline", false, 10.0, "spray"));

    arr.add(new LiquidMedicine("Iodine", 60.0, Date(1, 4, 2028),
        "Iodine", false, 25.0, "solution"));

    arr.add(new LiquidMedicine("Ambrobene", 310.0, Date(1, 2, 2027),
        "Ambroxol", false, 100.0, "syrup"));

    // ================= MedicalDevice (5) =================
    arr.add(new MedicalDevice("Sterile bandage", 50.0, Date(1, 12, 2030),
        "gauze", true, false));

    arr.add(new MedicalDevice("Syringe 5 ml", 15.0, Date(1, 8, 2029),
        "plastic", true, false));

    arr.add(new MedicalDevice("Rubber hot-water bottle", 400.0, Date(1, 1, 2035),
        "latex", false, true));

    arr.add(new MedicalDevice("Tonometer", 2500.0, Date(1, 7, 2032),
        "plastic", false, true));

    arr.add(new MedicalDevice("Electronic thermometer", 450.0, Date(1, 3, 2030),
        "plastic", false, true));

    // ================= Parapharmaceutical (5) =================
    arr.add(new Parapharmaceutical("Hand cream", 300.0, Date(1, 9, 2027),
        "cosmetics", true));

    arr.add(new Parapharmaceutical("Toothpaste", 180.0, Date(1, 5, 2028),
        "hygiene", false));

    arr.add(new Parapharmaceutical("Vitamin C", 220.0, Date(1, 11, 2027),
        "vitamins", true));

    arr.add(new Parapharmaceutical("Medicated shampoo", 550.0, Date(1, 4, 2028),
        "cosmetics", true));

    arr.add(new Parapharmaceutical("Wet wipes", 90.0, Date(1, 10, 2029),
        "hygiene", false));
}