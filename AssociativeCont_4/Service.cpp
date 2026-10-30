#include "Service.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cmath>  

Service::Service(std::vector<Torrent>& all)
    : all(all)
{

}


std::string Service::hashPassword(const std::string& pwd)
{
    // Простой djb2
    unsigned long long h = 5381ULL;
    for (unsigned char c : pwd)
        h = ((h << 5) + h) + c;
    return std::to_string(h);
}

int Service::findUserByLogin(const std::string& login) const
{
    for (int i = 0; i < static_cast<int>(users.size()); ++i)
        if (users[i].getLogin() == login)
            return i;
    return -1;
}

int Service::nextUserId() const
{
    int mx = 0;
    for (const auto& u : users)
        if (u.getId() > mx) mx = u.getId();
    return mx + 1;
}

bool Service::loadUsers(const std::string& path)
{
    std::ifstream is(path, std::ios::binary);
    if (!is.is_open())
        return false;

    int count = 0;
    is.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (is.fail() || count < 0)
        return false;

    users.clear();
    users.reserve(count);
    for (int i = 0; i < count; ++i) {
        User u;
        u.read(is);
        if (is.fail())
            return false;
        users.push_back(std::move(u));
    }
    return true;
}

bool Service::saveUsers(const std::string& path) const
{
    std::ofstream os(path, std::ios::binary);
    if (!os.is_open())
        return false;

    int count = static_cast<int>(users.size());
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& u : users) {
        u.write(os);
        if (os.fail())
            return false;
    }
    return true;
}

bool Service::registerUser(const std::string& login, const std::string& password, bool asAdmin)
{
    if (login.empty() || password.empty())
        return false;
    if (findUserByLogin(login) >= 0)
        return false; 

    User u;
    u.setId(nextUserId());
    u.setLogin(login);
    u.setPasswordHash(hashPassword(password));
    u.setRole(asAdmin ? User::Role::Admin : User::Role::User);

    users.push_back(std::move(u));
    return true;
}

bool Service::login(const std::string& login, const std::string& password)
{
    int idx = findUserByLogin(login);
    if (idx < 0) return false;
    if (users[idx].getPasswordHash() != hashPassword(password)) return false;

    const int uid = users[idx].getId();
    if (isBanned(uid)) {
        lastLoginError = "Вы заблокированы. Причина: " + *getBanReason(uid);
        return false;
    }

    currentUserId = uid;
    lastLoginError.clear();
    return true;
}

void Service::logout()
{
    currentUserId = -1;
}

const User* Service::getCurrentUser() const
{
    for (const auto& u : users)
        if (u.getId() == currentUserId)
            return &u;
    return nullptr;
}

bool Service::isAdmin() const
{
    const User* u = getCurrentUser();
    return u && u->isAdmin();
}


void Service::viewAll() const
{
    system("cls");
    if (all.empty()) {
        std::cout << "Список пуст.\n";
        return;
    }

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

    for (const auto& t : all)
        std::cout << t << "\n";
}

void Service::viewOne(int idx) const
{
    if (idx < 0 || idx >= static_cast<int>(all.size()))
        return;
    std::cout << all[idx] << "\n";
}

void Service::viewMine() const
{
    system("cls");
    if (currentUserId < 0) {
        std::cout << "Пользователь не выбран.\n";
        return;
    }

    bool any = false;
    std::cout << std::left
        << std::setw(6) << "ID" << " | "
        << std::setw(40) << "Название" << " | "
        << std::setw(10) << "Размер" << " | "
        << std::setw(15) << "Категория" << " | "
        << std::setw(12) << "Дата" << " | "
        << std::setw(6) << "S" << " | "
        << std::setw(6) << "L" << " |\n";
    std::cout << std::string(100, '-') << "\n";

    for (const auto& t : all) {
        if (t.getOwnerCode() == currentUserId) {
            std::cout << t << "\n";
            any = true;
        }
    }
    if (!any)
        std::cout << "У вас пока нет торрентов.\n";
}

void Service::sort(int type) const
{
    switch (type) {
    case 1:
        std::sort(all.begin(), all.end(),
            [](const Torrent& a, const Torrent& b) { return a < b; });
        break;
    case 2:
        std::sort(all.begin(), all.end(),
            [](const Torrent& a, const Torrent& b) { return a > b; });
        break;
    case 3:
        std::sort(all.begin(), all.end(),
            [](const Torrent& a, const Torrent& b) { return a.getId() < b.getId(); });
        break;
    case 4:
        std::sort(all.begin(), all.end(),
            [](const Torrent& a, const Torrent& b) { return a.getTotalSize() > b.getTotalSize(); });
        break;
    default:
        std::cout << "Неизвестный тип сортировки.\n";
        return;
    }
}

