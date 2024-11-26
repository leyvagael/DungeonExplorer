#pragma once
#include <fstream>
#include <sstream>
#include <limits>
#include "DLinkedList.h"
#include "Queue.h"

template <typename T>
class Graph {
private:
    class Vertex {
    public:
        List<int> edges;
        bool visited;
        T data;

        Vertex() : edges(), data(), visited(false) {}
    };

    Vertex* vertices;
    unsigned int size;

    void erase() {
        if (vertices) {
            delete[] vertices;
            vertices = nullptr;
            size = 0;
        }
    }

    void resetVisited() {
        for (unsigned int i = 0; i < size; ++i) {
            vertices[i].visited = false;
        }
    }

public:
    Graph() : vertices(nullptr), size(0) {}

    ~Graph() {
        erase();
    }

    bool createGraph(unsigned int nSize) {
        if (nSize == 0) {
            return false;
        }
        erase();

        vertices = new(std::nothrow) Vertex[nSize];
        if (!vertices) {
            return false;
        }
        size = nSize;
        return true;
    }

    bool setVertex(unsigned int vertex, const T& data) {
        if (!size || vertex >= size) {
            return false;
        }
        vertices[vertex].data = data;
        return true;
    }

    Vertex& getVertex(unsigned int vertex) {
        return vertices[vertex];
    }

    bool addEdge(unsigned int from, unsigned int to) {
        if (from >= size || to >= size) {
            return false;
        }

        if (vertices[from].edges.contains(to)) {
            return false;
        }

        return vertices[from].edges.newEndNode(to);
    }

    void print() {
        for (unsigned int i = 0; i < size; ++i) {
            std::cout << "[" << i << "] Cuarto con: " << vertices[i].data << ": ";
            std::cout << vertices[i].edges.toString() << std::endl;
        }
    }

    unsigned int getSize() const {
        return size;
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Archivo sin abrir" << std::endl;
            return false;
        }

        std::string header;
        std::getline(file, header);
        if (header != "Grafo") {
            std::cerr << "Error: Formato inválido, falta la cabecera 'Grafo'" << std::endl;
            return false;
        }

        unsigned int numVertices;
        file >> numVertices;

        if (file.fail() || numVertices == 0) {
            std::cerr << "Error: Número de vértices inválido" << std::endl;
            return false;
        }

        if (!createGraph(numVertices)) {
            return false;
        }

        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::string line;
        for (unsigned int i = 0; i < numVertices; ++i) {
            std::getline(file, line);
            std::stringstream ss(line);
            int neighbor;

            while (ss >> neighbor) {
                if (!addEdge(i, neighbor)) {
                    std::cerr << "Error: No se pudo agregar arista (" << i << ", " << neighbor << ")." << std::endl;
                    return false;
                }
            }
        }

        file.close();
        return true;
    }

    bool BFSPATH(unsigned int startVertex, unsigned int endVertex, List<int>& path) {
        if (!size || startVertex >= size || endVertex >= size) {
            return false;
        }

        Queue<unsigned int> queue(size);

        if (!queue.enqueue(startVertex)) {
            return false;
        }
        queue.markVisited(startVertex);

        while (!queue.empty()) {
            unsigned int current = *queue.getFront();
            queue.dequeue();

            if (current == endVertex) {
                for (unsigned int at = endVertex; at != -1; at = queue.getPrev(at)) {
                    path.newEndNode(at);
                }
                path.reverse();

                path.printPath();
                return true;
            }

            auto* edge = vertices[current].edges.getHead();
            while (edge) {
                unsigned int neighbor = edge->data;

                if (!queue.isVisited(neighbor)) {
                    queue.markVisited(neighbor);
                    queue.setPrev(neighbor, current);
                    if (!queue.enqueue(neighbor)) {
                        return false;
                    }
                }

                edge = edge->next;
            }
        }
        return false;
    }
};