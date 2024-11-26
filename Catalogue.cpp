#include "Catalogue.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

bool Catalogue::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        return false;
    }

    std::string line;
    if (!std::getline(file, line)) {
        std::cerr << "El archivo CSV está vacío o tiene un formato incorrecto" << std::endl;
        return false;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        std::string attributes[MONSTER_ATTRIB_SIZE];

        for (int i = 0; i < MONSTER_ATTRIB_SIZE; i++) {
            if (!std::getline(ss, token, ',')) {
                std::cerr << "Error en el formato del archivo CSV" << std::endl;
                return false;
            }
            attributes[i] = token;
        }

        Monster obj;
        obj.setName(attributes[0]);
        obj.setCR(std::stod(attributes[1]));
        obj.setType(attributes[2]);
        obj.setSize(attributes[3]);
        obj.setAC(std::stoi(attributes[4]));
        obj.setHP(std::stoi(attributes[5]));
        obj.setAlign(attributes[6]);

        if (!inserta(obj)) {
            std::cerr << "Error al insertar el objeto en el catálogo" << std::endl;
            return false;
        }
    }

    file.close();
    return true;
}

Monster* Catalogue::getRandomObject() {
    int totalNodos = getSize();
    if (totalNodos == 0) {
        return nullptr;
    }
    int randomIndex = rand() % totalNodos;
    return obtenerEnOrden(randomIndex);
}

Monster* Catalogue::obtenerEnOrden(int index) {
    int contador = 0;
    Monster* resultado = nullptr;

    arbolMonstruos.recorrerInOrder([&](Monster& dato) {
        if (contador == index) {
            resultado = &dato;
        }
        contador++;
        });

    return resultado;
}