#pragma once
#include <iostream>
#include <string>
#include "Item.h"

class ItemArray {
private:
    Item** data;
    int count;
    int capacity;

    void resize(int newCap);

    using LessFunc = bool(*)(const Item*, const Item*);

    void quickSort(int left, int right, LessFunc less);

public:
    ItemArray();
    ItemArray(const ItemArray&) = delete;
    ItemArray& operator=(const ItemArray&) = delete;
    ~ItemArray();

    int getCount()    const;
    int getCapacity() const;

    void add(Item* obj);
    Item* get(int i) const;
    Item* operator[](int i) const;

    Item* release(int index);
    bool  removeByName(const std::string& name);
    Item* findByName(const std::string& name) const;

    void sort(LessFunc less);

    void sortByTypeThenName();
    void sortByDate();
    void sortByPrice();

    void printAll(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const ItemArray& a);
};