int Service::searchItem(const std::string& name) const
{
    for (int i = 0; i < static_cast<int>(all.size()); ++i)
        if (all[i].getName().find(name) != std::string::npos)
            return i;
    return -1;
}


bool Service::canModify(int num) const
{
    if (num < 0 || num >= static_cast<int>(all.size()))
        return false;
    if (isAdmin())
        return true;
    return currentUserId >= 0 && all[num].getOwnerCode() == currentUserId;
}

bool Service::add()
{
    if (currentUserId < 0) {
        std::cout << "Сначала войдите в систему.\n";
        return false;
    }

    Torrent t;
    std::cin >> t;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(999999, '\n');
        return false;
    }
    t.setId(all.size() + 1);

    t.setOwnerCode(currentUserId);

    if (isAdmin()) {
        all.push_back(t);
        return true;
    }

    requests.emplace_back(nextRequestId++, currentUserId, t);
    return true;
}

bool Service::deleteItem(int num) { return deleteItem(num, -1); }
bool Service::editItem(int num) { return editItem(num, -1); }

bool Service::deleteItem(int num, int ownerCode)
{
    if (num < 0 || num >= static_cast<int>(all.size()))
        return false;

    const Torrent& t = all[num];

    if (ownerCode != -1) {
        if (currentUserId < 0)                     return false;
        if (!isAdmin() && t.getOwnerCode() != currentUserId) return false;
        if (t.getOwnerCode() != ownerCode)             return false;
    }
    else {
        if (!isAdmin())                             return false;
    }

    all.erase(all.begin() + num);
    return true;
}

bool Service::editItem(int num, int ownerCode)
{
    if (num < 0 || num >= static_cast<int>(all.size()))
        return false;

    const Torrent& original = all[num];

    if (ownerCode != -1) {
        if (currentUserId < 0)                          return false;
        if (!isAdmin() && original.getOwnerCode() != currentUserId) return false;
        if (original.getOwnerCode() != ownerCode)           return false;
    }
    else {
        if (!isAdmin())                                 return false;
    }

    Torrent reserveCopy = all[num];
    std::cin >> all[num];
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(999999, '\n');
        all[num] = reserveCopy;
        return false;
    }
    all[num].setOwnerCode(reserveCopy.getOwnerCode());
    return true;
}


bool Service::saveAllToFile(const std::string& path) const
{
    std::ofstream os(path, std::ios::binary);
    if (!os.is_open())
        return false;

    int count = static_cast<int>(all.size());
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& t : all) {
        t.writeBase(os);
        if (os.fail())
            return false;
    }
    return true;
}

bool Service::loadAllFromFile(const std::string& path)
{
    std::ifstream is(path, std::ios::binary);
    if (!is.is_open())
        return false;

    int count = 0;
    is.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (is.fail() || count < 0)
        return false;

    all.clear();
    all.reserve(count);

    for (int i = 0; i < count; ++i) {
        Torrent t;
        t.readBase(is);
        if (is.fail())
            return false;
        all.push_back(t);
    }
    return true;
}

bool Service::hasItems() const
{
    return !all.empty();
}


void Service::viewRequests() const
{
    system("cls");
    if (requests.empty()) {
        std::cout << "Заявок нет.\n";
        return;
    }

    std::cout << std::left
        << std::setw(6) << "ReqID" << " | "
        << std::setw(8) << "OwnerID" << " | "
        << std::setw(30) << "Название" << " | "
        << std::setw(15) << "Категория" << " | "
        << std::setw(10) << "Размер" << "\n";
    std::cout << std::string(80, '-') << "\n";

    for (const auto& r : requests) {
        const Torrent& t = r.getTorrent();
        std::cout << std::left
            << std::setw(6) << r.getId() << " | "
            << std::setw(8) << r.getOwnerId() << " | "
            << std::setw(30) << t.getName() << " | "
            << std::setw(15) << t.getCategory() << " | "
            << std::setw(10) << t.getTotalSize() << "\n";
    }
}

bool Service::approveRequest(int requestId)
{
    for (auto it = requests.begin(); it != requests.end(); ++it) {
        if (it->getId() == requestId) {
            all.push_back(it->getTorrent());
            requests.erase(it);
            saveRequests();
            return true;
       
        }
    }
    return false;
}

