#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <conio.h> 
#include <iostream> 
#include <locale.h>
#include <list>
#include <iterator>

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


int null_exist(int* NUM, int size) {
	for (int i = 0; i < size; i++) {
		if (NUM[i] != 1) {
			return i;
		}
	}
	return -1;
}

int* generate_list(int size, int value) {
	int* NUM = (int*)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		NUM[i] = value;
	}
	return NUM;
}

void DFS(int v) {
	NUM[v] = 1;
	Node* tmp = headers[v]->start;
	printf("%d ", v);
	while (tmp != NULL) {
		if (NUM[tmp->num] == 0) {
			DFS(tmp->num);
		}
		tmp = tmp->next;
	}
}


int** createMatrix(int size) {
	int** matrix = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		matrix[i] = (int*)calloc(size, sizeof(int));
	}
	return matrix;
}

void fillMatrix(graph m) {
	srand(time(NULL));
	int value;
	for (int i = 0; i < m.size; i++) {
		for (int j = i + 1; j < m.size; j++) {

			value = rand() % 10;
			if (value < 7)
				value = 0;
			else
				value = 1;

			m.matrix[i][j] = value;
			m.matrix[j][i] = m.matrix[i][j];
		}
	}
}

void outputMatrix(graph m) {
	printf_s("  ");
	for (int i = 0; i < m.size; i++) {
		printf_s("%d ", i);
	}
	printf_s("\n");
	for (int i = 0; i < m.size; i++) {
		printf_s("%d ", i);
		for (int j = 0; j < m.size; j++) {
			printf_s("%d ", m.matrix[i][j]);
		}
		printf_s("\n");
	}
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
		while (tmp != NULL){
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
		for (int j =0; j < m.size; j++) {
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



int main() {
	setlocale(LC_ALL, "Rus");
	int v = 0;

	printf("Введите размер матрицы: \n");
	scanf("%d", &m.size);

	while (true) {
		printf("Введите вершину для начала обхода: \n");
		scanf("%d", &v);
		if (v >= 0 && v < m.size) {
			break;
		}
		else {
			printf("Некорректное значение!\n");
			continue;
		}
	}

	m.matrix = createMatrix(m.size);
	fillMatrix(m);

	outputMatrix(m);
	printf("\n");

	headers = matrix_to_list(m);
	output_alist(headers, m.size);

	NUM = generate_list(m.size, 0);

	printf("\n");
	printf("Рекурсивная реализация DFS:\n");
	
	do {
		DFS(v);
		printf("\n");
	} while ((v = null_exist(NUM, m.size)) != -1);


	return 0;
}