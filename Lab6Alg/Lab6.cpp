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

void outputMatrix(graph m) {
	for (int i = 0; i < m.size; i++) {
		for (int j = 0; j < m.size; j++) {
			printf_s("%d ", m.matrix[i][j]);
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
			if (value < 6)
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

void BFSD(int v, graph m, queue <int> q, int* DIST) {
	q.push(v);
	DIST[v] = 0;
	while (q.empty() != true) {
		v = q.front();
		q.pop();
		//printf_s("%d ", v + 1);
		for (int i = 0; i < m.size; i++) {
			if (m.matrix[v][i] == 1 && DIST[i] == -1) {
				q.push(i);
				DIST[i] = DIST[v] + 1;
			}
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
	int* DIST = (int*)calloc(m.size, sizeof(int));

	int v;

	printf_s("Количество вершин графа:");
	scanf_s("%d", &m.size);
	DIST = (int*)calloc(m.size, sizeof(int));

	for (int i = 0; i < m.size; i++) {
		DIST[i] = -1;
	}

	m.matrix = createMatrix(m.size);
	fillMatrix(m);
	outputMatrix(m);
	printf_s("\n");
	//printf_s("\nНачать обход с вершины:");
	//scanf_s("%d", &v);
	//v--;


	//printf_s("\nОбход:\n");
	//BFSD(v, m, q, DIST);
	printf_s("Расстояния до вершин: \n\n");

	for (int i = 0; i < m.size; i++) {
		printf_s("%2d:  ", i + 1);
		BFSD(i, m, q, DIST);

		for (int i = 0; i < m.size; i++) {
				printf_s("%d ", DIST[i]);
				DIST[i] = -1;
		}

		printf_s("\n");
	}

//	printf_s("\nРасстояния до вершин:\n");
//	for (int i = 0; i < m.size; i++) {
//		printf_s("%d ", DIST[i]);
//	}
}