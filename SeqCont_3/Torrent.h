#pragma once
#include <string>
#include <iostream>
#include "Date.h"

class Torrent {
private:
    int id;
    std::string name;
    double totalSize;
    std::string category;
    std::string uploaderName;
    Date createdAt;
    int seeders;
    int leechers;
    int ownerCode;   

public:
    Torrent();
    Torrent(int id, const std::string& name, double totalSize,
 const std::string& category, const std::string& uploaderName,
 const Date& createdAt, int seeders, int leechers,
 int ownerCode = 0);

    int  getId() const;
    const std::string& getName() const;
    double getTotalSize() const;
    const std::string& getCategory() const;
    const std::string& getUploaderName() const;
    Date getCreatedAt() const;
    int  getSeeders() const;
    int  getLeechers() const;
    int  getOwnerCode() const;

    void setId(int id);
    void setName(const std::string& name);
    void setTotalSize(double totalSize);
    void setCategory(const std::string& category);
    void setUploaderName(const std::string& uploaderName);
    void setCreatedAt(const Date& createdAt);
    void setSeeders(int seeders);
    void setLeechers(int leechers);
    void setOwnerCode(int ownerCode);

    void print(std::ostream& os) const;
    void read(std::istream& is);

    void writeBase(std::ostream& os) const;
    void readBase(std::istream& is);

    static void writeString(std::ostream& os, const std::string& s);
    static void readString(std::istream& is, std::string& s);

    bool operator==(const Torrent& other) const;
    bool operator!=(const Torrent& other) const;
    bool operator< (const Torrent& other) const;
    bool operator> (const Torrent& other) const;
    bool operator<=(const Torrent& other) const;
    bool operator>=(const Torrent& other) const;

    friend std::istream& operator>>(std::istream& is, Torrent& t);
    friend std::ostream& operator<<(std::ostream& os, const Torrent& t);
};