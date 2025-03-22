#include "lista.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

lista creazaListaGoala() {
    /**
     *creaza lista goala
     *prama: none
     *return: lista goala
     */
    lista l;
    l.len = 0;
    l.capacity = 2;
    l.arr = (tipElement*)malloc(sizeof(tipElement) * l.capacity);
    return l;
}


void distrugeLista(lista* l) {
    /*
     *distruge lista
     *
     *param l: lista de distrus
     *return: none
     *efect: distruge lista
     */
    if (l->arr != NULL) {
        for (int i = 0; i < l->len; i++) {
            distrugeOferta(&l->arr[i]);
        }
        free(l->arr);
        l->arr = NULL;
    }
    l->len = 0;
    l->capacity = 2;
}

tipElement getElement(lista* l, int poz){
    /*
     *obtine un element al unei liste
     *param l: lista
     *param poz: pozitia elementului in lista
     *return: elementul de la pozitia poz
     */
    return l->arr[poz];
}

tipElement setElement(lista* l, int poz, tipElement element) {
    /*
     *seteaza un element al unei liste
     *
     *param l: lista
     *param poz: pozitia pe care se va seta elementul
     *param element: elementul care va fi setat
     *return: vechiul element de pe acea pozitie
     */
    tipElement el = l->arr[poz];
    l->arr[poz] = element;
    return el;
}

int size(lista* l) {
    /**
     *afla lungimea listea
     *param l: lista
     *return: lungimea listei
     */
    return l->len;
}

int asigura_capacitatea(lista* l) {
    /**
     *asigura capacitatea unei lista
     *param l: lista
     *return: 1 daca lungimea listei s-a modificat, 0 altfel
     *efect: aloca dinamic lista
     */
    if (l->len <l->capacity) {
        return 1;
    }
    if (l->len > l->capacity) {
        return 0;
    }
    int newCapacity = l->capacity * 2;
    tipElement* newArr = malloc(sizeof(tipElement) * newCapacity);
    if (newArr == NULL) return 0;
    for (int i = 0; i < l->len; i++) {
        newArr[i] = l->arr[i];
    }
    if (l->arr != NULL) {
        free(l->arr);
    }
    l->arr = newArr;
    l->capacity = newCapacity;
    return 1;
}

void adaugare_element(lista* l, oferta of){
    /**
     *Adauga oferta
     *param l: lista de oferte
     *param of: ofera de adaugat
     *effect: adauga oferta in lista
     */
    int ok = asigura_capacitatea(l);
    if (ok) {
        l->arr[l->len] = of;
        l->len++;
    }
}

void actualizare(lista* l, char* tip, char *destinatie, char *data, float pret){
    /**
     *Actualizeaza oferta
     *
     *param l: lista
     *param tip: tipul ofertei
     *param destinatie: destinatia ofertei
     *param data: data ofertei
     *param pret: pretul ofertei
     *effect: actualizeaza oferta
     */
    for(int i=0; i < l->len; i++){
        if (strcmp(l->arr[i].tip, tip) == 0 && strcmp(l->arr[i].destinatie, destinatie) == 0){
            strcpy(l->arr[i].data, data);
            l->arr[i].pret=pret;
            break;
        }
    }
}

void stergere(lista* l, char* tip, char* destinatie) {
    /*
     *sterge oferta
     *
     *param l: lista
     *param tip: tipul ofertei
     *param destinatie: destinatia ofertei
     *return: none
     *efect: sterge oferta de tipul si cu destinatia data
     */
    for (int i = 0; i < l->len; i++) {
        if (l->arr[i].tip !=NULL && l->arr[i].destinatie != NULL) {
            if (strcmp(l->arr[i].tip, tip) == 0 && strcmp(l->arr[i].destinatie, destinatie) == 0) {
                for (int j = i; j < l->len - 1; j++) {
                    l->arr[j] = l->arr[j + 1];
                }
                l->len--;
                break;
            }
        }
    }
}