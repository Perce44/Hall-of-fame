#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char ime[20];
	char prezime[20];
	float bodovi;
}studenti;


int main()
{
	int broj = 0, i, max = 100;
	studenti* Student;
	FILE* fp;
	fp = fopen("studenti.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!!!");
		return 0;
	}
	while (!feof(fp)) {
		if (fgetc(fp) == '\n') {
			broj++;
		}
	}
	printf("Broj redaka je %d.\n", broj);
	fseek(fp, 0, SEEK_SET);
	Student = (studenti*)malloc(broj * sizeof(studenti));
	for (i = 0; i < broj; i++) {
		fscanf(fp,"%s %s %f", Student[i].ime, Student[i].prezime, &Student[i].bodovi);
		Student[i].bodovi = Student[i].bodovi / (float)max * 100;
	}
	for (i = 0; i < broj; i++) {
		printf("%s %s %f\n", Student[i].ime, Student[i].prezime, Student[i].bodovi);
	}
	fclose(fp);
	return 0;
}
