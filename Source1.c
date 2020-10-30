/*Definirati strukturu osoba (ime, prezime, godina rođenja) i
napisati program koji:
a) dinamički dodaje novi element na početak liste,
b) ispisuje listu,
c) dinamički dodaje novi element na kraj liste,
d) pronalazi element u listi (po prezimenu),
e) briše određeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable.*/


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct osoba;
typedef struct osoba* Pozicija;
typedef struct osoba {
	char ime[20];
	char prezime[20];
	int godRodenja;
	Pozicija next;
}Osoba;

Osoba NovaOsoba(char* tempIme, char* tempPrez, int tempGod);
void unosPocetak(Pozicija p,Pozicija r);
void ispis(Pozicija p);
void unosKraj(Pozicija p, Pozicija r);
void pronalazak(Pozicija p, char* uspprez);
Pozicija traziispred(char* uspprez, Pozicija p);
void brisanje(Pozicija p, char* uspprez);
int main() {
	struct osoba Head;
	Head.next = NULL;
	char mIme[20], mPrezime[20];
	int mGod;
	char usporedno[20];
	Osoba x;
	printf("Unesite ime osobe:\n");
	scanf("%s",mIme);
	printf("Unesite prezime:\n");
	scanf(" %s",mPrezime);
	printf("Unesite godinu rodenja:\n");
	scanf(" %d", &mGod);
	x = NovaOsoba(mIme, mPrezime, mGod);
	unosPocetak(&x, &Head);
	ispis(Head.next);
	unosKraj(&x, &Head);
	ispis(&x, &Head);
	printf("Unesite prezime za pretrazivanje:\n");
	scanf(" %[^\n]", &usporedno);
	pronalazak(Head.next, &usporedno);
	brisanje(&Head, &usporedno);
	printf("\n");
	ispis(&x, &Head);
	getchar();
	getchar();
	return 0;
}
Osoba NovaOsoba(char* tempIme, char* tempPrez, int tempGod) {
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Osoba));
	strcpy(q->ime, tempIme);
	strcpy(q->prezime, tempPrez);
	q->godRodenja = tempGod;
	q->next = NULL;
}
void unosPocetak(Pozicija p, Pozicija r) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct osoba));
	strcpy(q->ime, p->ime);
	strcpy(q->prezime, p->prezime);
	q->godRodenja = p->godRodenja;
	q->next = r->next;
	r->next = q;
}
void ispis(Pozicija p) {
	while (p != NULL) {
		printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godRodenja);
		p = p->next;
	}
}
void unosKraj(Pozicija p, Pozicija r) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(struct osoba));
	strcpy(q->ime, p->ime);
	strcpy(q->prezime, p->prezime);
	q->godRodenja = p->godRodenja;
	while (p->next != NULL) {
		p = p->next;
	}

	q->next = r->next;
	r->next = q;
}
void pronalazak(Pozicija p, char* uspprez) {
	int br = 0;
	while (p!= NULL) {
		if (strcmp(p->prezime, uspprez) == 0) {
			br = 1;
		}
		p = p->next;
	}
	if (br == 1) {
		printf("Osoba pronadena.");
	}
	else {
		printf("Nema trazene osobe.");
	}
	
}
Pozicija traziispred(char* uspprez, Pozicija p)
{
	Pozicija prev = p;
	p = p->next;
	while (p != NULL && strcmp(p->prezime, uspprez))
	{
		prev = p;
		p = p->next;
	}
	if (p == NULL)
	{
		printf("Element ne postoji u listi. ");
		return NULL;
	}
	return prev;
}
void brisanje(Pozicija p, char* uspprez) {
	Pozicija prev;
	prev = traziispred(uspprez, p);
	if (prev != NULL) {
		p = prev->next;
		prev->next = p->next;
		free(p);
	}
}