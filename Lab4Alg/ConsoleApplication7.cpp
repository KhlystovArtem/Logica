
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <conio.h> 
#include <iostream> 
#include <locale.h>


// GLOBAL

int* NUM;
int* history;
int flag = 0;


struct graph {
	int** matrix;
	int* names;
	int size;
}m;



int** createMatrix(int size) {
	int** matrix = (int**)malloc(size * sizeof(int*));
	for (int i = 0; i < size; i++) {
		matrix[i] = (int*)calloc(size, sizeof(int));
	}
	return matrix;
}

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
	printf("%d ", v);
	for (int i = 0; i < m.size; i++){
		if (m.matrix[v][i] == 1 && NUM[i] == 0) {
			DFS(i);
		}
	}
}

int DFS_no_recursion(int v) {
	int i = 0;
	history[i] = v;
	NUM[v] = 1;
	if (flag == 0) {
		printf("%d ", v);
		flag = -1;
	}
	for (int j = 0; j < m.size; j++) {
		if (m.matrix[v][j] == 1 && NUM[j] == 0) {
			i++;
			history[i] = j;
			printf("%d ", j);
			return history[i];
		}
	}
	history[i] = -1;
	i--;
	return history[i];
}


int main() {
	setlocale(LC_ALL, "Rus");
	int v = 0;
	m.size = 5;

	m.matrix = createMatrix(m.size);

	fillMatrix(m);

	outputMatrix(m);
	printf("\n");

	NUM = generate_list(m.size, 0);

	printf("Рекурсивная реализация DFS:\n");
	while (true) {
		if ((v = null_exist(NUM, m.size)) != -1) {
			DFS(v);
			printf("\n");
		}
		break;
	}

	///

	printf("Нерекурсивная реализация DFS:\n");

	history = generate_list(m.size, -1);
	NUM = generate_list(m.size, 0);
	int last;
	while ((v = null_exist(NUM, m.size)) != -1) {
		last = v;
		do {
			last = DFS_no_recursion(last);
		} while (history[0] != -1);
		printf("\n");

	}
}
