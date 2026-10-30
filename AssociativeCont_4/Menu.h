#pragma once
#include <string>
#include <vector>
#include <set>
#include "Service.h"
#include "UI.h"

class Menu {
protected:
    Service& service;
    std::vector<std::string> items;

    void print(int selected) const;
    virtual bool handleChoice(int selected) = 0;

    void viewAll();
    void addItem();
    void searchItem();
    void chooseSort();
    void saveToFile();
    void loadFromFile();
    bool deleteItemWithOwner(int ownerId);
    bool editItemWithOwner(int ownerId);

    void showHotTorrents();
    void filterTorrents();

public:
    explicit Menu(Service& service);
    virtual ~Menu() = default;
    void run();
};

class AuthMenu {
public:
    enum class Result { LoggedIn, Exit };

private:
    Service& service;
    std::vector<std::string> items;

    void print(int selected) const;
    Result handleChoice(int selected);

    void screenLogin();
    void screenRegister();

public:
    explicit AuthMenu(Service& service);
    bool run();
};

class AdminMenu : public Menu {
    bool processRequests();
    void refreshItems();
protected:
    bool handleChoice(int selected) override;
    void screenBans();
public:
    explicit AdminMenu(Service& service);
};

class UserMenu : public Menu {
protected:
    bool handleChoice(int selected) override;
public:
    explicit UserMenu(Service& service);
};