#include "ItemArray.h"
#include <iomanip>

void ItemArray::resize(int newCap) {
    if (newCap < count) newCap = count;
    if (newCap < 1)     newCap = 1;
    if (newCap < count) return;

    Item** newArr = new Item * [newCap];
    for (int i = 0; i < count; ++i)
        newArr[i] = data[i];

    delete[] data;
    data = newArr;
    capacity = newCap;
}

void ItemArray::quickSort(int left, int right, LessFunc less) {
    if (left >= right) return;

    int i = left, j = right;
    Item* pivot = data[(left + right) / 2];

    while (i <= j) {
        while (less(data[i], pivot)) ++i;
        while (less(pivot, data[j])) --j;
        if (i <= j) {
            Item* tmp = data[i];
            data[i] = data[j];
            data[j] = tmp;
            ++i;
            --j;
        }
    }
    if (left < j)  quickSort(left, j, less);
    if (i < right) quickSort(i, right, less);
}

ItemArray::ItemArray()
    : data(new Item* [4]), count(0), capacity(4) {
}

ItemArray::~ItemArray() {
    for (int i = 0; i < count; ++i)
        delete data[i];
    delete[] data;
}

int ItemArray::getCount()    const { return count; }
int ItemArray::getCapacity() const { return capacity; }

void ItemArray::add(Item* obj) {
    if (!obj) return;
    if (count >= capacity) resize(capacity * 2);
    data[count++] = obj;
}

Item* ItemArray::get(int i) const {
    if (i < 0 || i >= count) return nullptr;
    return data[i];
}
Item* ItemArray::operator[](int i) const {
    return get(i);
}

bool ItemArray::removeByName(const std::string& name) {
    for (int i = 0; i < count; ++i) {
        if (data[i]->getName() == name) {
            delete data[i];
            for (int j = i; j < count - 1; ++j)
                data[j] = data[j + 1];
            --count;
            return true;
        }
    }
    return false;
}

bool ItemArray::replace(int index, Item* newItem) {
    if (index < 0 || index >= count || !newItem) return false;
    delete data[index];
    data[index] = newItem;
    return true;
}

Item* ItemArray::findByName(const std::string& name) const {
    for (int i = 0; i < count; ++i)
        if (data[i]->getName() == name)
            return data[i];
    return nullptr;
}
void ItemArray::sort(LessFunc less) {
    if (count > 1) quickSort(0, count - 1, less);
}

void ItemArray::sortByTypeThenName() {
    sort([](const Item* a, const Item* b) -> bool {
        int ta = a->type(), tb = b->type();
        if (ta != tb) return ta < tb;
        return a->getName() < b->getName();
        });
}

void ItemArray::sortByDate() {
    sort([](const Item* a, const Item* b) -> bool {
        return a->getReleaseDate() < b->getReleaseDate();
        });
}

void ItemArray::sortByPrice() {
    sort([](const Item* a, const Item* b) -> bool {
        return a->getPrice() < b->getPrice();
        });
}

void ItemArray::printAll(std::ostream& os) const {
    system("cls");
    int width = 195;
    std::cout << "+" << std::string(width, '-') << "+" << '\n';
    for (int i = 0; i < count; ++i)
        os << "|" << std::setw(3) << (i + 1) << " | " << *data[i] << "\n";
    std::cout << "+" << std::string(width, '-') << "+" << '\n';
}

std::ostream& operator<<(std::ostream& os, const ItemArray& a) {
    a.printAll(os);
    return os;
}
Item* ItemArray::release(int index, int amount) {
    if (index < 0 || index >= count) return nullptr;

    Item* obj = data[index];

    if (amount > obj->getAmount()) {
        for (int i = index; i < count - 1; ++i)
            data[i] = data[i + 1];
        --count;

    }
    else {
		obj->setAmount(obj->getAmount() - amount);
		obj = obj->clone();
		obj->setAmount(amount); 
    }
    return obj;
   
}

void ItemArray::clear() {
    for (int i = 0; i < count; ++i) delete data[i];
    count = 0;
}