#include"Menu.h"
#include"Filler.h"

int main() {
	SetConsoleCP('1251');

	ItemArray all;
	fill(all);
	ItemArray cart;
	Service service(all, cart);
	Menu menu(service);

	menu.run();
	return 0;
}

