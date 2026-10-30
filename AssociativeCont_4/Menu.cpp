#include "Menu.h"
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <windows.h>
#include <limits>
#include "UI.h"

namespace {
    const int KEY_ARROW = 224;
    const int KEY_ENTER = 13;
    const int KEY_UP = 72;
    const int KEY_DOWN = 80;

    const int ANY_OWNER = -1;


    void clearInput() {
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }

    int readIndex(const char* prompt) {
        std::cout << prompt;
        int idx = -1;
        std::cin >> idx;
        if (std::cin.fail()) {
            clearInput();
            return -1;
        }
        std::cin.ignore(999999, '\n');
        return idx;
    }
}

Menu::Menu(Service& service)
    : service(service)
{
}

void Menu::print(int selected = 0) const
{
    system("cls");
    PrintTorrentArt();
    SetConsoleTextAttribute(hConsole, 7);

    const int count = static_cast<int>(items.size());
    for (int i = 0; i < count; ++i) {
        if (i == selected) {
            SetConsoleTextAttribute(hConsole, ACCENT_COLOR);
            PrintCenter("[ " + items[i] + " ]", i + 7);
            SetConsoleTextAttribute(hConsole, 7);
        }
        else {
            PrintCenter(items[i], i + 7);
        }
    }

    SetConsoleTextAttribute(hConsole, 7);
}

void Menu::run()
{
    int selected = 0;
    const int count = static_cast<int>(items.size());

    while (true) {
        print(selected);

        int key = _getch();

        if (key == KEY_ARROW || key == 0) {
            key = _getch();
            if (key == KEY_UP)
                selected = (selected - 1 + count) % count;
            else if (key == KEY_DOWN)
                selected = (selected + 1) % count;
        }
        else if (key == KEY_ENTER) {
            if (!handleChoice(selected))
                return;

            std::cout << "\nНажмите любую клавишу...";
            _getch();
        }
    }
}


void Menu::viewAll()
{
    system("cls");
    service.viewAll();
}

void Menu::addItem()
{
    system("cls");

    bool ok = service.add();

    SetConsoleTextAttribute(hConsole, ok ? OK_COLOR : ERR_COLOR);
    std::cout << (ok ? "\nУспешно!" : "\nОшибка!");

    if (ok && !service.isAdmin())
        std::cout << " Торрент отправлен на модерацию администратору.";
    SetConsoleTextAttribute(hConsole, 7);
}

void Menu::searchItem()
{
    system("cls");

    std::cout << "Название (подстрока): ";
    std::string findName;
    std::getline(std::cin, findName);

    int idx = service.searchItem(findName);
    if (idx < 0) {
        SetConsoleTextAttribute(hConsole, ERR_COLOR);
        std::cout << "\nНе найдено!";
        SetConsoleTextAttribute(hConsole, 7);
    }
    else {
        service.viewOne(idx);
    }
}

void Menu::chooseSort()
{
    system("cls");
    std::cout << "Сортировка:\n"
        "  1 — по пирам (возрастание)\n"
        "  2 — по пирам (убывание)\n"
        "  3 — по ID\n"
        "  4 — по размеру (убывание)\n"
        "Выбор: ";

    int type = 0;
    std::cin >> type;
    if (std::cin.fail()) {
        clearInput();
        return;
    }
    std::cin.ignore(999999, '\n');

    service.sort(type);
    service.viewAll();
}

void Menu::saveToFile()
{
    system("cls");
    std::cout << "Имя файла (Enter — по умолчанию torrents.dat): ";
    std::string path;
    std::getline(std::cin, path);
    if (path.empty())
        path = "torrents.dat";

    bool ok = service.saveAllToFile(path);

    SetConsoleTextAttribute(hConsole, ok ? OK_COLOR : ERR_COLOR);
    std::cout << (ok ? "\nСохранено успешно!" : "\nОшибка сохранения!");
    SetConsoleTextAttribute(hConsole, 7);
}

