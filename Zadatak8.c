
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct _Direktorij* Pozicija;
typedef struct _Direktorij {
	char* ime;
	Pozicija child;
	Pozicija sibling;
}Direktorij;
typedef struct _Cvor* Pokazivac;
typedef struct _Cvor {
	Pozicija clan;
	Pokazivac next;
	Pokazivac prev;
}Cvor;

int Ispis(Pokazivac, Pozicija, Pozicija);
int Md(Pozicija);
int Cd(Pozicija, Pokazivac);
int Dir(Pozicija);
int Push(Pokazivac, Pozicija);
Pozicija Pop(Pokazivac);
Pozicija Trazi(char*, Pozicija);
Pokazivac TraziZadnjeg(Pokazivac);
int main() {
	Pozicija root, temp;
	Pokazivac head;
	root = (Pozicija)malloc(sizeof(Direktorij));
	head = (Pokazivac)malloc(sizeof(Cvor));
	root->child = NULL;
	root->sibling = NULL;
	head->next = NULL;
	head->prev = NULL;
	root->ime = "C:";
	temp = root;
	int odabir;

	printf("Odaberite opciju\n");
	printf("1 - Stvaranje novog direktorija\n");
	printf("2 - Otvaranje direktorija\n");
	printf("3 - Zatvaranje direktorija\n");
	printf("4 - Popis direktorija\n");
	printf("5 - Izlaz\n");
	scanf("%d", &odabir);

	do {
		switch (odabir) {
			Ispis(head, root, temp);
			scanf("%d", &odabir);
		case 1: 
			Md(temp);
			break;
		case 2: 
			temp = Cd(temp, head);
			break;
		case 3: 
			temp = Pop(head);
			break;
		case 4: 
			Dir(temp);
			break;
		default:
			printf("Nepoznata naredba!!!\n");
			break;
		}
	} while (odabir == 1 || odabir == 2 || odabir == 3 || odabir == 4);

	return 0;
}
int Ispis(Pokazivac P, Pozicija root, Pozicija temp) {
	Pokazivac q;
	q = TraziZadnjeg(P);

	printf("\n");
	if (P->next == NULL) {
		printf("%s>", root->ime);
	}

	while (q->prev != NULL) {
		printf("%s>", q->clan->ime);
	}

	return 0;
}
Pokazivac TraziZadnjeg(Pokazivac P) {
	Pokazivac q;
	q = P->next;

	while (q->next != NULL) {
		q = q->next;
	}

	return q;
}
int Md(Pozicija P) {
	Pozicija q;
	q = (Pokazivac)malloc(sizeof(Cvor));

	if (q == NULL) {
		printf("Greska u alokaciji!");
		return -1;
	}

	if (P->child != NULL) {
		P = P->child;
		while (P->sibling != NULL) {
			P = P->sibling;
		}
		P->sibling = q;
	}
	else
		P->child = q;

	printf("Ime direktorija?\n");
	scanf("%s", q->ime);

	q->sibling = NULL;
	q->child = NULL;

	return 0;
}
Pozicija Trazi(char* ime, Pozicija P) {
	P = P->child;

	while (strcmp(ime, P->ime) != NULL && P->sibling != NULL) {
		P = P->sibling;
	}
	if (P->sibling == NULL) {
		if (strcmp(ime, P->sibling != NULL))
			return 0;
		else
			return P;
	}

	else return P;
}
int Cd(Pozicija temp, Pokazivac head) {
	Pozicija q;
	q = (Pokazivac)malloc(sizeof(Cvor));
	char* ime;
	ime = (char*)malloc(20 * sizeof(char));
	printf("Ime direktorija?\n");
	scanf("%s", ime);

	if (q->child == NULL) {
		printf("Nema direktorija\n");
		return temp;
	}
	q = Trazi(ime, temp);
	if (q == NULL) {
		printf("Nema direktorija\n");
		return temp;
	}
	Push(head, temp);

	return q;

}

int Dir(Pozicija temp) {
	if (temp->child == NULL) {
		printf("Nema podataka!\n");
	}
	temp = temp->child;

	printf(" %s\n", temp->ime);
	while (temp->sibling != NULL) {
		printf(" %s\n", temp->sibling->ime);
		temp = temp->sibling;
	}
	return 0;
}

int Push(Pokazivac head, Pozicija P) {
	Pokazivac q = (Pokazivac)malloc(sizeof(Cvor));
	q->next = head->next;
	q->prev = head;
	if (head->next != NULL) {
		head = q;
	}
	head->next = q;
	q->clan = P;
	return 0;
}

Pozicija Pop(Pokazivac head) {
	Pokazivac q;
	Pozicija p;
	q = (Pokazivac)malloc(sizeof(Cvor));
	if (q == NULL) {
		printf("Greska");
		return -1;
	}
	q = head->next;
	p = q->clan;
	head->next = head->next->next;
	free(q);

	return p;
}