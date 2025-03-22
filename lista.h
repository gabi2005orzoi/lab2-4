#ifndef LISTA_H
#define LISTA_H

#include "oferta.h"
typedef oferta tipElement;
typedef struct{
  tipElement* arr;
  int len;
  int capacity;
}lista;

lista creazaListaGoala();
void distrugeLista(lista* l);
tipElement getElement(lista* l, int poz);
tipElement setElement(lista* l, int poz, tipElement element);
int size(lista* l);
int asigura_capacitatea(lista* l);
void adaugare_element(lista* l, oferta of);
void actualizare(lista* l, char* tip, char *destinatie, char *data, float pret);
void stergere(lista* l, char* tip, char *destinatie);

#endif