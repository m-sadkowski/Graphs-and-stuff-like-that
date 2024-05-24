#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// tablica dynamiczna
class Vector {
    int* tab;
    int capacity;

public:
    int size;

    Vector() {
        size = 0;
        tab = new int[1];
        capacity = 1;
    }

    explicit Vector(int size) {
        this->size = size;
        tab = new int[size];
        capacity = size;
    }

    Vector(const Vector& other) {
        size = other.size;
        capacity = other.capacity;
        tab = new int[capacity];
        for (int i = 0; i < size; ++i) {
            tab[i] = other.tab[i];
        }
    }

    ~Vector() {
        delete[] tab;
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) {
            return *this;
        }

        delete[] tab;

        size = other.size;
        capacity = other.capacity;
        tab = new int[capacity];
        for (int i = 0; i < size; ++i) {
            tab[i] = other.tab[i];
        }

        return *this;
    }

    int get(int index) const {
        if (index >= 0 && index < size) {
            return tab[index];
        }
        return 0;
    }

    void push_back(int value) {
        if (size >= capacity) {
            int newCapacity = capacity * 2;
            int* newTab = new int[newCapacity];
            for (int i = 0; i < size; ++i) {
                newTab[i] = tab[i];
            }
            delete[] tab;
            tab = newTab;
            capacity = newCapacity;
        }
        tab[size] = value;
        size++;
    }
};

// kolejka FIFO
class Stack {
    Vector vec;

public:
    Stack() : vec() {}

    void push(int value) {
        vec.push_back(value);
    }

    void pop() {
        if (!isEmpty()) {
            vec.size--;
        }
    }

    int top() const {
        if (!isEmpty()) {
            return vec.get(vec.size - 1);
        }
        return 0;
    }

    bool isEmpty() const {
        return vec.size == 0;
    }
};

// stos LIFO
class Queue {
    Vector vec;
    int frontElement;

public:
    Queue() : frontElement(0) {}

    void push(int value) {
        vec.push_back(value);
    }

    void pop() {
        if (!isEmpty()) {
            frontElement++;
        }
    }

    int front() const {
        if (!isEmpty()) {
            return vec.get(frontElement);
        }
        return 0;
    }

    bool isEmpty() const {
        return frontElement >= vec.size;
    }

    int size() const {
		return vec.size - frontElement;
	}
};

void quickSort(int* tab, int size) {
    if (size <= 1) return;

    int pivot = tab[size / 2];
    int i = 0;
    int j = size - 1;

    while (i <= j) {
        while (tab[i] < pivot) {
            i++;
        }
        while (tab[j] > pivot) {
            j--;
        }
        if (i <= j) {
            int temp = tab[i];
            tab[i] = tab[j];
            tab[j] = temp;
            i++;
            j--;
        }
    }

    quickSort(tab, j + 1);
    quickSort(tab + i, size - i);
}

//ci¹gu stopniowy 
// (ci¹g n liczb)
void degreeSequence(Vector* graph, int numberOfNodes) {
    int* degree = new int[numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        degree[i] = graph[i].size;
    }
    quickSort(degree, numberOfNodes);
    printf("\n");
    for (int i = numberOfNodes - 1; i >= 0; i--) {
        printf("%d ", degree[i]);
    }
    delete[] degree;
    return;
}

//liczba sk³adowych spójnoœci
// (liczba)
void DFS(Vector* graph, int startNode, int* visited) {
    Stack stack;
    stack.push(startNode);

    while (!stack.isEmpty()) {
        int node = stack.top();
        stack.pop();
        if (!visited[node]) {
            visited[node] = 1;
            for (int i = graph[node].size - 1; i >= 0; i--) {
                int neighbour = graph[node].get(i) - 1;
                if (!visited[neighbour]) {
                    stack.push(neighbour);
                }
            }
        }
    }

    return;
}

bool numberOfComponents(Vector* graph, int numberOfNodes) {
    int* visited = new int[numberOfNodes];
	for (int i = 0; i < numberOfNodes; i++) {
		visited[i] = 0;
	}
    int components = 0;
    for (int i = 0; i < numberOfNodes; i++) {
        if (visited[i] == 0) {
            DFS(graph, i, visited);
            components++;
        }
    }
    printf("\n%d", components);
    delete[] visited;
    if (components == 1) {
		return true;
	}
    return false;
}

