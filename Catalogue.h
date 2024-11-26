#pragma once
#include <iostream>
#include "Monster.h"
#include "BST.h"

class Catalogue {
private:
    ArbolBinario<Monster> arbolMonstruos; //Cambiar por AVL
    int size;

public:
    Catalogue() : size(0) {}
    bool inserta(const Monster& obj) {
        if (arbolMonstruos.inserta(obj)) {
            size++;
            return true;
        }
        return false;
    }
    bool loadFromCSV(const std::string& filename);
    Monster* getRandomObject();

private:
    int getSize() const {
        return size;
    }
    Monster* obtenerEnOrden(int index);
};