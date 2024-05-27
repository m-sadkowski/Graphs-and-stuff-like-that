#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// vector
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

    explicit Vector(int capacity) {
        size = 0;
        tab = new int[capacity + 1];
        this->capacity = capacity;
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

// stos (LIFO)
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

// kolejka (FIFO)
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

// ci¹gu stopniowy 
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
}

// liczba sk³adowych spójnoœci
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

void numberOfComponents(Vector* graph, int numberOfNodes) {
    int* visited = new int[numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        visited[i] = 0;
    }

    // zliczanie sk³adowych spójnoœci grafu przez DFS
    int components = 0;
    for (int i = 0; i < numberOfNodes; i++) {
        if (visited[i] == 0) {
            DFS(graph, i, visited);
            components++;
        }
    }
    printf("\n%d", components);
    delete[] visited;
}

// dwudzielnoœæ grafu
// (true/false)
void bipartiteness(Vector* graph, int numberOfNodes) {
    int* colours = new int[numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        colours[i] = 0;
    }
    Queue queue;

    // nadawanie kolorów na przemian do momentu próby nadania koloru wierzcho³kowi, który ma ju¿ nadany inny kolor
    for (int i = 0; i < numberOfNodes; i++) {
        if (colours[i] == 0) {
            colours[i] = 1;
            queue.push(i);
            // BFS
            while (!queue.isEmpty()) {
                int node = queue.front();
                queue.pop();
                for (int j = 0; j < graph[node].size; j++) {
                    int neighbour = graph[node].get(j) - 1;
                    // nadanie koloru wierzcho³kom na przemian
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
}

// acentrycznoœci  wierzcho³ków (w ramach sk³adowych spójnoœci)
// (ci¹g n liczb)
void eccentricityOfVertices(Vector* graph, int numberOfNodes) {
    printf("\n");
    // ¿aden wierzcho³ek nie jest odwiedzony
    int* visited = new int[numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        visited[i] = -1;
    }
    for (int i = 0; i < numberOfNodes; i++) {
        // BFS
        Queue queue;
        queue.push(i);
        visited[i] = i;
        int distance = 0;
        int pushed = 1;
        while (!queue.isEmpty()) {
            // pobieramy wierzcho³ek z kolejki i sprawdzamy jego s¹siadów
            int size = queue.size();
            for (int j = 0; j < size; j++) {
                int v = queue.front();
                queue.pop();
                // jeœli s¹siedzi nie s¹ odwiedzeni to dodajemy do kolejki
                for (int k = 0; k < graph[v].size; k++) {
                    int neighbour = graph[v].get(k) - 1;
                    if (visited[neighbour] != i) {
                        ++pushed;
                        // jeœli iloœæ dodanych wierzcho³ków jest równa iloœci wierzcho³ków w grafie to przerywamy BFS
                        if (pushed == numberOfNodes) break;
                        queue.push(neighbour);
                        visited[neighbour] = i;
                    }
                }
                if (pushed == numberOfNodes) break;
            }
            ++distance;
            if (pushed == numberOfNodes) {
                // zwiêkszamy odleg³oœæ o 1, bo je¿eli tu dojdzie to ostatni wierzcho³ek nie ma s¹siadów
                ++distance;
                break;
            }
        }
        printf("%d ", distance - 1);
    }
    delete[] visited;
}

//planarnoœæ grafu (true/false)
void planarity(Vector* graph, int numberOfNodes) {
    printf("\n?");
}

// kolorowanie wierzcho³ków grafu algorytmem zach³annym
// w kolejnoœci wierzcho³ków zgodnej z numerem wierzcho³ka
// (ci¹g n liczb)
void verticesColoursGreedy(Vector* graph, int numberOfNodes) {
    int* colours = new int[numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        colours[i] = 0;
    }

    // kolorowanie wierzcho³ków grafu w kolejnoœci inputu przypisuj¹c najmniejszy mo¿liwy kolor
    for (int i = 0; i < numberOfNodes; i++) {
        if (colours[i] == 0) {
            int smallest = 1;
            while (true) {
                bool colorAvailable = true;
                for (int j = 0; j < graph[i].size; j++) {
                    if (colours[graph[i].get(j) - 1] == smallest) {
                        colorAvailable = false;
                        break;
                    }
                }
                if (colorAvailable) {
                    colours[i] = smallest;
                    break;
                }
                smallest++;
            }
        }
    }

    printf("\n");
    for (int i = 0; i < numberOfNodes; i++) {
        printf("%d ", colours[i]);
    }
    delete[] colours;
}

// kolorowanie wierzcho³ków grafu algorytmem LF
// (remisy rozwi¹zujemy przy pomocy numeru wierzcho³ka)
// (ci¹g n liczb)
void merge(int** tab, int left, int middle, int right) {
    // tworzenie tablic pomocniczych
    int leftSize = middle - left + 1;
    int rightSize = right - middle;
    int** leftTab = new int* [leftSize];
    int** rightTab = new int* [rightSize];

    // kopiowanie elementów do tablic pomocniczych
    for (int i = 0; i < leftSize; i++) {
        leftTab[i] = tab[left + i];
    }
    for (int i = 0; i < rightSize; i++) {
        rightTab[i] = tab[middle + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    // porównywanie elementów tablic pomocniczych i przypisywanie ich do tablicy g³ównej
    while (i < leftSize && j < rightSize) {
        if (leftTab[i][1] >= rightTab[j][1]) {
            tab[k] = leftTab[i];
            i++;
        }
        else {
            tab[k] = rightTab[j];
            j++;
        }
        k++;
    }

    // przepisanie pozosta³ych elementów z tablic pomocniczych
    while (i < leftSize) {
        tab[k] = leftTab[i];
        i++;
        k++;
    }
    while (j < rightSize) {
        tab[k] = rightTab[j];
        j++;
        k++;
    }

    // zwalnianie pamiêci
    delete[] leftTab;
    delete[] rightTab;
}

void mergeSort(int** tab, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(tab, left, middle);
        mergeSort(tab, middle + 1, right);
        merge(tab, left, middle, right);
    }
}

void verticesColoursLF(Vector* graph, int numberOfNodes) {
    int** indexAndDegree = new int* [numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        indexAndDegree[i] = new int[2];
        indexAndDegree[i][0] = i;
        indexAndDegree[i][1] = graph[i].size;
    }

    // sortowanie tablicy indexAndDegree w kolejnoœci malej¹cej przy pomocy merge sort
    mergeSort(indexAndDegree, 0, numberOfNodes - 1);

    int* colours = new int[numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        colours[i] = 0;
    }

    // kolorowanie wierzcho³ków grafu posortowanego wed³ug stopni wierzcho³ków przypisuj¹c najmniejszy mo¿liwy kolor
    for (int i = 0; i < numberOfNodes; i++) {
        int x = indexAndDegree[i][0];
        if (colours[x] == 0) {
            int smallest = 1;
            while (true) {
                bool colorAvailable = true;
                for (int j = 0; j < graph[x].size; j++) {
                    if (colours[graph[x].get(j) - 1] == smallest) {
                        colorAvailable = false;
                        break;
                    }
                }
                if (colorAvailable) {
                    colours[x] = smallest;
                    break;
                }
                smallest++;
            }
        }
    }

    printf("\n");
    for (int i = 0; i < numberOfNodes; i++) {
        printf("%d ", colours[i]);
    }
    delete[] colours;
    for (int i = 0; i < numberOfNodes; i++) {
        delete[] indexAndDegree[i];
    }
    delete[] indexAndDegree;
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
/*bool DFS(Vector* graph, int node, int lastVisitedNode, int depth, int startNode, int& counter) {
    if (depth == 4 && node == startNode) {
        counter++;
    }
    if (depth == 4) {
        return false;
    }
	for (int i = 0; i < graph[node].size; i++) {
		int neighbour = graph[node].get(i) - 1;
		if (neighbour != lastVisitedNode) {
            if (DFS(graph, neighbour, node, depth + 1, startNode, counter)) {
                return true;
            }
        }
	}
    return false;
}

void c4Subgraphs(Vector* graph, int numberOfNodes) {
	int c4Subgraphs = 0;
    for (int i = 0; i < numberOfNodes; i++) {
        DFS(graph, i, -1, 0, i, c4Subgraphs);
    }
	printf("\n%d", c4Subgraphs / 4);
}*/
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
}

// wczytywanie grafu i wywo³ywanie funkcji
void inputGraph() {
    int numberOfNodes = 0;
    scanf("%d", &numberOfNodes);

    int numberOfNeighbours = 0;
    int neighbour = 0;

    Vector* graph = new Vector[numberOfNodes];

    for (int i = 0; i < numberOfNodes; i++) {
        scanf("%d", &numberOfNeighbours);
        Vector neighbours(numberOfNeighbours);
        for (int j = 0; j < numberOfNeighbours; j++) {
            scanf("%d", &neighbour);
            neighbours.push_back(neighbour);
        }
        graph[i] = neighbours;
    }

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
