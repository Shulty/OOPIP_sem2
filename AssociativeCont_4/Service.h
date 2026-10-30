#pragma once
#include <list>
#include <string>
#include <vector>
#include <set> 
#include<functional>
#include<map>
#include<unordered_map>

#include "Torrent.h"
#include "User.h"
#include "Request.h"


class Service {
    std::vector<Torrent>& all;
    std::vector<User> users;
    std::list<Request> requests;
    std::unordered_map<int, std::string> activeBans;   // userId - причина
    std::multimap<int, std::string>      banLogs;      // userId - "BAN: ..." / "UNBAN: ..."
    std::string                          lastLoginError;
    int nextRequestId = 1;

    int  currentUserId = -1;

public:
    explicit Service(std::vector<Torrent>& all);

    bool loadUsers(const std::string& path = "users.dat");
    bool saveUsers(const std::string& path = "users.dat") const;
    bool registerUser(const std::string& login, const std::string& password, bool asAdmin = false);
    bool login(const std::string& login, const std::string& password);
    void logout();

    bool isLoggedIn()     const { return currentUserId >= 0; }
    int  getCurrentUserId() const { return currentUserId; }
    const User* getCurrentUser() const;
    bool isAdmin()        const;
    bool hasUsers()       const { return !users.empty(); }

    void viewAll() const;
    void viewOne(int idx) const;
    void viewMine() const;

    void sort(int type) const;
    int  searchItem(const std::string& name) const;

    bool add();
    bool deleteItem(int num);
    bool editItem(int num);
    bool deleteItem(int num, int ownerId);
    bool editItem(int num, int ownerId);
    bool canModify(int num) const;

    bool hasRequests()  const { return !requests.empty(); }
    size_t requestCount() const { return requests.size(); }

    void viewRequests() const;

    bool approveRequest(int requestId);
    bool rejectRequest(int requestId);

    bool hasPendingRequest() const { return !requests.empty(); }
    const Request& frontRequest() const { return requests.front(); }

    bool saveRequests(const std::string& path = "requests.dat") const;
    bool loadRequests(const std::string& path = "requests.dat");

    bool saveAllToFile(const std::string& path) const;
    bool loadAllFromFile(const std::string& path);
    bool hasItems() const;

    //—амые гор€чие торенты
    std::multiset<Torrent, std::function<bool(const Torrent&, const Torrent&)>>
        getHotTorrents() const;
    static double heat(const Torrent& t);
    // ---- ‘ильтраци€ ----
    std::set<int> filterBySeeders(int minSeeders) const;

    std::set<int> filterByCategory(const std::string& category) const;

    static std::set<int> intersect(const std::set<int>& a, const std::set<int>& b);

    void viewByIndices(const std::set<int>& idx) const;

    std::set<std::string> getAllCategories() const;



    // ---- Ѕаны ----
    bool banUser(int userId, const std::string& reason);
    bool unbanUser(int userId);
    bool isBanned(int userId) const;
    const std::string* getBanReason(int userId) const;

    void viewBans() const;
    void viewBanLogs() const;
    void viewBanLogsFor(int userId) const;

    bool saveBans(const std::string& path = "bans.dat") const;
    bool loadBans(const std::string& path = "bans.dat");
    bool saveBanLogs(const std::string& path = "banlog.dat") const;
    bool loadBanLogs(const std::string& path = "banlog.dat");

    int findUserByLogin(const std::string& login) const;
    const User* getUserById(int id) const;

    const std::string& getLastLoginError() const { return lastLoginError; }
    void clearLoginError() { lastLoginError.clear(); }

private:
    static std::string hashPassword(const std::string& pwd);
    int  nextUserId() const;
};