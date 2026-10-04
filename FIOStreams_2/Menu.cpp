#include "Menu.h"
#include <conio.h>
#include <iostream> 
#include <windows.h>

namespace {
    const char* items[] = { "1. Просмотр товаров", "2. Добавить товар", "3. Удалить товар",
                        "4. Редактировать товар", "5. Сортировка", "6. Найти товар",
                        "7. Моя корзина", "8. Сохранить в файл", "9. Загрузить из файла",
                        "0. Выход" };
    const int itemsCount = sizeof(items) / sizeof(items[0]);
    const int KEY_ENTER = 13;
    const int KEY_ARROW = 224;
    const int KEY_UP = 72;
    const int KEY_DOWN = 80;
}
void Menu::print(int selected) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    SetConsoleTextAttribute(hConsole, 10);
    for (int i = 0; i < itemsCount; ++i) {
        if (i == selected) {
            SetConsoleTextAttribute(hConsole, 7);
            std::cout << "> " << items[i] << '\n';
            SetConsoleTextAttribute(hConsole, 10);
        }
        else {
            std::cout << items[i] << '\n';
        }
    }
    SetConsoleTextAttribute(hConsole, 7);
}
void Menu::run() {
    int selected = 0; while (true) {
        Menu::print(selected);
        int key = _getch();
        if (key == KEY_ARROW || key == 0) {
            key = _getch();
            if (key == KEY_UP)
                selected = (selected - 1 + itemsCount) % itemsCount;
            else if (key == KEY_DOWN)
                selected = (selected + 1) % itemsCount;
        }
        else if (key == KEY_ENTER) {
            switch (selected) {
            case 0: service.viewAll(false); break;
            case 1: addItem(); break;
            case 2: deleteItem(); break;
            case 3: editItem(); break;
            case 4: chooseSort(); break;
            case 5: searchItem(); break;
            case 6: service.viewAll(true); break;
            case 7: saveToFile(); break;   
            case 8: loadFromFile(); break; 
            case 9: return;               
            }
            _getch();
        }
    }
}
void Menu::chooseSort() {
    system("cls");
    std::cout << "Выберите тип сортировки\n";
    std::cout << "1.По типу, затем по имени\n";
    std::cout << "2.По цене\n";
    std::cout << "3.По дате\n";
    int choose = _getch();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 10);
    std::cout << "Готово!\n";
    SetConsoleTextAttribute(hConsole, 7);
    service.sort(choose);
}
void Menu::deleteItem() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    std::cout << "Удалить из корзины (0) или из общего списка (1)? 0/1 \n";
    int choose = _getch();
    std::cout << "\n Номер: ";
    bool succesful = false;
    if (choose != '0' && choose != '1') return;
    int delIdx = -1;
    std::cin >> delIdx;
    if (std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(99999, '\n');
        succesful = false;
    }
    else {
        succesful = service.deleteItem(delIdx, choose == '0');
    }
    if (succesful) {
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "Успешно!";
    }
    else {
        SetConsoleTextAttribute(hConsole, 31);
        std::cout << "Ошибка!";
    }
    SetConsoleTextAttribute(hConsole, 7);
}
void Menu::editItem() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    std::cout << "Редактировать в корзине (0) или в общем списке (1)? 0/1 \n";
    int choose = _getch();
    std::cout << "\n Номер: ";
    bool succesful = false;
    if (choose != '0' && choose != '1') return;
    int delIdx = -1;
    std::cin >> delIdx;
    if (std::cin.fail()) {
        std::cin.clear(); std::cin.ignore(99999, '\n');
        succesful = false;
    }
    else {
        succesful = service.editItem(delIdx, choose == '0');
    }
    if (succesful) {
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "Успешно!";
    }
    else {
        SetConsoleTextAttribute(hConsole, 31);
        std::cout << "Ошибка!";
    }
    SetConsoleTextAttribute(hConsole, 7);
}
void Menu::searchItem() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    std::cout << "Поиск в корзине (0) или во всем списке (1)? 0/1 \n";
    int choose = _getch();
    std::cout << "\n Название: ";
    bool succesful = false;
    if (choose != '0' && choose != '1') return;
    std::string findName;
    std::cin >> findName;
    std::cout << service.searchItem(findName, choose == '0');
}
void Menu::addItem() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    bool ok = service.add();

    SetConsoleTextAttribute(hConsole, ok ? 10 : 31);
    std::cout << (ok ? "\nУспешно!" : "\nОшибка!");
    SetConsoleTextAttribute(hConsole, 7);
    _getch();
}
void Menu::saveToFile() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    std::cout << "Имя файла (Enter — по умолчанию pharmacy.dat): ";
    std::string path;
    std::getline(std::cin, path);
    if (path.empty()) path = "pharmacy.dat";

    bool ok = service.saveAllToFile(path);

    SetConsoleTextAttribute(hConsole, ok ? 10 : 12);
    std::cout << (ok ? "\nСохранено успешно!" : "\nОшибка сохранения!");
    SetConsoleTextAttribute(hConsole, 7);
    _getch();
}

void Menu::loadFromFile() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    std::cout << "Имя файла (Enter — по умолчанию pharmacy.dat): ";
    std::string path;
    std::getline(std::cin, path);
    if (path.empty()) path = "pharmacy.dat";

    bool ok = service.loadAllFromFile(path);

    SetConsoleTextAttribute(hConsole, ok ? 10 : 12);
    std::cout << (ok ? "\nЗагружено успешно!" : "\nОшибка загрузки!");
    SetConsoleTextAttribute(hConsole, 7);
    _getch();
}