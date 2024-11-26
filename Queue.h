#pragma once

template <typename T>
class Queue {
private:
    class Node {
    public:
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* front;
    Node* rear;
    unsigned int count;

    bool* visited;
    unsigned int* prevNodes;

public:
    Queue(unsigned int size) : front(nullptr), rear(nullptr), count(0) {
        visited = new(std::nothrow) bool[size] {false};
        prevNodes = new(std::nothrow) unsigned int[size];

        if (!visited || !prevNodes) {
            throw std::bad_alloc();
        }

        for (unsigned int i = 0; i < size; ++i) {
            prevNodes[i] = -1;
        }
    }

    ~Queue() {
        delete[] visited;
        delete[] prevNodes;
        while (!empty()) {
            dequeue();
        }
    }

    bool enqueue(const T& value) {
        Node* newNode = new(std::nothrow) Node(value);
        if (!newNode) {
            return false;
        }

        if (rear) {
            rear->next = newNode;
        }
        rear = newNode;
        if (!front) {
            front = rear;
        }
        ++count;
        return true;
    }

    bool dequeue() {
        if (empty()) {
            return false;
        }

        Node* temp = front;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        delete temp;
        --count;
        return true;
    }

    T* getFront() const {
        if (empty()) {
            return nullptr;
        }
        return &front->data;
    }

    bool empty() const {
        return count == 0;
    }

    void markVisited(unsigned int index) {
        visited[index] = true;
    }

    bool isVisited(unsigned int index) const {
        return visited[index];
    }

    void setPrev(unsigned int index, unsigned int prevIndex) {
        prevNodes[index] = prevIndex;
    }

    unsigned int getPrev(unsigned int index) const {
        return prevNodes[index];
    }
};