bool Service::rejectRequest(int requestId)
{
    for (auto it = requests.begin(); it != requests.end(); ++it) {
        if (it->getId() == requestId) {
            requests.erase(it);
            saveRequests();
            return true;
            
        }
    }
    return false;
}

bool Service::saveRequests(const std::string& path) const
{
    std::ofstream os(path, std::ios::binary);
    if (!os.is_open()) return false;

    int count = static_cast<int>(requests.size());
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));
    os.write(reinterpret_cast<const char*>(&nextRequestId), sizeof(nextRequestId));

    for (const auto& r : requests) {
        r.write(os);
        if (os.fail()) return false;
    }
    return true;
}

bool Service::loadRequests(const std::string& path)
{
    std::ifstream is(path, std::ios::binary);
    if (!is.is_open()) return false;

    int count = 0;
    is.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (is.fail() || count < 0) return false;

    is.read(reinterpret_cast<char*>(&nextRequestId), sizeof(nextRequestId));
    if (is.fail()) return false;

    requests.clear();
    for (int i = 0; i < count; ++i) {
        Request r;
        r.read(is);
        if (is.fail()) return false;
        requests.push_back(std::move(r));
    }
    return true;
}
double Service::heat(const Torrent& t)
{
    const double L = static_cast<double>(t.getLeechers());
    const double S = static_cast<double>(t.getSeeders());
    return L * std::log(1.0 + S);
}

std::multiset<Torrent, std::function<bool(const Torrent&, const Torrent&)>>
Service::getHotTorrents() const
{
    auto cmp = [](const Torrent& a, const Torrent& b) {
        const double ha = heat(a);
        const double hb = heat(b);
        if (ha != hb) return ha < hb;
        return (a.getSeeders() + a.getLeechers())
    < (b.getSeeders() + b.getLeechers());
        };

    std::multiset<Torrent, std::function<bool(const Torrent&, const Torrent&)>>
        result(cmp);
    int i = 0;
    for (const auto& t : all)
        result.insert(t);

    return result;
}


#include <iterator>

std::set<int> Service::filterBySeeders(int minSeeders) const
{
    std::set<int> result;
    for (int i = 0; i < static_cast<int>(all.size()); ++i) {
        if (all[i].getSeeders() > minSeeders)  
            result.insert(i);
    }
    return result;
}

std::set<int> Service::filterByCategory(const std::string& category) const
{
    std::set<int> result;
    for (int i = 0; i < static_cast<int>(all.size()); ++i) {
        if (all[i].getCategory() == category)
            result.insert(i);
    }
    return result;
}

std::set<int> Service::intersect(const std::set<int>& a, const std::set<int>& b)
{
    std::set<int> result;
    std::set_intersection(
        a.begin(), a.end(),
        b.begin(), b.end(),
        std::inserter(result, result.begin()));
    return result;
}

void Service::viewByIndices(const std::set<int>& idx) const
{
    system("cls");
    if (idx.empty()) {
        std::cout << "Ничего не найдено по заданным фильтрам.\n";
        return;
    }

    std::cout << std::left
        << std::setw(6) << "ID" << " | "
        << std::setw(30) << "Название" << " | "
        << std::setw(10) << "Размер" << " | "
        << std::setw(15) << "Категория" << " | "
        << std::setw(20) << "Загрузил" << " | "
        << std::setw(12) << "Дата" << " | "
        << std::setw(6) << "S" << " | "
        << std::setw(6) << "L" << " |\n";
    std::cout << std::string(120, '-') << "\n";

    for (int i : idx)
        std::cout << all[i] << "\n";
}

std::set<std::string> Service::getAllCategories() const
{
    std::set<std::string> cats;
    for (const auto& t : all)
        cats.insert(t.getCategory());
    return cats;
}

//  Баны

bool Service::banUser(int userId, const std::string& reason)
{
    if (!isAdmin()) return false;
    if (userId < 0) return false;
    if (getUserById(userId) == nullptr) return false;
    if (userId == currentUserId) return false;  
    if (isBanned(userId))   return false;   

    activeBans[userId] = reason;
    banLogs.emplace(userId, "BAN: " + reason);

    saveBans();
    saveBanLogs();
    return true;
}

