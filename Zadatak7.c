#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct stog* Pozicija;
typedef struct stog {
	double broj;
	Pozicija next;
}Stog;

int citanjeIzDatoteke(Pozicija p, char *datoteka);
int dodavanjeNaStog(Pozicija p, double unosnik);
int ispisIzDatoteke(char* datoteka);
double skidanjeSaStoga(Pozicija p);
int main() {
	char imeDatoteke[30];
	Stog head;

	head.next = NULL;

	printf("Unesite ime datoteke za citanje izraza:\n");
	scanf("%s", imeDatoteke);

	ispisIzDatoteke(imeDatoteke);
	citanjeIzDatoteke(&head, imeDatoteke);

	printf("Rezultat postfix izraza je:\n%f", head.next->broj);

	free(head.next);

	return 0;
}
int citanjeIzDatoteke(Pozicija p, char* datoteka) {
	FILE* fp;
	char znakIzDatoteke;
	double PrviOperand = 0, DrugiOperand = 0, rezultat = 0;

	fp = fopen(datoteka, "r");

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!!!\n"); 
		return -1;
	}

	while (!feof(fp)) {
		znakIzDatoteke = fgetc(fp);
		if (isdigit(znakIzDatoteke)) {
			dodavanjeNaStog(p, znakIzDatoteke);
		}
		else if (znakIzDatoteke == ' ') {
			znakIzDatoteke = fgetc(fp);
		}
		else {
			DrugiOperand = skidanjeSaStoga(p);
			PrviOperand = skidanjeSaStoga(p);
			if (znakIzDatoteke == '+') {
				rezultat = PrviOperand + DrugiOperand;
				dodavanjeNaStog(p, rezultat);
			}
			else if (znakIzDatoteke == '-') {
				rezultat = PrviOperand - DrugiOperand;
				dodavanjeNaStog(p, rezultat);
			}
			else if (znakIzDatoteke == '*') {
				rezultat = PrviOperand * DrugiOperand;
				dodavanjeNaStog(p, rezultat);
			}
			else if (znakIzDatoteke == '/') {
				rezultat = PrviOperand / DrugiOperand;
				dodavanjeNaStog(p, rezultat);
			}
			else {
				printf("Operacija nije dozvoljena.\n");
			}

		}
	}

	fclose(fp);
	return 0;
}
int dodavanjeNaStog(Pozicija p, double unosnik) {
	Pozicija q;

	q = (Pozicija)malloc(sizeof(Stog));

	q->broj = unosnik;
	q->next = p->next;
	p->next = q;

	return 0;
}
int ispisIzDatoteke(char* datoteka) {
	char sadrzajDatoteke[256];
	FILE* fp;

	fp = fopen(datoteka, "r");

	fgets(sadrzajDatoteke, 256, fp);
	printf("Sadrzaj datoteke:\n%s", sadrzajDatoteke);

	fclose(fp);
	return 0;
}
double skidanjeSaStoga(Pozicija p) {
	Pozicija temp;
	double skinutiBroj;

	temp = p->next;
	skinutiBroj = temp->broj;
	p->next = temp->next;
	free(temp);

	return skinutiBroj;
}
