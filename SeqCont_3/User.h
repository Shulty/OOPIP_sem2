#pragma once
#include <string>
#include <fstream>

class User {
public:
    enum class Role { User = 0, Admin = 1 };

private:
    int         id = -1;
    std::string login;
    std::string passwordHash; 
    Role        role = Role::User;

public:
    User() = default;
    User(int id, std::string login, std::string passwordHash, Role role)
        : id(id), login(std::move(login)),
        passwordHash(std::move(passwordHash)), role(role) {
    }

    int         getId()  const { return id; }
    const std::string& getLogin() const { return login; }
    const std::string& getPasswordHash() const { return passwordHash; }
    Role        getRole()         const { return role; }

    void setId(int v) { id = v; }
    void setLogin(const std::string& v) { login = v; }
    void setPasswordHash(const std::string& v) { passwordHash = v; }
    void setRole(Role r) { role = r; }

    bool isAdmin() const { return role == Role::Admin; }

    void write(std::ostream& os) const {
        os.write(reinterpret_cast<const char*>(&id), sizeof(id));
        int roleInt = static_cast<int>(role);
        os.write(reinterpret_cast<const char*>(&roleInt), sizeof(roleInt));

        writeString(os, login);
        writeString(os, passwordHash);
    }

    void read(std::istream& is) {
        is.read(reinterpret_cast<char*>(&id), sizeof(id));
        int roleInt = 0;
        is.read(reinterpret_cast<char*>(&roleInt), sizeof(roleInt));
        role = static_cast<Role>(roleInt);

        readString(is, login);
        readString(is, passwordHash);
    }

private:
    static void writeString(std::ostream& os, const std::string& s) {
        int len = static_cast<int>(s.size());
        os.write(reinterpret_cast<const char*>(&len), sizeof(len));
        os.write(s.data(), len);
    }
    static void readString(std::istream& is, std::string& s) {
        int len = 0;
        is.read(reinterpret_cast<char*>(&len), sizeof(len));
        s.resize(len);
        if (len > 0)
   is.read(&s[0], len);
    }
};