//dwudzielnoœæ grafu
// (true/false)
void bipartiteness(Vector* graph, int numberOfNodes) {
    int* colours = new int[numberOfNodes];
	for (int i = 0; i < numberOfNodes; i++) {
		colours[i] = 0;
	}

    Queue queue;

    for (int i = 0; i < numberOfNodes; i++) {
        if (colours[i] == 0) {
			colours[i] = 1;
			queue.push(i);
            while (!queue.isEmpty()) {
                int node = queue.front();
                queue.pop();
                for (int j = 0; j < graph[node].size; j++) {
                    int neighbour = graph[node].get(j) - 1;
                    if (colours[neighbour] == 0) {
                        if (colours[node] == 1) {
                            colours[neighbour] = 2;
                        }
                        else {
                            colours[neighbour] = 1;
                        }
                        queue.push(neighbour);
                    }
                    else if (colours[neighbour] == colours[node]) {
                        printf("\nF");
                        delete[] colours;
                        return;
                    }
                }
             }
         }
     }

    

    printf("\nT");
    delete[] colours;
    return;
}

//acentrycznoœci  wierzcho³ków (w ramach sk³adowych spójnoœci)
// (ci¹g n liczb)
void eccentricityOfVertices(Vector* graph, int numberOfNodes) {
    printf("\n?");
}

//planarnoœæ grafu (true/false)
void planarity(Vector* graph, int numberOfNodes) {
    printf("\n?");
}

// kolorowanie wierzcho³ków grafu algorytmem zach³annym
// w kolejnoœci wierzcho³ków zgodnej z numerem wierzcho³ka
// (ci¹g n liczb)
void verticesColoursGreedy(Vector* graph, int numberOfNodes) {
    printf("\n?");
}

// kolorowanie wierzcho³ków grafu algorytmem LF
// (remisy rozwi¹zujemy przy pomocy numeru wierzcho³ka)
// (ci¹g n liczb)
void verticesColoursLF(Vector* graph, int numberOfNodes) {
    printf("\n?");
}

// kolorowanie wierzcho³ków grafu algorytmem SLF
// (w przypadku remisu wybierz wierzcho³ek z najwy¿szym stopniem,
// a jeœli nadal jest remis to wierzcho³ek o najmniejszym indeksie)
// (ci¹g n liczb)
void verticesColoursSLF(Vector* graph, int numberOfNodes) {
    printf("\n?");
}

// liczba ró¿nych podgrafów C4
// (liczba)
void c4Subgraphs(Vector* graph, int numberOfNodes) {
    printf("\n?");
}

// liczba krawêdzi dope³nienia grafu
// (liczba)
void complementsEdges(Vector* graph, int numberOfNodes) {
    long long edges = 0;
    long long nodes = long long(numberOfNodes);
    for (long long i = 0; i < nodes; i++) {
        edges += graph[i].size;
    }
    long long complementEdges = (nodes * (nodes - 1) / 2) - (edges / 2);
    printf("\n%lld", complementEdges);
    return;
}

void inputGraph() {
    int numberOfNodes = 0;
    scanf("%d", &numberOfNodes);

    int numberOfNeighbours = 0;
    int neighbour = 0;

    Vector* graph = new Vector[numberOfNodes];

    for (int i = 0; i < numberOfNodes; i++) {
        scanf("%d", &numberOfNeighbours);
        Vector neighbours;
        for (int j = 0; j < numberOfNeighbours; j++) {
            scanf("%d", &neighbour);
            neighbours.push_back(neighbour);
        }
        graph[i] = neighbours;
    }

    /*
    printf("\n");
    for (int i = 0; i < numberOfNodes; i++) {
        for (int j = 0; j < graph[i].size(); j++) {
            printf("%d ", graph[i].get(j));
        }
        printf("\n");
    }
    */

    degreeSequence(graph, numberOfNodes);

    numberOfComponents(graph, numberOfNodes);

    bipartiteness(graph, numberOfNodes);

    eccentricityOfVertices(graph, numberOfNodes);

    planarity(graph, numberOfNodes);

    verticesColoursGreedy(graph, numberOfNodes);

    verticesColoursLF(graph, numberOfNodes);

    verticesColoursSLF(graph, numberOfNodes);

    c4Subgraphs(graph, numberOfNodes);

    complementsEdges(graph, numberOfNodes);

    printf("\n\n");

    delete[] graph;
}

int main() {
    int numberOfGraphs = 0;
    scanf("%d", &numberOfGraphs);

    for (int i = 0; i < numberOfGraphs; i++) {
        inputGraph();
    }

    return 0;
}
