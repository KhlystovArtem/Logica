#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <queue>

using namespace std;

struct graph {
	int** matrix;
	int size;
}m;

typedef struct Node {
	int num;
	Node* next;
	Node* back;
}Node;

typedef struct HeadCells {
	Node* start = NULL;
	int empty;
	int num;
}HeadCells;

Node* it;

int* NUM;

HeadCells** headers;

void outputMatrix(graph m) {
	printf_s("   ");
	for (int i = 0; i < m.size; i++) {
		printf_s("%2d ", i);
	}
	printf_s("\n");
	for (int i = 0; i < m.size; i++) {
		printf_s("%2d ", i);
		for (int j = 0; j < m.size; j++) {
			printf_s("%2d ", m.matrix[i][j]);
		}
		printf_s("\n");
	}
}

//Заполнение массива
void fillMatrix(graph m) {
	int value;
	for (int i = 0; i < m.size; i++) {
		for (int j = i + 1; j < m.size; j++) {

			value = rand() % 10;
			if (value < 3)
				value = 0;
			else
				value = 1;

			m.matrix[i][j] = value;
			m.matrix[j][i] = m.matrix[i][j];
		}
	}
}

//Создание двумерного массива
int** createMatrix(int size) {
	int** matrix = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		matrix[i] = (int*)calloc(size, sizeof(int));
	}
	return matrix;
}

HeadCells** createHList(int size) {
	HeadCells** Headers = (HeadCells**)malloc(size * sizeof(HeadCells*));
	for (int i = 0; i < size; i++) {
		Headers[i] = (HeadCells*)malloc(sizeof(HeadCells));
		Headers[i]->start = NULL;
		Headers[i]->empty = 1;
	}
	return Headers;
}

Node* createNode() {
	Node* N = (Node*)malloc(sizeof(Node));
	N->back = NULL;
	N->next = NULL;
	return N;
}

void output_alist(HeadCells** headers, int size) {
	int i = 0;
	HeadCells* work_vertex;
	Node* tmp;
	for (int i = 0; i < size; i++) {
		work_vertex = headers[i];
		tmp = work_vertex->start;
		printf_s("%d. ", i);
		if (tmp == NULL) {
			printf("-");
		}
		while (tmp != NULL) {
			printf_s("%d ", tmp->num);
			tmp = tmp->next;
		}
		printf_s("\n");
	}
}

void push_back(HeadCells* list, int num) {
	Node* tmp;
	if (list->empty == 1) {
		it->num = num;
		it->next = NULL;
		list->start = it;
		list->empty = 0;
	}
	else {
		tmp = createNode();
		tmp->num = num;
		tmp->next = NULL;
		it->next = tmp;
		tmp->back = it;
		it = tmp;
	}
}

HeadCells** matrix_to_list(graph m) {
	HeadCells** headers = createHList(m.size);
	int* line;
	HeadCells* workVertex;
	for (int i = 0; i < m.size; i++) {
		line = m.matrix[i];
		workVertex = headers[i];
		if (workVertex->empty == 1) {
			it = createNode();
		}
		for (int j = 0; j < m.size; j++) {
			if (line[j] == 1) {
				push_back(workVertex, j);
			}
			else {
				continue;
			}
		}
	}
	return headers;
}



void BFS(int v, graph m, queue <int> q, int* NUM) {
	Node* tmp;
	q.push(v);
	NUM[v] = 1;
	while (q.empty() != true) {
		v = q.front();
		tmp = headers[v]->start;
		q.pop();
		printf_s("%d ", v);
		while (tmp != NULL) {
			if (NUM[tmp->num] == 0) {
				q.push(tmp->num);
				NUM[tmp->num] = 1;
			}
			tmp = tmp->next;
		}
	}
}

bool checkNewVertex(int* NUM) {
	for (int i = 0; i < m.size; i++) {
		if (NUM[m.size - i - 1] == 0) {
			return true;
			break;
		}
	}
	return false;
}

int main()
{

	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	queue <int> q;
	int* NUM = (int*)calloc(m.size, sizeof(int));
	int v;

	printf_s("Количество вершин графа:");
	scanf_s("%d", &m.size);
	NUM = (int*)calloc(m.size, sizeof(int));

	m.matrix = createMatrix(m.size);
	fillMatrix(m);
	outputMatrix(m);
	
	printf("\n");

	headers = matrix_to_list(m);
	output_alist(headers, m.size);

	printf_s("\nНачать обход с вершины:");
	scanf_s("%d", &v);


	printf_s("\nОбход:\n");
	while (checkNewVertex(NUM)) {
		BFS(v, m, q, NUM);
	}

}