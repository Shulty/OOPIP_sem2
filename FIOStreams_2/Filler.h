#pragma once
#include "ItemFabric.h"
#include "ItemArray.h"
#include "Tablets.h"
#include "LiquidMedicine.h"
#include "MedicalDevice.h"
#include "Parapharmaceutical.h"

inline void fill(ItemArray& arr) {
	// ================= Tablets (5) =================
	arr.add(new Tablets("Магне B6", Money::fromRubles(420.0), Date(1, 5, 2028),
		"Магний", false, 500.0, 20, 30));

	arr.add(new Tablets("Глицин", Money::fromRubles(60.0), Date(1, 12, 2028),
		"Глицин", false, 100.0, 50, 120));

	arr.add(new Tablets("Валидол", Money::fromRubles(45.0), Date(1, 8, 2027),
		"Ментол", false, 60.0, 10, 150));

	arr.add(new Tablets("Нитроглицерин", Money::fromRubles(70.0), Date(1, 3, 2027),
		"Нитроглицерин", false, 0.5, 20, 45));

	arr.add(new Tablets("Активированный уголь", Money::fromRubles(35.0), Date(1, 10, 2029),
		"Уголь", false, 250.0, 10, 200));

	// ================= LiquidMedicine (5) =================
	arr.add(new LiquidMedicine("Мирамистин", Money::fromRubles(360.0), Date(1, 6, 2028),
		"Бензилдиметил", false, 150.0, "Раствор", 20));

	arr.add(new LiquidMedicine("Хлоргексидин", Money::fromRubles(55.0), Date(1, 1, 2029),
		"Хлоргексидин", false, 100.0, "Раствор", 60));

	arr.add(new LiquidMedicine("Перекись водорода", Money::fromRubles(40.0), Date(1, 9, 2027),
		"Пероксид", false, 25.0, "Раствор", 80));

	arr.add(new LiquidMedicine("Йод", Money::fromRubles(30.0), Date(1, 4, 2027),
		"Йод", false, 10.0, "Раствор", 100));

	arr.add(new LiquidMedicine("Зелёнка", Money::fromRubles(35.0), Date(1, 7, 2027),
		"Бриллиантовый зелёный", false, 10.0, "Раствор", 90));

	// ================= MedicalDevice (5) =================
	arr.add(new MedicalDevice("Бинт эластичный", Money::fromRubles(190.0), Date(1, 2, 2030),
		"Ткань", true, false, 70));

	arr.add(new MedicalDevice("Пластырь бактерицидный", Money::fromRubles(85.0), Date(1, 11, 2028),
		"Нетканое", true, false, 300));

	arr.add(new MedicalDevice("Горчичники", Money::fromRubles(50.0), Date(1, 3, 2027),
		"Горчица", true, false, 120));

	arr.add(new MedicalDevice("Кружка Эсмарха", Money::fromRubles(550.0), Date(1, 8, 2031),
		"Резина", true, false, 15));

	arr.add(new MedicalDevice("Молокоотсос ручной", Money::fromRubles(780.0), Date(1, 5, 2030),
		"Пластик", true, false, 12));

	// ================= Parapharmaceutical (5) =================
	arr.add(new Parapharmaceutical("Бальзам для губ", Money::fromRubles(130.0), Date(1, 9, 2028),
		"Гигиенический", "Уход", false, 90));

	arr.add(new Parapharmaceutical("Крем детский", Money::fromRubles(210.0), Date(1, 6, 2028),
		"Детский", "Уход", false, 45));

	arr.add(new Parapharmaceutical("Влажные салфетки", Money::fromRubles(160.0), Date(1, 12, 2027),
		"Гигиенические", "Гигиена", true, 70));

	arr.add(new Parapharmaceutical("Пеленка впитывающая", Money::fromRubles(480.0), Date(1, 4, 2030),
		"Многослойная", "Уход", false, 35));

	arr.add(new Parapharmaceutical("Фильтр для воды", Money::fromRubles(990.0), Date(1, 10, 2032),
		"Бытовой", "Быт", false, 20));
}