void Menu::loadFromFile()
{
    system("cls");
    std::cout << "Имя файла (Enter — по умолчанию torrents.dat): ";
    std::string path;
    std::getline(std::cin, path);
    if (path.empty())
        path = "torrents.dat";

    bool ok = service.loadAllFromFile(path);

    SetConsoleTextAttribute(hConsole, ok ? OK_COLOR : ERR_COLOR);
    std::cout << (ok ? "\nЗагружено успешно!" : "\nОшибка загрузки!");
    SetConsoleTextAttribute(hConsole, 7);
}


bool Menu::deleteItemWithOwner(int ownerCode)
{
    system("cls");
    service.viewAll();

    if (!service.hasItems()) {
        SetConsoleTextAttribute(hConsole, ERR_COLOR);
        std::cout << "\nСписок пуст!";
        SetConsoleTextAttribute(hConsole, 7);
        return false;
    }

    int idx = readIndex("\nНомер для удаления (0..N-1): ");

    bool ok = false;
    if (idx >= 0) {

        ok = service.deleteItem(idx, ownerCode);
    }

    SetConsoleTextAttribute(hConsole, ok ? OK_COLOR : ERR_COLOR);
    std::cout << (ok ? "\nУспешно!" : "\nОшибка! (нет прав или неверный номер)");
    SetConsoleTextAttribute(hConsole, 7);
    return ok;
}

bool Menu::editItemWithOwner(int ownerCode)
{
    system("cls");
    service.viewAll();

    if (!service.hasItems()) {
        SetConsoleTextAttribute(hConsole, ERR_COLOR);
        std::cout << "\nСписок пуст!";
        SetConsoleTextAttribute(hConsole, 7);
        return false;
    }

    int idx = readIndex("\nНомер для редактирования (0..N-1): ");

    bool ok = false;
    if (idx >= 0) {
        ok = service.editItem(idx, ownerCode);
    }

    SetConsoleTextAttribute(hConsole, ok ? OK_COLOR : ERR_COLOR);
    std::cout << (ok ? "\nУспешно!" : "\nОшибка! (нет прав или неверный номер)");
    SetConsoleTextAttribute(hConsole, 7);
    return ok;
}


AdminMenu::AdminMenu(Service& service)
    : Menu(service)
{
    items = {
    "1. Просмотр торрентов",        
    "2. Добавить торрент",          
    "3. Удалить торрент",             
    "4. Редактировать торрент",       
    "5. Сортировка",                 
    "6. Поиск",                   
    "7. Сохранить в файл",            
    "8. Загрузить из файла",         
    "9. Заявки (" + std::to_string(service.requestCount()) + ")",  
    "10. Баны",                     
    "0. Выход"                      
    };
}
void AdminMenu::refreshItems()
{
    this->items = {
    "1. Просмотр торрентов",
    "2. Добавить торрент",
    "3. Удалить торрент",
    "4. Редактировать торрент",
    "5. Сортировка",
    "6. Поиск",
    "7. Сохранить в файл",
    "8. Загрузить из файла",
    "9. Заявки (" + std::to_string(service.requestCount()) + ")",
    "10. Баны",
    "0. Выход"
    };
}

bool AdminMenu::handleChoice(int selected)
{
    
    switch (selected) {
    case 0: viewAll();                              break;
    case 1: addItem();                              break;
    case 2: deleteItemWithOwner(ANY_OWNER);         break;  
    case 3: editItemWithOwner(ANY_OWNER);           break; 
    case 4: chooseSort();                           break;
    case 5: searchItem();                           break;
    case 6: saveToFile();                           break;
    case 7: showHotTorrents();                      break;
    case 8: {
        processRequests();
        AdminMenu::refreshItems();
    }                                               break;
    case 9: screenBans();                           break;
    case 10: return false;
    default: break;
    }
    return true;
}


UserMenu::UserMenu(Service& service)
    : Menu(service)
{
    items = {
        "1. Просмотр торрентов",
        "2. Добавить торрент",
        "3. Удалить свой торрент",
        "4. Редактировать свой торрент",
        "5. Сортировка",
        "6. Поиск",
        "7. Сохранить в файл",
        "8. Горячие торенты",
        "9. Фильтр",
        "0. Выход"
    };
}

