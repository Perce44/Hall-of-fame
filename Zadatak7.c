#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stog* Pozicija;
typedef struct stog{
    float broj;
    Pozicija next;
} Clan;

int DodajNaStog(Pozicija P, float broj);
float SkiniSaStoga(Pozicija P);
int IzracunajPostfix(Pozicija P, char* imeDatoteke);
int Operacija(Pozicija P, char operator);
int IspisIzDatoteke(char* datoteka);
int main(){
    char imeDatoteke[256];
    Pozicija Head = (Pozicija)malloc(sizeof(Clan));

    if (Head == NULL) {
        return -1;
    }

    Head->next = NULL;

    printf("Unesi ime datoteke s postfix izrazom:\n");
    scanf("%s", imeDatoteke);
    IspisIzDatoteke(imeDatoteke);
    IzracunajPostfix(Head, imeDatoteke);

    if (Head->next == NULL) {
        return -1;
    }
    printf("%f\n", Head->next->broj);

    return 0;
}
int DodajNaStog(Pozicija P, float broj){
    Pozicija novi = (Pozicija)malloc(sizeof(Clan));

    if (novi == NULL) {
        return -1;
    }

    novi->next = P->next;
    P->next = novi;
    novi->broj = broj;

    return 0;
}
float SkiniSaStoga(Pozicija P){
    Pozicija temp;
    float broj;
    broj = P->next->broj;
    temp = P->next;
    P->next = P->next->next;

    free(temp);
    return broj;
}
int IzracunajPostfix(Pozicija P, char* ime){
    FILE* fp;
    char buffer[256];
    char* pBuffer = buffer;
    float operand1 = 0;
    float operand2 = 0;

    fp = fopen(ime, "r");

    if (fp == NULL)
        return -1;

    fgets(buffer, 256, fp);

    fclose(fp);

    while (strlen(pBuffer) > 0){
        char operator= 0;
        int k = 0;
        float broj = 0;
        if (sscanf(pBuffer, " %f%n", &broj, &k) == 1){
            DodajNaStog(P, broj);
            pBuffer += k;
        }
        else{
            sscanf(pBuffer, " %c%n", &operator, &k);
            Operacija(P, operator);
            pBuffer += k;
        }
    }

    return 0;
}
int Operacija(Pozicija P, char operator){
    float operand1 = 0;
    float operand2 = 0;

    switch (operator){
    case ('*'):
        operand2 = SkiniSaStoga(P);
        operand1 = SkiniSaStoga(P);
        DodajNaStog(P, operand1 * operand2);
        break;
    case ('/'):
        operand1 = SkiniSaStoga(P);
        operand2 = SkiniSaStoga(P);
        DodajNaStog(P, operand1 / operand2);
        break;
    case ('+'):
        operand1 = SkiniSaStoga(P);
        operand2 = SkiniSaStoga(P);
        DodajNaStog(P, operand1 + operand2);
        break;
    case ('-'):
        operand1 = SkiniSaStoga(P);
        operand2 = SkiniSaStoga(P);
        DodajNaStog(P, operand1 - operand2);
        break;
    default:
        printf("Operacija nije dozvoljena.\n");
        break;
    }
    

    return 0;
}
int IspisIzDatoteke(char* datoteka) {
    char sadrzajDatoteke[256];
    FILE* fp;

    fp = fopen(datoteka, "r");

    fgets(sadrzajDatoteke, 256, fp);
    printf("Sadrzaj datoteke:\n%s\n", sadrzajDatoteke);

    fclose(fp);
    return 0;
}
