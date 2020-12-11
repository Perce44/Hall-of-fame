#include<stdio.h>
#include <stdlib.h>
typedef struct  lista* Pozicija;
typedef struct lista {
	int broj;
	Pozicija next;
}Lista;
int stogDodaj(Pozicija clanListe, int unosnik);
int ispis(Pozicija clanListe);
int stogSkini(Pozicija clanListe);
int redDodaj(Pozicija clanListe, int unosnik);
int redSkini(Pozicija clanListe);
int nasumicniBroj(int a, int b);
int main() {
	Lista heads;
	Lista headr;
	heads.next = NULL;
	headr.next = NULL;
	int min, max;
	min = 10;
	max = 100;
	stogDodaj(&heads, nasumicniBroj(min, max));
	stogDodaj(&heads, nasumicniBroj(min, max));
	stogDodaj(&heads, nasumicniBroj(min, max));
	stogDodaj(&heads, nasumicniBroj(min, max));
	ispis(heads.next);


	stogSkini(&heads);
	ispis(heads.next);

	redDodaj(&headr, nasumicniBroj(min,max));
	redDodaj(&headr, nasumicniBroj(min, max));
	redDodaj(&headr, nasumicniBroj(min, max));
	redDodaj(&headr, nasumicniBroj(min, max));
	redDodaj(&headr, nasumicniBroj(min, max));
	ispis(headr.next);

	redSkini(&headr);
	ispis(headr.next);

	getchar();
	return 0;
}
int stogDodaj(Pozicija clanListe, int unosnik) {
	Pozicija temp;
	temp = (Pozicija)malloc(sizeof(Lista));
	temp->broj = unosnik;
	temp->next = clanListe->next;
	clanListe->next = temp;
	return 0;
}
int ispis(Pozicija clanListe) {
	while (clanListe != NULL) {
		printf("%d\t", clanListe->broj);
		clanListe = clanListe->next;
	}
	printf("\n");
	return 0;
}
int stogSkini(Pozicija clanListe) {
	printf("Skinut je %d sa stoga!\n", clanListe->next->broj);
	brisi(clanListe);

	return 0;
}
int brisi(Pozicija clanListe) {
	Pozicija prev;

	prev = clanListe;
	clanListe = clanListe->next;

	prev->next = clanListe->next;
	free(clanListe);

	return 0;
}
int redDodaj(Pozicija clanListe, int unosnik) {
	Pozicija q;

	q = (Pozicija)malloc(sizeof(Lista));
	q->broj = unosnik;

	while (clanListe->next != NULL)
		clanListe = clanListe->next;

	q->next = clanListe->next;
	clanListe->next = q;
	return 0;
}
int redSkini(Pozicija clanListe) {
	printf("Skinut je %d s reda!\n", clanListe->next->broj);
	brisi(clanListe);

	return 0;
}
int nasumicniBroj(int a, int b) {
	return rand() % (b - a + 1) + a;
}