#pragma once
#include <iostream>

template <typename T>
class Lista {
private:
    class nodo {
    public:
        T data;
        nodo* next;

        nodo(const T& value) : data(value), next(nullptr) {}
    };

    nodo* head;

public:
    Lista() : head(nullptr) {}

    ~Lista() {
        eraseList();
    }

    bool insertarInicio(const T& data) {
        nodo* node = new(std::nothrow) nodo(data);

        if (!node) {
            return false;
        }
        
        if (head == nullptr) {
            head = node;
            node->next = nullptr;
        }
        
        node->next = head;
        head = node;
        return true;
    }

    void eraseList() {
        nodo* current = head;
        while (current != nullptr) {
            nodo* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

    void printMonsterName() {
        nodo tmp = head;
        while (tmp) {
            std::cout << tmp->data->getName() << std::endl;
            tmp = tmp->next;
        }
    }
};
