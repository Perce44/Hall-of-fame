/*Definirati strukturu osoba (ime, prezime, godina rođenja) i
napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct osoba;
typedef struct osoba* Pozicija;
typedef struct osoba {
	char ime[20];
	char prezime[20];
	int godRodenja;
	Pozicija next;
}Osoba;
int unos(Pozicija unosnik, Pozicija clanListe);
Osoba inicijalizacija();
int ispis(Pozicija clanListe);
int unosNaKraj(Pozicija unosnik, Pozicija clanListe);
int traziPrezime(char* tempPrez, Pozicija clanListe);
int brisi(char* tempPrez, Pozicija clanListe);
int main() {
	Osoba head, x;
	head.next = NULL;
	char prezimeZaUsporedbu, prezimeZaBrisanje;
	x = inicijalizacija();
	unos(&x, &head);
	x = inicijalizacija();
	unos(&x, &head);
	x = inicijalizacija();
	unos(&x, &head);
	x = inicijalizacija();
	unosNaKraj(&x, &head);
	ispis(head.next);
	printf("Unesite prezime koje zelite traziti:\n");
	scanf(" %[^\n]",&prezimeZaUsporedbu);
	traziPrezime(&prezimeZaUsporedbu, head.next);
	printf("Unesite prezime koje zelite izbrisati:\n");
	scanf(" %[^\n]", &prezimeZaBrisanje);
	brisi(&prezimeZaBrisanje, &head);
	ispis(head.next);
	return 0;
}
Osoba inicijalizacija() {
	Osoba unosnik;
	printf("Unesite ime osobe:\n");
	scanf(" %[^\n]", unosnik.ime);
	printf("Unesite prezime osobe:\n");
	scanf(" %[^\n]", unosnik.prezime);
	printf("Unesite godinu rodenja osobe:\n");
	scanf("%d", &unosnik.godRodenja);
	unosnik.next = NULL;
	return unosnik;
}
int unos(Pozicija unosnik, Pozicija clanListe) {
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Osoba));
	strcpy(q->ime, unosnik->ime);
	strcpy(q->prezime, unosnik->prezime);
	q->godRodenja = unosnik->godRodenja;
	q->next = clanListe->next;
	clanListe->next = q;
	return 0;
}
int ispis(Pozicija clanListe) {
	while (clanListe != NULL) {
		printf("%s\t%s\t%d\n", clanListe->ime, clanListe->prezime, clanListe->godRodenja);
		clanListe = clanListe->next;
	}
	return 0;
}
int unosNaKraj(Pozicija unosnik, Pozicija clanListe) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	strcpy(q->ime, unosnik->ime);
	strcpy(q->prezime, unosnik->prezime);
	q->godRodenja = unosnik->godRodenja;
	while (clanListe->next != NULL)
		clanListe = clanListe->next;
	q->next = clanListe->next;
	clanListe->next = q;
	return 0;
}
int traziPrezime(char* tempPrez, Pozicija clanListe) {
	while (clanListe != NULL) {
		if (strcmp(clanListe->prezime, tempPrez) == 0) {
			printf("\n%s\t%s\t%d\n", clanListe->ime, clanListe->prezime, clanListe->godRodenja);
		}
		clanListe = clanListe->next;
	}
	return 0;
}
int brisi(char* tempPrez, Pozicija clanListe) {
	Pozicija prev;
	prev = clanListe;
	clanListe = clanListe->next;
	while (clanListe != NULL) {
		if (strcmp(clanListe->prezime, tempPrez) == 0) {
			prev->next = clanListe->next;
			free(clanListe);
		}
		else {
			prev= clanListe;
			clanListe = clanListe->next;
		}
	}
	return 0;
}