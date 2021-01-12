#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct polinom* Pozicija;
typedef struct polinom {
	int koeficijent;
	int eksponent;
	Pozicija next;
}Polinom;

int citanjeIzDatoteke(Pozicija pol, char *c);
int ispis(Pozicija ispisnik);
int zbrojPolinoma(Pozicija p1, Pozicija p2, Pozicija zbroj);
int umnozakPolinoma(Pozicija p1, Pozicija p2, Pozicija umnozak);
int main() {
	Polinom head1, head2, headZbroj, headUmnozak;
	head1.next = NULL;
	head2.next = NULL;
	headZbroj.next = NULL;
	headUmnozak.next = NULL;
	char imeDatoteke[30];
	//Citanje i ispisivanje prvog polinoma
	printf("Unesite ime datoteke za citanje prvog polinoma:\n");
	scanf("%s", imeDatoteke);
	citanjeIzDatoteke(&head1, imeDatoteke);
	ispis(head1.next);
	//Citanje i ispisivanje drugog polinoma
	printf("Unesite ime datoteke za citanje drugog polinoma:\n");
	scanf("%s", imeDatoteke);
	citanjeIzDatoteke(&head2, imeDatoteke);
	ispis(head2.next);
	zbrojPolinoma(head1.next, head2.next, &headZbroj);
	printf("Zbroj polinoma je:\n");
	ispis(headZbroj.next);
	umnozakPolinoma(head1.next, head2.next, &headUmnozak);
	printf("Umnozak polinoma je:\n");
	ispis(headUmnozak.next);
	return 0;
}
int citanjeIzDatoteke(Pozicija pol, char *datoteka) {
	Pozicija temp, polStart;
	FILE* fp;
	int koef, exp;
	polStart = pol;

	fp = fopen(datoteka, "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!");
		return -1;
	}

	while (!feof(fp)) {
		//stvaranje novog elementa polinoma
		fscanf(fp, "%d %d ", &koef, &exp);
		temp = (Pozicija)malloc(sizeof(Polinom));
		temp->koeficijent = koef;
		temp->eksponent = exp;
		//Sortiranje polinoma po eksponentima
		pol = polStart;
		while (pol->next != NULL && pol->next->eksponent < temp->eksponent) {
			pol = pol->next;
		}
		temp->next = pol->next;
		pol->next = temp;
	}

	fclose(fp);
	return 0;
}
int ispis(Pozicija ispisnik) {
	while (ispisnik != NULL) {
		printf("%dX^%d + ", ispisnik->koeficijent, ispisnik->eksponent);
		ispisnik = ispisnik->next;
	}
	printf("\n");
	return 0;
}
int zbrojPolinoma(Pozicija p1, Pozicija p2, Pozicija zbroj) {
	Pozicija q;
	while (p1 != NULL && p2 != NULL) {
		if (p1->eksponent == p2->eksponent) {
			q = (Pozicija)malloc(sizeof(Polinom));
			q->eksponent = p1->eksponent;
			q->koeficijent = p1->koeficijent + p2->koeficijent;
			while (zbroj->next != NULL) {
				zbroj = zbroj->next;
			}
			q->next = zbroj->next;
			zbroj->next = q;

			p1 = p1->next;
			p2 = p2->next;
		}
		else if (p1->eksponent < p2->eksponent) {
			q = (Pozicija)malloc(sizeof(Polinom));
			q->eksponent = p1->eksponent;
			q->koeficijent = p1->koeficijent;
			while (zbroj->next != NULL) {
				zbroj = zbroj->next;
			}
			q->next = zbroj->next;
			zbroj->next = q;

			p1 = p1->next;
		}
		else {
			q = (Pozicija)malloc(sizeof(Polinom));
			q->eksponent = p2->eksponent;
			q->koeficijent = p2->koeficijent;
			while (zbroj->next != NULL) {
				zbroj = zbroj->next;
			}
			q->next = zbroj->next;
			zbroj->next = q;

			p2 = p2->next;
		}
	}
	if (p2 != NULL) {
		while (p2 != NULL) {
			q = (Pozicija)malloc(sizeof(Polinom));
			q->eksponent = p2->eksponent;
			q->koeficijent = p2->koeficijent;
			while (zbroj->next != NULL && zbroj->next->eksponent < p2->eksponent) {
				zbroj = zbroj->next;
			}
			q->next = zbroj->next;
			zbroj->next = q;

			p2 = p2->next;
		}
	}
	else {
		while (p1 != NULL) {
			q = (Pozicija)malloc(sizeof(Polinom));
			q->eksponent = p1->eksponent;
			q->koeficijent = p1->koeficijent;
			while (zbroj->next != NULL && zbroj->next->eksponent < p1->eksponent) {
				zbroj = zbroj->next;
			}
			q->next = zbroj->next;
			zbroj->next = q;

			p1 = p1->next;
		}
	}
	return 0;

}
int umnozakPolinoma(Pozicija p1, Pozicija p2, Pozicija umnozak) {
	Pozicija q, p2Start;
	p2Start = p2;
	while (p1 != NULL) {
		p2 = p2Start;
		while (p2 != NULL) {
			q = (Pozicija)malloc(sizeof(Polinom));
			q->eksponent = p1->eksponent + p2->eksponent;
			q->koeficijent = p1->koeficijent * p2->koeficijent;
			while (umnozak ->next != NULL) {
				umnozak = umnozak->next;
			}
			q->next = umnozak->next;
			umnozak->next = q;

			p2 = p2->next;
		}
		p1 = p1->next;
	}
	return 0;
}