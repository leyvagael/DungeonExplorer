#include <iostream>
#include <functional>

template<typename T>
class ArbolBinario {
private:
    class NodoArbol {
    public:
        T dato;
        NodoArbol* left;
        NodoArbol* right;

        NodoArbol(T dato) : dato(dato), left(nullptr), right(nullptr) {}
        ~NodoArbol() {}
    };

    NodoArbol* root;

    void dfsInOrder(NodoArbol* nodo, std::function<void(T&)> func) const {
        if (!nodo) return;
        dfsInOrder(nodo->left, func);
        func(nodo->dato);
        dfsInOrder(nodo->right, func);
    }

    void dfsPostOrder(NodoArbol* nodo, std::function<void(NodoArbol*)> func) {
        if (!nodo) return;
        dfsPostOrder(nodo->left, func);
        dfsPostOrder(nodo->right, func);
        func(nodo);
    }


public:
    ArbolBinario() : root(nullptr) {}
    ~ArbolBinario() {
        borrarArbol();
    }

    bool inserta(T dato) {
        NodoArbol** current = &root;
        while (*current) {
            if (dato < (*current)->dato) {
                current = &(*current)->left;
            }
            else if (dato > (*current)->dato) {
                current = &(*current)->right;
            }
            else {
                return false;
            }
        }
        *current = new(std::nothrow) NodoArbol(dato);
        return *current != nullptr;
    }

    void recorrerInOrder(std::function<void(T&)> func) const {
        dfsInOrder(root, func);
    }

    void borrarArbol() {
        auto deleteNodo = [](NodoArbol* nodo) {
            delete nodo;
            };
        dfsPostOrder(root, deleteNodo);
        root = nullptr;
    }
};