#pragma once
#include "Room.h"
#include "Graph.h"
#include "DLinkedList.h"

class Dungeon {
private:
    Graph<Room> rooms;
    List<int> currentPath;
    List<int>::Iterator pathIterator;

public:
    Dungeon() : pathIterator(currentPath.getIterator()) {}

    bool createDungeon(std::string filename) {
        return rooms.loadFromFile(filename);
    }

    bool createRoom(unsigned int index, Monster& monster) {
        Room newRoom(monster);
        return rooms.setVertex(index, newRoom);
    }

    unsigned int getSize() {
        return rooms.getSize();
    }

    void showRooms() {
        rooms.print();
    }

    bool trazaRuta(unsigned int inicio, unsigned int fin) {
        currentPath = List<int>();
        pathIterator = currentPath.getIterator();

        if (!rooms.BFSPATH(inicio, fin, currentPath)) {
            return false;
        }

        pathIterator = currentPath.getIterator();
        return true;
    }

    bool avanzaRuta() {
        return pathIterator.next();
    }

    Room* cuartoActualRuta() {
        if (!pathIterator.isValid()) {
            return nullptr;
        }
        int roomIndex = pathIterator.getValue();
        return &rooms.getVertex(roomIndex).data;
    }
};
