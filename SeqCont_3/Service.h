#pragma once
#include <list>
#include <string>
#include <vector>
#include "Torrent.h"
#include "User.h"
#include "Request.h"

class Service {
    std::vector<Torrent>& all;
    std::vector<User>     users;
    std::list<Request>    requests;
    int                   nextRequestId = 1;

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

private:
    static std::string hashPassword(const std::string& pwd);
    int  findUserByLogin(const std::string& login) const;
    int  nextUserId() const;
};