bool Service::unbanUser(int userId)
{
    if (!isAdmin())             return false;
    auto it = activeBans.find(userId);
    if (it == activeBans.end()) return false;

    const std::string reason = it->second;
    activeBans.erase(it);
    banLogs.emplace(userId, "UNBAN: " + reason);

    saveBans();
    saveBanLogs();
    return true;
}

bool Service::isBanned(int userId) const
{
    return activeBans.find(userId) != activeBans.end();
}

const std::string* Service::getBanReason(int userId) const
{
    auto it = activeBans.find(userId);
    return it == activeBans.end() ? nullptr : &it->second;
}

//  Просмотр

void Service::viewBans() const
{
    system("cls");
    if (activeBans.empty()) {
        std::cout << "Активных банов нет.\n";
        return;
    }

    std::cout << std::left
        << std::setw(8) << "UserID" << " | "
        << std::setw(20) << "Логин" << " | "
        << std::setw(40) << "Причина" << "\n";
    std::cout << std::string(75, '-') << "\n";

    for (const auto& [uid, reason] : activeBans) {
        const User* u = getUserById(uid);
        std::cout << std::left
            << std::setw(8) << uid << " | "
            << std::setw(20) << (u ? u->getLogin() : "?") << " | "
            << std::setw(40) << reason << "\n";
    }
}

void Service::viewBanLogs() const
{
    system("cls");
    if (banLogs.empty()) {
        std::cout << "Логов нет.\n";
        return;
    }

    std::cout << std::left
        << std::setw(8) << "UserID" << " | "
        << std::setw(20) << "Логин" << " | "
        << std::setw(50) << "Событие" << "\n";
    std::cout << std::string(85, '-') << "\n";

    for (const auto& [uid, event] : banLogs) {
        const User* u = getUserById(uid);
        std::cout << std::left
            << std::setw(8) << uid << " | "
            << std::setw(20) << (u ? u->getLogin() : "?") << " | "
            << std::setw(50) << event << "\n";
    }
}

void Service::viewBanLogsFor(int userId) const
{
    system("cls");
    auto range = banLogs.equal_range(userId);
    if (range.first == range.second) {
        std::cout << "Для пользователя " << userId << " логов нет.\n";
        return;
    }
    for (auto it = range.first; it != range.second; ++it)
        std::cout << it->second << "\n";
}


bool Service::saveBans(const std::string& path) const
{
    std::ofstream os(path, std::ios::binary);
    if (!os.is_open()) return false;

    int count = static_cast<int>(activeBans.size());
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& [uid, reason] : activeBans) {
        os.write(reinterpret_cast<const char*>(&uid), sizeof(uid));
        int len = static_cast<int>(reason.size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(reason.data(), len);
        if (os.fail()) return false;
    }
    return true;
}

bool Service::loadBans(const std::string& path)
{
    std::ifstream is(path, std::ios::binary);
    if (!is.is_open()) return false;

    int count = 0;
    is.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (is.fail() || count < 0) return false;

    activeBans.clear();
    for (int i = 0; i < count; ++i) {
        int uid = -1;
        is.read(reinterpret_cast<char*>(&uid), sizeof(uid));
        int len = 0;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string reason(len, '\0');
        if (len > 0) is.read(&reason[0], len);
        if (is.fail()) return false;
        activeBans[uid] = reason;
    }
    return true;
}

bool Service::saveBanLogs(const std::string& path) const
{
    std::ofstream os(path, std::ios::binary);
    if (!os.is_open()) return false;

    int count = static_cast<int>(banLogs.size());
    os.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto& [uid, event] : banLogs) {
        os.write(reinterpret_cast<const char*>(&uid), sizeof(uid));
        int len = static_cast<int>(event.size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(event.data(), len);
        if (os.fail()) return false;
    }
    return true;
}

bool Service::loadBanLogs(const std::string& path)
{
    std::ifstream is(path, std::ios::binary);
    if (!is.is_open()) return false;

    int count = 0;
    is.read(reinterpret_cast<char*>(&count), sizeof(count));
    if (is.fail() || count < 0) return false;

    banLogs.clear();
    for (int i = 0; i < count; ++i) {
        int uid = -1;
        is.read(reinterpret_cast<char*>(&uid), sizeof(uid));
        int len = 0;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        std::string event(len, '\0');
        if (len > 0) is.read(&event[0], len);
        if (is.fail()) return false;
        banLogs.emplace(uid, event);
    }
    return true;
}
const User* Service::getUserById(int id) const
{
    for (const auto& u : users)
        if (u.getId() == id)
            return &u;
    return nullptr;
}