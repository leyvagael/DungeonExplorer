#pragma once
#include <iostream>

template <typename T>
class List {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node* prev;

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Node* head;

    void deleteList() {
        if (head) {
            Node* tmp = head;
            while (tmp != nullptr) {
                Node* next = tmp->next;
                delete tmp;
                tmp = next;
            }
        }
    }

public:
    class Iterator { //Sobrecargar *, ==, != y ++.
    private:
        Node* current;

    public:
        Iterator(Node* start) : current(start) {}
        bool next() {
            if (current) {
                current = current->next;
                return current != nullptr;
            }
            return false;
        }
        T getValue() const {
            if (!current) {
                throw std::out_of_range("Iterador fuera de rango.");
            }
            return current->data;
        }
        bool isValid() const {
            return current != nullptr;
        }
    };

    Iterator getIterator() const {
        return Iterator(head);
    }



    List() : head(nullptr) {}

    ~List() {
        deleteList();
    }

    Node* getHead() const {
        return head;
    }

    bool newEndNode(T data) {
        Node* new_node = new(std::nothrow) Node(data);
        if (!new_node) {
            return false;
        }

        if (head == nullptr) {
            head = new_node;
        }
        else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
            new_node->prev = current;
        }
        return true;
    }

    bool contains(T value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void reverse() {
        Node* current = head;
        Node* prev = nullptr;

        while (current != nullptr) {
            Node* next = current->next;
            current->next = prev;
            current->prev = next;
            prev = current;
            current = next;
        }
        head = prev;
    }

    std::string toString() const {
        std::stringstream ss;
        Node* current = head;
        while (current != nullptr) {
            ss << current->data;
            if (current->next != nullptr) {
                ss << ", ";
            }
            current = current->next;
        }
        return ss.str().empty() ? "Sin conexiones" : ss.str();
    }

    void printPath() const {
        Node* current = head;
        while (current) {
            std::cout << current->data;
            if (current->next) {
                std::cout << ", ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
};