#include <vector>
#include<Windows.h>
#include "Torrent.h"
#include "Service.h"
#include "Menu.h"


int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    std::vector<Torrent> all;
    Service service(all);

    service.loadUsers("users.dat");
    service.loadAllFromFile("torrents.dat");
    service.loadUsers("users.dat");
    service.loadAllFromFile("torrents.dat");
    service.loadRequests("requests.dat");

    AuthMenu auth(service);
    if (!auth.run())
        return 0;

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

    return 0;
   
}