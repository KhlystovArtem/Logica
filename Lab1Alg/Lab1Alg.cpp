//Лабораторная работа номер 1 получаеца.
#include <limits.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <Windows.h>

int max = INT_MIN;
int min = INT_MAX;

typedef struct result
{
	int difference;
	int* the_sum_of_the_values_rows;
	int* the_sum_of_the_values_cols;
}result;



int main()
{
	srand(time(NULL));
	result answer_task;
	int size_x, size_y;

	int** matrix;
	int value;
	printf("enter size of matrix:\n column =");
	scanf_s("%d", &size_x);
	printf("\n lines =");
	scanf_s("%d", &size_y);

	matrix = (int**)malloc(size_y * sizeof(int*));
	answer_task.the_sum_of_the_values_cols = (int*)calloc(size_x, sizeof(int));
	answer_task.the_sum_of_the_values_rows = (int*)calloc(size_y, sizeof(int));

	for (int i = 0; i < size_y; i++) {
		matrix[i] = (int*)malloc(size_x * sizeof(int));
		for (int j = 0; j < size_x; j++) {
			matrix[i][j] = -100 + (rand() % 200);
		}
	}
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			value = matrix[i][j];
			if (value > max) {
				max = value;
			}
			if (value < min) {
				min = value;
			}
			answer_task.the_sum_of_the_values_rows[i] += value;
			answer_task.the_sum_of_the_values_cols[j] += value;
		}
	}
	answer_task.difference = max - min;




	for (int i = 0; i < size_y; i++) {
		printf("\n");
		for (int j = 0; j < size_x; j++) {
			printf("%d\t", matrix[i][j]);
		}
		printf("= %d", answer_task.the_sum_of_the_values_rows[i]);
	}
	printf("\n");
	for (int i = 0; i < size_x; i++) {
		printf("=\t");
	}
	printf("\n");
	for (int i = 0; i < size_x; i++) {
		printf("%d\t", answer_task.the_sum_of_the_values_cols[i]);
	}
	printf("\n\nDifferent (max-min) = %d", answer_task.difference);
	for (int i = 0; i < size_y; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
	return 0;
}

