/*Prethodnom zadatku dodati funkcije:
a) dinamički dodaje novi element iza određenog elementa,
b) dinamički dodaje novi element ispred određenog elementa,
c) sortira listu po prezimenima osoba,
d) upisuje listu u datoteku,
e) čita listu iz datoteke*/

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
int unosIza(char* tempPrez, Pozicija unosnik, Pozicija clanListe);
int unosIspred(char* tempPrez, Pozicija unosnik, Pozicija clanListe);
int sortiraj(Pozicija clanListe);
int upisUDatoteku(Pozicija clanListe);
int citajIzDatoteke();
int main() {
	Osoba head, x;
	head.next = NULL;
	char prezimeZaSve[20];
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
	scanf(" %[^\n]", prezimeZaSve);
	traziPrezime(&prezimeZaSve, head.next);
	printf("Unesite prezime koje zelite izbrisati:\n");
	scanf(" %[^\n]", &prezimeZaSve);
	brisi(&prezimeZaSve, &head);
	ispis(head.next);
	printf("Unesite prezime osobe iza koje cete dodati novog clana:\n");
	scanf(" %[^\n]", &prezimeZaSve);
	x = inicijalizacija();
	unosIza(&prezimeZaSve, &x, &head);
	ispis(head.next);
	printf("Unesite prezime osobe ispred koje cete dodati novog clana:\n");
	scanf(" %[^\n]", &prezimeZaSve);
	x = inicijalizacija();
	unosIspred(&prezimeZaSve, &x, &head);
	ispis(head.next);
	printf("Sortirana lista:\n");
	sortiraj(&head);
	ispis(head.next);
	upisUDatoteku(head.next);
	citajIzDatoteke();
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
	while (prev->next != NULL && strcmp(prev->next->prezime, tempPrez) != 0){
		prev = prev->next;
		clanListe = clanListe->next;
	}
	prev->next = clanListe->next;
	free(clanListe);
	return 0;
}
int unosIza(char* tempPrez, Pozicija unosnik, Pozicija clanListe) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Osoba));
	strcpy(q->ime, unosnik->ime);
	strcpy(q->prezime, unosnik->prezime);
	q->godRodenja = unosnik->godRodenja;
	while (clanListe != NULL) {
		if (strcmp(clanListe->prezime, tempPrez) == 0) {
			q->next = clanListe->next;
			clanListe->next = q;
		}
		clanListe = clanListe->next;
	}
	return 0;
}
int unosIspred(char* tempPrez, Pozicija unosnik, Pozicija clanListe) {
	Pozicija q, prev;
	q = (Pozicija)malloc(sizeof(Osoba));
	strcpy(q->ime, unosnik->ime);
	strcpy(q->prezime, unosnik->prezime);
	q->godRodenja = unosnik->godRodenja;
	prev = clanListe;
	clanListe = clanListe->next;
	while (clanListe != NULL) {
		if (strcmp(clanListe->prezime, tempPrez) == 0) {
			prev->next = q;
			q->next = clanListe;
		}
		prev = clanListe;
		clanListe = clanListe->next;
	}
	return 0;
}
int sortiraj(Pozicija clanListe) {
	Pozicija q, qPrev, temp, end;
	end = NULL;
	while (clanListe->next != end) {
		qPrev = clanListe;
		q = clanListe->next;
		while (q->next != end) {
			if (strcmp(q->prezime, q->next->prezime) > 0) {
				temp = q->next;
				qPrev->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}
			else if (strcmp(q->ime, q->next->ime) > 0) {
				temp = q->next;
				qPrev->next = temp;
				q->next = temp->next;
				temp->next = q;

				q = temp;
			}
			qPrev = q;
			q = q->next;
		}
		end = q;
	}
	
	return 0;
}
int upisUDatoteku(Pozicija clanListe) {
	FILE* fp = fopen("Osobe.txt","w");
	while (clanListe != NULL) {
		fprintf(fp, "%s\t%s\t%d\n", clanListe->ime, clanListe->prezime, clanListe->godRodenja);
		clanListe = clanListe->next;
	}
	fclose(fp);
	printf("Podatci upisani u datoteku.\n");
	return 0;
}
int citajIzDatoteke() {
	Pozicija q = NULL;
	int br = 0, i;
	q = (Pozicija)malloc(sizeof(Osoba));
	FILE* fp = fopen("Osobe.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke.");
		return 1;
	}
	while (!feof(fp)) {
		if (fgetc(fp) == '\n') {
			br++;
		}
	}
	fseek(fp, 0, SEEK_SET);
	printf("\nCitanje iz datoteke:\n");
	for (i = 0; i < br; i++) {
		fscanf(fp, "%s %s %d\n", q->ime, q->prezime, &q->godRodenja);
		printf("%s\t%s\t%d\n", q->ime, q->prezime, q->godRodenja);
	}
	fclose(fp);
	return 0;
}