#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "Rus");
	struct student
	{
		char famil[20];
		char name[20], facult[20];
		char Nomzach[5];
	} stud[3];

	int full = -1;
	int  part[4] = { -1 , -1, -1, -1};
	int ipart = 0;

	int i;
	int call = 0;
	int coincidences = 0;
	struct student find;
	char search[20];

	for (i = 0; i < 3; i++)
	{
		printf("Введите фамилию студента\n"); scanf("%20s", stud[i].famil);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите имя студента %s\n", stud[i].famil); scanf("%20s", stud[i].name);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите название факультета студента %s %s\n", stud[i].famil, stud[i].name); scanf("%20s", stud[i].facult);
	}
	for (i = 0; i < 3; i++)
	{
		printf("Введите номер зачётной книжки студента %s %s\n", stud[i].famil, stud[i].name); scanf("%5s", stud[i].Nomzach);
	}

	//printf("Ввдите данные для поиска:\n");

	//printf("Введите фамилию студента\n"); scanf("%20s", find.famil);
	//printf("Введите имя студента %s\n", find.famil); scanf("%20s", find.name);
	//printf("Введите название факультета студента %s %s\n", find.famil, find.name); scanf("%20s", find.facult);
	//printf("Введите номер зачётной книжки студента %s %s\n", find.famil, find.name); scanf("%d", &find.Nomzach);

	printf("Поиск: \n"); scanf("%20s", &search);

	for (i = 0; i < 3; i++)
	{
		if (!(strcmp(search, stud[i].name) && strcmp(search, stud[i].famil) && strcmp(search, stud[i].facult) && strcmp(search, stud[i].Nomzach)) ) {
			printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %s \n", stud[i].famil, stud[i].name,
			stud[i].facult, stud[i].Nomzach);
			coincidences++;
		}

		//if (strcmp(search, stud[i].famil) == 0) {
		//	coincidences += 1;
		//}
		//if (strcmp(search, stud[i].facult) == 0) {
		//	coincidences += 1;
		//}
		//if (search == stud[i].Nomzach) {
		//	coincidences += 1;
		//}

		//if (coincidences > 0) {
		//	part[ipart] = i;
		//	ipart++;
		//	coincidences = 0;
		//}
		//else {
		//	continue;
		//}
	}
	//if (full != -1) {
	//	printf("Найдена запись: \n");
	//	printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n", stud[full].famil, stud[full].name,
	//		stud[full].facult, stud[full].Nomzach);
	//}
	if (coincidences == 0) {
			printf("Ничего не найдено\n");
	}
	return 0;
}