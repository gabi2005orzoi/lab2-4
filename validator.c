#include "validator.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int val_tip(char* tip){
    /**
     *verifica daca tipul este valid
     *param tip: tipul ofertei
     *return: 1 daca este valid, 0 altfel
     */
    if (strcmp(tip, "munte") == 0 || strcmp(tip, "mare") == 0 || strcmp(tip, "city break") == 0)
        return 1;
    return 0;
}

int val_destinatie(char* destinatie){
    /**
     *verifica daca o destinatie este valida
     *param tip: destinatia ofertei
     *return: 1 daca este valid, 0 altfel
     */
    if (strcmp(destinatie, "") == 0)
        return 0;
    int x=strlen(destinatie);
    for (int i = 0; i < x; i++){
        if (destinatie[i] <'a' || destinatie[i] > 'z')
            return 0;
    }
    return 1;
}

int este_an_bisect(char an){
    /**
     *Verifica daca un an este bisect
     *
     *param an: un an
     *return 1 daca anul este bisect, 0 altfel
     */
    if((an%4 == 0 && an%100!=0) || (an%400 == 0))
        return 1;
    return 0;
}

int este_nr(char *s){
    /**
     *Verifica daca un sir este un numar
     *
     *param s: sirul
     *return: 1 daca sirul este un numar, 0 altfel
     */
    int x=strlen(s);
    for (int i = 0; i < x; i++){
        if (s[i] < '0' || s[i] > '9')
            return 0;
    }
    return 1;
}

int val_data(char* data){
    /**
     *Verifica daca data este valida
     *
     *param data: data ofertei
     *return: 1 daca data este valida, 0 altfel
     */
    int zi, luna, an;
    int zile_luni[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    char copie[11];
    strcpy(copie, data);
    char *p = strtok(copie, "/");
    if (p == NULL || !este_nr(p))
        return 0;
    zi = atoi(p);
    p=strtok(NULL, "/");
    if (p == NULL || !este_nr(p))
        return 0;
    luna = atoi(p);
    p=strtok(NULL, "/");
    if (p == NULL || !este_nr(p))
        return 0;
    an = atoi(p);
    if (an<2025 || an>2050) return 0;
    if (luna<1 || luna>12) return 0;
    if (luna == 2 && este_an_bisect(an))
        zile_luni[1]=29;
    if (zi<1 || zi>zile_luni[luna-1])
        return 0;
    return 1;
}

int val_pret(float pret){
    /**
     *Verifica daca pretul este valid
     *param: pret
     *return: 1 daca pretul este valid, 0 alfel
     */
    if (pret<0)
        return 0;
    return 1;
}