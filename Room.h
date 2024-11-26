#pragma once
#include "Monster.h"

class Room
{
public:
    Monster insideMonster;
    Room() : insideMonster() {}
    Room(const Monster &input) : insideMonster(input) {}

    Monster getMonster() {
        return insideMonster;
    }

    friend std::ostream& operator<<(std::ostream& os, const Room& room) {
        os << room.insideMonster;
        return os;
    }
};