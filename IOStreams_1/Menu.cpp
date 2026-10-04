#include "Menu.h"
#include <conio.h>
#include <iostream> 
#include <windows.h>

namespace {
    const char* items[] = { "1.View items", "2.Add item", "3.Delete item", "4.Edit item", "5.Sort items", "6.Find item","7.MyCart", "0.Exit" }; const int itemsCount = sizeof(items) / sizeof(items[0]);
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
                std::cout << ">" << items[i] << '\n';
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
                    case 7: return;  
                    }
                    _getch();  
                }
            }
        }
    void Menu::chooseSort() {
        system("cls");
        std::cout << "Please choose sort type \n";
        std::cout << "1.By type and than by name \n";
        std::cout << "2.By price \n";
        std::cout << "3.By Date \n";
        int choose = _getch();
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 10);
        std::cout << "Succesful! \n";
        SetConsoleTextAttribute(hConsole, 7);
        service.sort(choose);
    }
    void Menu::deleteItem() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        system("cls");
        std::cout << "Delete from cart(0) or all(1)? 0/1 \n";
        int choose = _getch();
        std::cout << "\n Number: ";
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
            std::cout << "Succesful!";
        }
        else {
            SetConsoleTextAttribute(hConsole, 31);
            std::cout << "Failure!";
        }
        SetConsoleTextAttribute(hConsole, 7);
    }
    void Menu::editItem() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        system("cls");
        std::cout << "Edit in cart(0) or all(1)? 0/1 \n";
        int choose = _getch();
        std::cout << "\n Number: ";
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
            std::cout << "Succesful!";
        }
        else {
            SetConsoleTextAttribute(hConsole, 31);
            std::cout << "Failure!";
        }
        SetConsoleTextAttribute(hConsole, 7);
    }
    void Menu::searchItem() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        system("cls");
        std::cout << "Search in cart(0) or all(1) ? 0 / 1 \n";
        int choose = _getch();
        std::cout << "\n Name: ";
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
        std::cout << (ok ? "\nSuccesful!" : "\nFailure!");
        SetConsoleTextAttribute(hConsole, 7);
        _getch();
    }