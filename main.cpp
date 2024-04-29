#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class MyVector {
    int size;
    int* tab;
    int capacity;

public:
    MyVector() {
        size = 0;
        tab = new int[1];
        capacity = 1;
    }

    MyVector(int size) {
        this->size = size;
        tab = new int[size];
        capacity = size;
    }

    MyVector(const MyVector& other) {
        size = other.size;
        capacity = other.capacity;
        tab = new int[capacity];
        for (int i = 0; i < size; ++i) {
            tab[i] = other.tab[i];
        }
    }

    ~MyVector() {
        delete[] tab;
    }

    MyVector& operator=(const MyVector& other) {
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

    void set(int index, int value) {
        if (index >= 0 && index < size) {
            tab[index] = value;
        }
    }

    int get(int index) {
        if (index >= 0 && index < size) {
            return tab[index];
        }
    }

    int getSize() {
        return size;
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

    int& operator[](int index) {
        if (index >= 0 && index < size) {
            return tab[index];
        }
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
void degreeSequence (MyVector* graph, int numberOfNodes) {
    int* degree = new int[numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        if (graph[i][0] == -1) {
			degree[i] = 0;
        }
        else {
			degree[i] = graph[i].getSize();
		}
    }
    quickSort(degree, numberOfNodes);
    for (int i = 0; i < numberOfNodes; i++) {
		printf("%d ", degree[i]);
	}
    return;
}

/*
//liczba sk³adowych spójnoœci 
// (true/false)
void numberOfComponents (MyVector* graph, int numberOfNodes) {

}

//dwudzielnoœæ grafu 
// (true/false)
void bipartiteness(MyVector* graph, int numberOfNodes) {

}

//acentrycznoœci  wierzcho³ków (w ramach sk³adowych spójnoœci) 
// (ci¹g n liczb)
void eccentricityOfVertices(MyVector* graph, int numberOfNodes) {

}

//planarnoœæ grafu (true/false)
void planarity(MyVector* graph, int numberOfNodes) {

}

// kolorowanie wierzcho³ków grafu algorytmem zach³annym
// w kolejnoœci wierzcho³ków zgodnej z numerem wierzcho³ka 
// (ci¹g n liczb)
void verticesColoursGreedy(MyVector* graph, int numberOfNodes) {

}

// kolorowanie wierzcho³ków grafu algorytmem LF
// (remisy rozwi¹zujemy przy pomocy numeru wierzcho³ka) 
// (ci¹g n liczb)
void verticesColoursLF(MyVector* graph, int numberOfNodes) {

}

// kolorowanie wierzcho³ków grafu algorytmem SLF  
// (w przypadku remisu wybierz wierzcho³ek z najwy¿szym stopniem, 
// a jeœli nadal jest remis to wierzcho³ek o najmniejszym indeksie) 
// (ci¹g n liczb)
void verticesColoursSLF(MyVector* graph, int numberOfNodes) {

}

// liczba ró¿nych podgrafów C4 
// (liczba)
void c4Subgraphs(MyVector* graph, int numberOfNodes) {

}

// liczba krawêdzi dope³nienia grafu 
// (liczba)
void complementsEdges(MyVector* graph, int numberOfNodes) {

}
*/

void inputGraph() {
    int numberOfNodes = 0;
    scanf("%d", &numberOfNodes);

    int numberOfNeighbours = 0;
    int neighbour = 0;

    MyVector* graph = new MyVector[numberOfNodes];

    for (int i = 0; i < numberOfNodes; i++) {
        scanf("%d", &numberOfNeighbours);
        MyVector neighbours;
        if (numberOfNeighbours == 0) {
            neighbours.push_back(-1);
        }
        for (int j = 0; j < numberOfNeighbours; j++) {
            scanf("%d", &neighbour);
            neighbours.push_back(neighbour);
        }
        graph[i] = neighbours;
    }

    /*
    printf("\n");
    for (int i = 0; i < numberOfNodes; i++) {
        for (int j = 0; j < graph[i].getSize(); j++) {
			printf("%d ", graph[i].get(j));
		}
		printf("\n");
	}
    */

    printf("\n1. Ciag stopniowy: ");
    degreeSequence(graph, numberOfNodes);
    /*
    printf("\n2. Liczba skladowych spojnosci: ");
    numberOfComponents(graph, numberOfNodes);
    printf("\n3. Dwudzielnosc grafu: ");
    bipartiteness(graph, numberOfNodes);
    printf("\n4. Acentrycznosc wierzcholkow: ");
    eccentricityOfVertices(graph, numberOfNodes);
    printf("\n5. Planarnosc grafu: ");
    planarity(graph, numberOfNodes);
    printf("\n6. Kolory wierzcholkow (zachlannie): ");
    verticesColoursGreedy(graph, numberOfNodes);
    printf("\n7. Kolory wierzcholkow (LF): ");
    verticesColoursLF(graph, numberOfNodes);
    printf("\n8. Kolory wierzcholkow (SLF): ");
    verticesColoursSLF(graph, numberOfNodes);
    printf("\n9. Liczba roznych podgrafow C4: ");
    c4Subgraphs(graph, numberOfNodes);
    printf("\n10. Liczba krawedzi dopelnienia grafu: ");
    complementsEdges(graph, numberOfNodes); */
    printf("\n\n");
}

int main() {
    int numberOfGraphs = 0;
    scanf("%d", &numberOfGraphs);

    for (int i = 0; i < numberOfGraphs; i++) {
        inputGraph();
    }
    return 0;
}
