#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <queue>

using namespace std;

clock_t start, stop;

struct graph {
	int** matrix;
	int size;
}m;



int* NUM;


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

typedef struct Node {
	int num;
	Node* next;
	Node* back;
}Node;

typedef struct que {
	Node* qstart;
	Node* qend;
	int count;
}que;

Node* createNode() {
	Node* N = (Node*)malloc(sizeof(Node));
	N->back = NULL;
	N->next = NULL;
	return N;
}

que* create_queue() {
	que* q = (que*)malloc(sizeof(que));
	q->count = 0;
	q->qstart = NULL;
	q->qend = NULL;
	return q;
};

void qpush(que* q,  int num) {
	Node* Element = createNode();
	Element->num = num;
	if (q->count == 0) {
		q->qstart = Element;
		q->qend = Element;
		q->count++;
	}
	else {
		if (q->count == 1) {
			q->qend = Element;
			q->qend->back = q->qstart;
			q->qstart->next = q->qend;
			q->count++;
		}
		else {
			q->qend->next = Element;
			q->qend = Element;
			q->count++;
		}
	}
};

int qfront(que* q) {
	int val;
	if (q->count == 0) {
		return NULL;
	}
	val = q->qstart->num;
	return val;
};

int qpop(que* q) {
	Node* n;
	if (q->count == 0) {
		return 0;
	}
	if (q->count == 1) {
		q->qstart = NULL;
		q->qend = NULL;
		q->count--;
		return 1;
	}
	else {
			n = q->qstart;
			q->qstart = q->qstart->next;
			q->qstart->back = NULL;
			free(n);
			q->count--;
			return 1;
		}
};




void BFS(int v, graph m, queue <int> q, int* NUM) {
	q.push(v);
	NUM[v] = 1;
	while (q.empty() != true) {
		v = q.front();
		q.pop();
		//printf_s("%d ", v);
		for (int i = 0; i < m.size; i++) {
			if (m.matrix[v][i] == 1 && NUM[i] == 0) {
				q.push(i);
				NUM[i] = 1;
			}
		}
	}
}

void BFS_h(int v, graph m, que* q, int* NUM) {
	qpush(q, v);
	NUM[v] = 1;
	while (q->count != 0) {
		v = qfront(q);
		qpop(q);
		//printf_s("%d ", v);
		for (int i = 0; i < m.size; i++) {
			if (m.matrix[v][i] == 1 && NUM[i] == 0) {
				qpush(q, i);
				NUM[i] = 1;
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
	que* qh = create_queue();
	int* NUM = (int*)calloc(m.size, sizeof(int));
	int* NUMh = (int*)calloc(m.size, sizeof(int));
	int v;

	printf_s("Количество вершин графа:");
	scanf_s("%d", &m.size);
	NUM = (int*)calloc(m.size, sizeof(int));
	NUMh = (int*)calloc(m.size, sizeof(int));

	m.matrix = createMatrix(m.size);
	fillMatrix(m);
	//outputMatrix(m);

	printf("\n");


	printf_s("\nНачать обход с вершины:");
	scanf_s("%d", &v);


	printf_s("\nОбход (queue):\n");
	start = clock();
	while (checkNewVertex(NUM)) {
		BFS(v, m, q, NUM);
	}
	stop = clock();
	printf("\nВремя выполнения: %d", (stop - start));


	printf_s("\nОбход (ручная очередь):\n");
	start = clock();
	while (checkNewVertex(NUMh)) {
		BFS_h(v, m, qh, NUMh);
	}
	stop = clock();
	printf("\nВремя выполнения: %d", (stop - start));
}