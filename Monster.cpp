#include "Monster.h"

void Monster::setName(std::string nName) {
    name = nName;
}
void Monster::setCR(double nCR) {
    cr = nCR;
}
void Monster::setType(std::string nType) {
    type = nType;
}
void Monster::setSize(std::string nSize) {
    size = nSize;
}
void Monster::setAC(int nAC) {
    ac = nAC;
}
void Monster::setHP(int nHP) {
    hp = nHP;
}
void Monster::setAlign(std::string nAlign) {
    align = nAlign;
}

void Monster::printCreatureData() {
    std::cout << "Name: " << name << std::endl;
    std::cout << "cr: " << cr << std::endl;
    std::cout << "type: " << type << std::endl;
    std::cout << "size: " << size << std::endl;
    std::cout << "ac: " << ac << std::endl;
    std::cout << "hp: " << hp << std::endl;
    std::cout << "align: " << align << std::endl;
}