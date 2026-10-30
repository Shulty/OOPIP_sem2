#pragma once
#include <fstream>
#include <string>
#include "Torrent.h"

class Request {
    int id;         
    int ownerId;    
    Torrent torrent;    

public:
    Request() = default;
    Request(int id, int ownerId, const Torrent& t)
        : id(id), ownerId(ownerId), torrent(t) {
    }

    int     getId()      const { return id; }
    int     getOwnerId() const { return ownerId; }
    const Torrent& getTorrent() const { return torrent; }

    void write(std::ostream& os) const {
        os.write(reinterpret_cast<const char*>(&id), sizeof(id));
        os.write(reinterpret_cast<const char*>(&ownerId), sizeof(ownerId));
        torrent.writeBase(os);
    }
    void read(std::istream& is) {
        is.read(reinterpret_cast<char*>(&id), sizeof(id));
        is.read(reinterpret_cast<char*>(&ownerId), sizeof(ownerId));
        torrent.readBase(is);
    }
};