#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct stablo* Pozicija;
typedef struct stablo
{
    int broj;
    Pozicija lijevi;
    Pozicija desni;
} Stablo;

Pozicija Unos(Pozicija root, int br);
Pozicija Trazi(const Pozicija root, int br);
int NoviBroj();
Pozicija Alokacija(int br);
int Ispis(const Pozicija root, int razmak);
Pozicija Najmanji(Pozicija cvor);
Pozicija Brisi(const Pozicija root, Pozicija element);
int BrisiSve(const Pozicija root);
int main(){
    int izbor = 0;
    Pozicija root = NULL;

    do{
        printf("Odaberite operaciju:\n1.) Unesi element\n2.) Izbrisi element\n3.) Ispisi stablo\n0.) Zatvori program\n");
        scanf("%d", &izbor);

        switch (izbor){
        case 1:
            root = Unos(root, NoviBroj());
            break;
        case 2:
            root = Brisi(root, Trazi(root, NoviBroj()));
            break;
        case 3:
            Ispis(root, 10);
            break;
        case 0:
            BrisiSve(root);
            break;
        }
    } while (root != NULL);

    return 0;
}
Pozicija Unos(Pozicija root, int br){
    if (root == NULL) {
        root = Alokacija(br);
    }
    else if (br < root->broj) {
        root->lijevi = Unos(root->lijevi, br);
    }
    else if (br > root->broj) {
        root->desni = Unos(root->desni, br);
    }
    return root;
}
int NoviBroj(){
    int n;

    printf("Unesite broj: \n");
    scanf("%d", &n);

    return n;
}
Pozicija Alokacija(int br){
    Pozicija q;
    q = malloc(sizeof(Stablo));

    q->broj = br;
    q->lijevi = NULL;
    q->desni = NULL;

    return q;
}
Pozicija Trazi(const Pozicija root, int br){
    Pozicija cvor = (Pozicija)root;
    if (cvor == NULL) {
        return NULL;
    }
    else if (br < cvor->broj) {
        cvor = Trazi(cvor->lijevi, br);
    }
    else if (br > cvor->broj) {
        cvor = Trazi(cvor->desni, br);
    }
    return cvor;
}
int Ispis(const Pozicija root, int razmak){
    Pozicija cvor = (Pozicija)root;
    int i = 0;

    if (cvor == NULL) {
        return 0;
    }

    Ispis(cvor->desni, razmak + 10);
    printf("\n");

    for (i = 10; i < razmak + 10; i++) {
        printf(" ");
    }

    printf("%d\n", cvor->broj);
    Ispis(cvor->lijevi, razmak + 10);
}
Pozicija Najmanji(Pozicija cvor){
    if (!cvor) {
        return NULL;
    }
    else if (!cvor->lijevi) {
        return cvor;
    }
    return Najmanji(cvor->lijevi);
}
Pozicija Brisi(const Pozicija root, Pozicija Element){
    Pozicija cvor = (Pozicija)root;
    Pozicija temp = NULL;

    if (!cvor) {
        return NULL;
    }
    else if (Element->broj < cvor->broj) {
        cvor->lijevi = Brisi(cvor->lijevi, Element);
    }
    else if (Element->broj > cvor->broj) {
        cvor->desni = Brisi(cvor->desni, Element);
    }
    else if (cvor->lijevi && cvor->desni){
        temp = Najmanji(cvor->desni);
        cvor->broj = temp->broj;
        cvor->desni = Brisi(cvor->desni, cvor);
    }
    else{
        temp = cvor;
        if (!cvor->lijevi) {
            cvor = cvor->desni;
        }
        else {
            cvor = cvor->lijevi;
        }
        free(temp);
    }
    return cvor;
}
int BrisiSve(const Pozicija q) {
    if (q != NULL) {
        BrisiSve(q->lijevi);
        BrisiSve(q->desni);
        BrisiSve(q);
    }
    free(q);

    return 0;
}