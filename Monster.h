#pragma once
#include <string>
#include <iostream>

#define MONSTER_ATTRIB_SIZE 7

class Monster {
private:
    std::string name;
    std::string type;
    std::string size;
    std::string align;
    double cr;
    int ac;
    int hp;

public:
    Monster() : name(""), cr(0), type(""), size(""), ac(0), hp(0), align("") {}
    void setName(std::string nName);
    void setCR(double nCR);
    void setType(std::string nType);
    void setSize(std::string nSize);
    void setAC(int nAC);
    void setHP(int nHP);
    void setAlign(std::string nAlign);
    void printCreatureData();

    std::string getName() const {
        return name;
    }

    bool operator<(const Monster& other) const {
        return name < other.name;
    }

    bool operator>(const Monster& other) const {
        return name > other.name;
    }

    bool operator==(const Monster& other) const {
        return name == other.name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Monster& monster) {
        os << "Name: " << monster.name
            << ", AC: " << monster.ac
            << ", HP: " << monster.hp;
        return os;
    }
};