bool UserMenu::handleChoice(int selected)
{

    const int me = service.getCurrentUserId();

    switch (selected) {
    case 0: viewAll();                              break;
    case 1: addItem();                              break;
    case 2: deleteItemWithOwner(me);                break;  
    case 3: editItemWithOwner(me);                  break;  
    case 4: chooseSort();                           break;
    case 5: searchItem();                           break;
    case 6: saveToFile();                           break;
    case 7: showHotTorrents();                      break;
    case 8: filterTorrents();                       break;
    case 9: return false;
    default: break;
    }
    return true;
}


AuthMenu::AuthMenu(Service& service)
    : service(service)
{
    items = {
        "1. Войти",
        "2. Зарегистрироваться",
        "0. Выход"
    };
}

void AuthMenu::print(int selected) const
{
    system("cls");
    PrintTorrentArt();
    SetConsoleTextAttribute(hConsole, 7);

    SetConsoleTextAttribute(hConsole, ACCENT_COLOR);
    PrintCenter("=== Вход в систему ===", 6);
    SetConsoleTextAttribute(hConsole, 7);

    if (!service.hasUsers()) {
        SetConsoleTextAttribute(hConsole, ERR_COLOR);
        PrintCenter("Пользователей нет — зарегистрируйте первого (админ)", 7);
        SetConsoleTextAttribute(hConsole, 7);
    }
    else {
        PrintCenter("", 7);
    }

    const int startY = 9;
    for (int i = 0; i < static_cast<int>(items.size()); ++i) {
        if (i == selected) {
            SetConsoleTextAttribute(hConsole, ACCENT_COLOR);
            PrintCenter("[ " + items[i] + " ]", startY + i * 2);
            SetConsoleTextAttribute(hConsole, 7);
        }
        else {
            PrintCenter(items[i], startY + i * 2);
        }
    }
}

void AuthMenu::screenLogin()
{
    system("cls");
    PrintTorrentArt();
    SetConsoleTextAttribute(hConsole, 7);

    SetConsoleTextAttribute(hConsole, ACCENT_COLOR);
    PrintCenter("=== Вход ===", 6);
    SetConsoleTextAttribute(hConsole, 7);

    bool cancelled = false;

    const std::string login = ReadCenteredLine("Логин: ", 9, false, "", &cancelled);
    if (cancelled) return;

    const std::string password = ReadCenteredLine("Пароль: ", 10, true, "", &cancelled);
    if (cancelled) return;

    const bool ok = service.login(login, password);

    if (ok) {
        ShowMessage("Вход выполнен!", 13, OK_COLOR);
    }
    else {
        std::string msg = service.getLastLoginError();
        if (msg.empty()) msg = "Неверный логин/пароль!";
        ShowMessage(msg, 13, ERR_COLOR);
    }
    WaitAnyKey("Нажмите любую клавишу...", 15);
}

void AuthMenu::screenRegister()
{
    system("cls");
    PrintTorrentArt();
    SetConsoleTextAttribute(hConsole, 7);

    SetConsoleTextAttribute(hConsole, ACCENT_COLOR);
    PrintCenter("=== Регистрация ===", 6);
    SetConsoleTextAttribute(hConsole, 7);

    const bool firstRun = !service.hasUsers();
    if (firstRun) {
        SetConsoleTextAttribute(hConsole, ERR_COLOR);
        PrintCenter("Первый аккаунт будет АДМИНИСТРАТОРОМ", 7);
        SetConsoleTextAttribute(hConsole, 7);
    }

    bool cancelled = false;

    const std::string login = ReadCenteredLine("Логин: ", 9, false, "", &cancelled);
    if (cancelled) return;

    const std::string password = ReadCenteredLine("Пароль: ", 10, true, "", &cancelled);
    if (cancelled) return;

    const std::string confirm = ReadCenteredLine("Повторите пароль: ", 11, true, "", &cancelled);
    if (cancelled) return;

    bool ok = false;
    std::string msg;

    if (password != confirm) {
        msg = "Пароли не совпадают!";
    }
    else if (login.empty() || password.empty()) {
        msg = "Логин и пароль не могут быть пустыми";
    }
    else if (!service.registerUser(login, password, firstRun)) {
        msg = "Ошибка: логин занят";
    }
    else {
        service.saveUsers("users.dat");
        service.login(login, password);
        ok = true;
        msg = firstRun ? "Готово! Вы администратор." : "Готово! Вы зарегистрированы.";
    }

    ShowMessage(msg, 13, ok ? OK_COLOR : ERR_COLOR);
    WaitAnyKey("Нажмите любую клавишу...", 15);
}

