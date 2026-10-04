#pragma once
#include<Windows.h>
#include"Service.h"
class Menu {
	Service& service;
public:
	Menu(Service& service) : service(service) {}

	void run();
	void print(int selected); 

	void chooseSort();
	void deleteItem();
	void searchItem();
	void addItem();
	void editItem();

};