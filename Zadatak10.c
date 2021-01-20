#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cvor* Pozicija;
typedef struct cvor{
    char element[20];
    Pozicija lijevi;
    Pozicija desni;
} Cvor;

typedef struct stog* Veza;
typedef struct stog{
    char element[20];
    Veza next;
} Stog;

int PostfixUStog(Veza P, char* buffer);
int CitanjeIzDatotoeke(Veza P, char* imeDatoteke);
int PrepoznavanjeOperatora(char element);
int DodavanjeNaStog(Veza P, char* znak);
char* SkidanjeSaStoga(Veza P);
Pozicija IzradaStabla(Veza P, Pozicija Q);
Pozicija Alokacija();
int Infix(Pozicija Q);
int main(void){
    char naziv[20];
    Veza head = malloc(sizeof(Stog));
    Pozicija root = Alokacija();
    head->next = NULL;

    printf("Unesite naziv datoteke: ");
    scanf(" %s", naziv);

    CitanjeIzDatoteke(head, naziv);

    root = IzradaStabla(head, root);

    Infix(root);

    return 0;
}
int CitanjeIzDatoteke(Veza P, char* imeDatoteke){
    FILE* fp;
    char buffer[20] = { 0 };
    fp = fopen(imeDatoteke, "r");

    if (fp == NULL) {
        printf("Neuspjesno otvaranje datoteke!!!\n");
        return -1;
    }

    fgets(buffer, 20, fp);
    PostfixUStog(P, buffer);

    return 0;
}
int PostfixUStog(Veza P, char* buffer){
    int k = 0;
    char znak[20] = { 0 };

    while (sscanf(buffer, " %s %n", znak, &k) == 1){
        DodavanjeNaStog(P, znak);
        buffer += k;
        k = 0;
    }

    return 0;
}
int PrepoznavanjeOperatora(char element){
    if (element == '+' || element == '-' || element == '*' || element == '/') {
        return 1;
    }
    else {
        return 0;
    }
}
int DodavanjeNaStog(Veza P, char* znak){
    Veza novi = (Veza)malloc(sizeof(Stog));

    if (novi == NULL) {
        return -1;
    }

    novi->next = P->next;
    P->next = novi;
    strcpy(novi->element, znak);

    return 0;
}
char* SkidanjeSaStoga(Veza P){
    char* tempStr = malloc(sizeof(char));

    if (P->next == NULL) {
        return NULL;
    }

    Veza temp = P->next;
    strcpy(tempStr, temp->element);
    P->next = P->next->next;
    free(temp);

    return tempStr;
}
Pozicija IzradaStabla(Veza P, Pozicija Q){
    char* element = SkidanjeSaStoga(P);

    Q = Alokacija();

    if (element == NULL) {
        return NULL;
    }

    strcpy(Q->element, element);

    if (PrepoznavanjeOperatora(Q->element[0]) != 0) {
        Q->desni = IzradaStabla(P, Q->desni);
        Q->lijevi = IzradaStabla(P, Q->lijevi);
    }

    return Q;
}
Pozicija Alokacija(){
    Pozicija Novi = malloc(sizeof(Cvor));
    Novi->lijevi = NULL;
    Novi->desni = NULL;

    return Novi;
}
int Infix(Pozicija Q){
    FILE* fp;
    fp = fopen("Infix.txt","w");

    if (fp == NULL) {
        printf("Neuspjesno otvaranje datoteke!!!\n");
        return -1;
    }
    if (Q == NULL) {
        return 0;
    }
    printf("(");
    fprintf(fp, "(");

    Infix(Q->lijevi);

    printf("%s", Q->element);
    fprintf(fp, "%s",(char *) Q->element);

    Infix(Q->desni);

    printf(")");
    fprintf(fp, ")");

    fclose(fp);

    return 0;
}