AuthMenu::Result AuthMenu::handleChoice(int selected)
{
    switch (selected) {
    case 0:
        screenLogin();
        return service.isLoggedIn() ? Result::LoggedIn : Result::Exit /*не выходим, но проверим ниже*/;
    case 1:
        screenRegister();
        return service.isLoggedIn() ? Result::LoggedIn : Result::Exit;
    case 2:
        return Result::Exit;
    default:
        return Result::Exit;
    }
}

bool AuthMenu::run()
{
    int selected = 0;
    const int count = static_cast<int>(items.size());

    while (true) {
        print(selected);

        int key = _getch();

        if (key == KEY_ARROW || key == 0) {
            key = _getch();
            if (key == KEY_UP)
                selected = (selected - 1 + count) % count;
            else if (key == KEY_DOWN)
                selected = (selected + 1) % count;
        }
        else if (key == KEY_ENTER) {

            switch (selected) {
            case 0:
                screenLogin();
                if (service.isLoggedIn()) return true;
                break;
            case 1:
                screenRegister();
                if (service.isLoggedIn()) return true;
                break;
            case 2:
                return false;
            default:
                break;
            }
        }
    }
}
namespace {
    char askAction()
    {
        while (true) {
            std::cout << "\n[A] Принять   [R] Отклонить   [Esc] В меню: ";
            int ch = _getch();
            if (ch == 27)              return 'Q';   
            if (ch == 'a' || ch == 'A') return 'A';
            if (ch == 'r' || ch == 'R') return 'R';
        }
    }
}

bool AdminMenu::processRequests()
{
    while (service.hasPendingRequest()) {
        system("cls");
        service.viewRequests();

        const Request& req = service.frontRequest();

        std::cout << "\n=== Рассматривается заявка #"
            << req.getId() << " ===\n";
        std::cout << "Владелец (userId): " << req.getOwnerId() << "\n";
        std::cout << "Торрент:\n" << req.getTorrent() << "\n";

        char action = askAction();

        if (action == 'Q')
            return false;

        bool ok = false;
        if (action == 'A')
            ok = service.approveRequest(req.getId());
        else if (action == 'R')
            ok = service.rejectRequest(req.getId());

        SetConsoleTextAttribute(hConsole, ok ? OK_COLOR : ERR_COLOR);
        std::cout << (ok
            ? (action == 'A' ? "\nПринято." : "\nОтклонено.")
            : "\nОшибка!");
        SetConsoleTextAttribute(hConsole, 7);
        std::cout << "\nНажмите любую клавишу...";

        _getch();
        
    }

    system("cls");
    std::cout << "Заявок больше нет.\n";
    _getch();
    return true;
}

void Menu::showHotTorrents()
{
    system("cls");
    PrintTorrentArt();
    SetConsoleTextAttribute(hConsole, 7);

    SetConsoleTextAttribute(hConsole, ACCENT_COLOR);
    PrintCenter("=== Горячие торренты (heat = L * log(1 + S)) ===", 6);
    SetConsoleTextAttribute(hConsole, 7);
    std::cout << std::left
        << std::setw(6) << "ID" << " | "
        << std::setw(40) << "Название" << " | "
        << std::setw(10) << "Размер" << " | "
        << std::setw(15) << "Категория" << " | "
        << std::setw(20) << "Загрузил" << " | "
        << std::setw(12) << "Дата" << " | "
        << std::setw(6) << "S" << " | "
        << std::setw(6) << "L" << " |\n";

    std::cout << std::string(120, '-') << "\n";

    auto hot = service.getHotTorrents();
    if (hot.empty()) {
        SetConsoleTextAttribute(hConsole, ERR_COLOR);
        PrintCenter("Список пуст.", 8);
        SetConsoleTextAttribute(hConsole, 7);
        _getch();
        return;
    }

    int y = 8;
    int count = 0;
    for (auto it = hot.rbegin(); it != hot.rend(); ++it, ++y,++count) {
        if (count == 5) break;
        if (y >= ConsoleHeight() - 2) {
            PrintCenter("... (нажмите любую клавишу)", y);
            _getch();
            system("cls");
            PrintTorrentArt();
            y = 8;
        }

        std::cout << *it<<"\n";
    }

    std::cin.clear();
    std::cin.ignore(999999, '\n');
}

