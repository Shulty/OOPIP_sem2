#include <iostream>
#include <vector>
#include <windows.h>

#include "Torrent.h"
#include "Service.h"
#include "Menu.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<Torrent> all;
    Service service(all);

    service.loadUsers("users.dat");
    service.loadAllFromFile("torrents.dat");
    service.loadRequests("requests.dat");
    service.loadBans("bans.dat");
    service.loadBanLogs("banlog.dat");

    AuthMenu auth(service);
    if (!auth.run()) {
        service.saveUsers("users.dat");
        service.saveAllToFile("torrents.dat");
        service.saveRequests("requests.dat");
        service.saveBans("bans.dat");
        service.saveBanLogs("banlog.dat");
        return 0;
    }

    if (service.isAdmin()) {
        AdminMenu admin(service);
        admin.run();
    }
    else {
        UserMenu user(service);
        user.run();
    }

    service.saveUsers("users.dat");
    service.saveAllToFile("torrents.dat");
    service.saveRequests("requests.dat");
    service.saveBans("bans.dat");
    service.saveBanLogs("banlog.dat");

    return 0;
}