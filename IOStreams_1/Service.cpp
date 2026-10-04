#include"Service.h"

void Service::viewAll(bool isCart) const {
	if (isCart) {
		std::cout << cart;
	}
	else {
		std::cout << allPharma;
	}
}
void Service::sort(int type) const { 
	switch (type) {
	case '1': {
		allPharma.sortByTypeThenName();
		cart.sortByTypeThenName();
	}break;
	case '2': {
		allPharma.sortByPrice();
		cart.sortByPrice();
	}break;
	case '3': {
		allPharma.sortByDate();
		cart.sortByDate();
	}break;
	}
}
bool Service::deleteItem(int num,bool isCart) const {
	if (isCart) {
		if (num < cart.getCount()) {
			cart.removeByName(cart[num - 1]->getName());
			return true;
		}
	}
	else {
		if (num < allPharma.getCount()) {
			allPharma.removeByName(allPharma[num - 1]->getName());
			return true;
		}
	}
	return false;
}
bool Service::editItem(int num, bool isCart) const {
	Item* edited = nullptr;
	if (isCart) {
		if (num < cart.getCount()) {
			edited = cart.findByName(cart[num - 1]->getName());
		}
		else {
			return false;
		}
	}
	else {
		if (num < allPharma.getCount()) {
			edited = allPharma.findByName(allPharma[num - 1]->getName());
		}
		else {
			return false;
		}
	}
	Item* reserveCopy = ItemFabric::create(edited->type());
	*reserveCopy = *edited;
	std::cin >> *edited;
	if (std::cin.fail()) {
		std::cin.ignore(999999, '\n');
		std::cin.clear();
		*edited = *reserveCopy;
		delete reserveCopy;
		return false;
	}
	else {
		return true;
	}
	return false;
}
std::string Service::searchItem(std::string name, bool isCart) {
	Item* finded = nullptr;
	if (isCart) {
		finded = cart.findByName(name);
	}
	else {
		finded = allPharma.findByName(name);
	}
	if (finded != nullptr) {
		std::cout << *finded;
		return "\n";
	}
	else {
		return "not found...";
	}
}
bool Service::add() {
	system("cls");
	std::cout << "Add menu:\n"
		<< "  1 - Create new item in ALL\n"
		<< "  2 - Move item from ALL to CART\n"
		<< "Choose: ";

	int mode;
	std::cin >> mode;
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(99999, '\n');
		return false;
	}
	std::cin.ignore(99999, '\n');

	if (mode == 1) {
		std::cout << "Type (1-Tablets, 2-Liquid, 3-Device, 4-Parapharm): ";
		int type;
		std::cin >> type;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(99999, '\n');
			return false;
		}
		std::cin.ignore(99999, '\n');

		Item* obj = ItemFabric::create(type);
		if (!obj) return false;

		std::cin >> *obj;            
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(99999, '\n');
			delete obj;
			return false;
		}

		allPharma.add(obj);
		return true;
	}
	else if (mode == 2) {
		std::cout << allPharma;   
		std::cout << "Number in ALL: ";
		int num;
		std::cin >> num;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(99999, '\n');
			return false;
		}
		std::cin.ignore(99999, '\n');

		if (num < 1 || num > allPharma.getCount()) return false;

		Item* obj = allPharma.release(num - 1);
		if (!obj) return false;

		cart.add(obj);
		return true;
	}

	return false;
}