void Menu::filterTorrents()
{
    system("cls");
    PrintTorrentArt();
    SetConsoleTextAttribute(hConsole, 7);

    SetConsoleTextAttribute(hConsole, ACCENT_COLOR);
    PrintCenter("=== Фильтр торрентов ===", 6);
    SetConsoleTextAttribute(hConsole, 7);

    std::cout << "\nМинимальное число сидов (S > N): ";
    int minSeeders = 0;
    std::cin >> minSeeders;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(999999, '\n');
        return;
    }
    std::cin.ignore(999999, '\n');

    auto cats = service.getAllCategories();
    std::cout << "\nДоступные категории:\n";
    for (const auto& c : cats)
        std::cout << "  - " << c << "\n";
    std::cout << "Категория: ";
    std::string category;
    std::getline(std::cin, category);

    auto bySeeders = service.filterBySeeders(minSeeders);
    auto byCategory = service.filterByCategory(category);
    auto filtered = Service::intersect(bySeeders, byCategory);

    service.viewByIndices(filtered);

    std::cin.ignore(999999, '\n');
}

void AdminMenu::screenBans()
{
    while (true) {
        system("cls");
        PrintTorrentArt();

        SetConsoleTextAttribute(hConsole, ACCENT_COLOR);
        PrintCenter("=== Управление банами ===", 6);
        SetConsoleTextAttribute(hConsole, 7);

        std::vector<std::string> opts = {
            "1. Список активных банов",
            "2. Забанить пользователя",
            "3. Разбанить пользователя",
            "4. Логи банов",
            "0. Назад"
        };

        int startY = 9;
        for (int i = 0; i < (int)opts.size(); ++i)
            PrintCenter(opts[i], startY + i * 2);

        std::cout << "\nВыбор: ";
        int c;
        std::cin >> c;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(999999, '\n');
            continue;
        }
        std::cin.ignore(999999, '\n');

        if (c == 0) return;

        if (c == 1) {
            service.viewBans();
            _getch();
        }
        else if (c == 2) {
            std::cout << "Логин пользователя: ";
            std::string login;
            std::getline(std::cin, login);
            int uid = service.findUserByLogin(login);
            if (uid < 0) {
                std::cout << "Пользователь не найден.\n";
                _getch();
                continue;
            }
            std::cout << "Причина: ";
            std::string reason;
            std::getline(std::cin, reason);

            bool ok = service.banUser(uid, reason);
            SetConsoleTextAttribute(hConsole, ok ? OK_COLOR : ERR_COLOR);
            std::cout << (ok ? "\nЗабанен." : "\nОшибка (уже забанен / нет прав).");
            SetConsoleTextAttribute(hConsole, 7);
            _getch();
        }
        else if (c == 3) {
            std::cout << "Логин пользователя: ";
            std::string login;
            std::getline(std::cin, login);
            int uid = service.findUserByLogin(login);
            if (uid < 0) {
                std::cout << "Пользователь не найден.\n";
                _getch();
                continue;
            }
            bool ok = service.unbanUser(uid);
            SetConsoleTextAttribute(hConsole, ok ? OK_COLOR : ERR_COLOR);
            std::cout << (ok ? "\nРазбанен." : "\nОшибка (не забанен).");
            SetConsoleTextAttribute(hConsole, 7);
            _getch();
        }
        else if (c == 4) {
            service.viewBanLogs();
            _getch();
        }
    }
}