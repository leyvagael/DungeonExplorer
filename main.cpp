//Situación problema: Entrega final
//Heli Jesse Aguilar Olea A01666805
//Gael Leyva ´Martínez A01660387

//Verificar encapsulamiento en Queue y Grafo

#include <iostream>
#include <ctime>
#include "Catalogue.h"
#include "Dungeon.h"
#include "Monster.h"

#define NUM_CUARTOS 20

using namespace std;

int main()
{
    srand(time(0));
    unsigned int inicio, fin;
    Catalogue miCatalogo;
    Dungeon miDungeon;

    if (!miCatalogo.loadFromCSV("monsters.csv")) {
        cout << "No se pudo crear el catálogo" << endl;
        return 0;
    }

    cout << "Creando Dungeon..." << endl;
    if (!miDungeon.createDungeon("dungeon.txt")) {
        cout << "No se pudo crear el dungeon" << endl;
        return 0;
    }
    for (unsigned int c = 0; c < miDungeon.getSize(); c++) {
        Monster* pMonster = nullptr, copiaMonstruo;

        pMonster = miCatalogo.getRandomObject();
        if (!pMonster) {
            cout << "No se pudo obtener un monstruo del catalogo" << endl;
            return 0;
        }

        copiaMonstruo = *pMonster;
        if (!miDungeon.createRoom(c, copiaMonstruo)) {
            cout << "No se pudo insertar cuarto con monstruo al dungeon" << endl;
            return 0;
        }
    }

    miDungeon.showRooms();

    cout << "Elije una ruta:\n";
    do {
        cout << "Dame el cuarto inicial: ";
        cin >> inicio;
        cout << "Dame el cuarto final: ";
        cin >> fin;
    } while (fin > miDungeon.getSize() || inicio == fin);

    if (!miDungeon.trazaRuta(inicio, fin)) {
        cout << "No existe ruta de " << inicio << " a " << fin << "\n";
        return 0;
    }

    do {
        Room* actual = nullptr;

        actual = miDungeon.cuartoActualRuta();
        if (actual) {
            cout << "Entrando a " << *actual << "\n";
        }
    } while (miDungeon.avanzaRuta());


    return 0;
}