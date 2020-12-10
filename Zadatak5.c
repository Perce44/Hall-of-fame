#include<stdio.h>
#include<stdlib.h>
typedef struct skup* Pozicija;
typedef struct skup {
	int broj;
	Pozicija next;
}Skup;
int definiranjeSkupa(Pozicija s, int noviClan);
int ispisSkupa(Pozicija s);
int stvaranjePresjeka(Pozicija s1, Pozicija s2, Pozicija presjek);
int stvaranjeUnije(Pozicija s1, Pozicija s2, Pozicija unija);
int main() {
	Skup head1, head2, headPresjek, headUnija;
	head1.next = NULL;
	head2.next = NULL;
	headPresjek.next = NULL;
	headUnija.next = NULL;
	//Prvi skup
	definiranjeSkupa(&head1, 3);
	definiranjeSkupa(&head1, 15);
	definiranjeSkupa(&head1, 2);
	definiranjeSkupa(&head1, 6);
	definiranjeSkupa(&head1, 17);
	ispisSkupa(head1.next);
	//Drugi skup
	definiranjeSkupa(&head2, 2);
	definiranjeSkupa(&head2, 1);
	definiranjeSkupa(&head2, 13);
	definiranjeSkupa(&head2, 17);
	definiranjeSkupa(&head2, 28);
	definiranjeSkupa(&head2, 173);
	ispisSkupa(head2.next);
	//Presjek
	printf("\nPresjek:\t");
	stvaranjePresjeka(head1.next, head2.next, &headPresjek);
	ispisSkupa(headPresjek.next);
	//Unija
	printf("\nUnija:\t");
	stvaranjeUnije(head1.next, head2.next, &headUnija);
	ispisSkupa(headUnija.next);


	return 0;
}
int definiranjeSkupa(Pozicija s, int noviClan) {
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Skup));
	q->broj = noviClan;

	while (s->next != NULL && s->next->broj < q->broj) {
		s = s->next;
	}
	q->next = s->next;
	s->next = q;

	return 0;
}
int ispisSkupa(Pozicija s) {
	while (s != NULL) {
		printf("%d\t", s->broj);
		s = s->next;
	}
	printf("\n");

	return 0;
}
int stvaranjePresjeka(Pozicija s1, Pozicija s2, Pozicija presjek) {
	Pozicija q;
	while (s1 != NULL && s2 != NULL) {
		if (s1->broj < s2->broj) {
			s1 = s1->next;
		}
		else if (s1->broj > s2->broj) {
			s2 = s2->next;
		}
		else if (s1->broj == s2->broj) {
			q = (Pozicija)malloc(sizeof(Skup));
			q->broj = s1->broj;
			while (presjek->next != NULL) {
				presjek = presjek->next;
			}
			q->next = presjek->next;
			presjek->next = q;

			s1 = s1->next;
			s2 = s2->next;
		}
		
	}

	return 0;
}

int stvaranjeUnije(Pozicija s1, Pozicija s2, Pozicija unija) {
	Pozicija q, s2Start, unijaStart;
	s2Start = s2;
	unijaStart = unija;
	while (s1 != NULL && s2 != NULL) {
		if (s1->broj < s2->broj) {
			q = (Pozicija)malloc(sizeof(Skup));
			q->broj = s1->broj;
			while (unija->next != NULL) {
				unija = unija->next;
			}
			q->next = unija->next;
			unija->next = q;

			s1 = s1->next;
		}
		else if (s1->broj > s2->broj) {
			s2 = s2->next;
		}
		else {
			s1 = s1->next;
		}
	}
	s2 = s2Start;
	unija = unijaStart;
	while (s2 != NULL) {
		q = (Pozicija)malloc(sizeof(Skup));
		q->broj = s2->broj;
		while (unija->next != NULL && unija->next->broj < s2->broj) {
			unija = unija->next;
		}
		q->next = unija->next;
		unija->next = q;

		s2 = s2->next;
	}
	return 0;
}
