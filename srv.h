#ifndef SRV_H
#define SRV_H

#include "lista.h"

typedef struct{
    lista oferte;
}oferteleAgentiei;
typedef int (*FunctieComparare)(oferta of1, oferta of2);

oferteleAgentiei creazaOfertaAgentie();
void distrugeOfertaAgentie(oferteleAgentiei* ofa);
void adaugare_srv(oferteleAgentiei* ofa, char* tip, char* destinatie, char* data, float pret);
void actualizare_srv(lista* l, char* tip, char* destinatie, char* data, float pret);
void stergere_srv(lista* l, char* tip, char* destinatie);
int valid(char tip, char destinatie, char data, float pret);
char* afisare_srv(lista* l);
void sortare(lista*l, FunctieComparare funct);
lista filtruDestinatie(lista* l, char*dest);
lista filtruTip(lista* l, char*tip);
lista filtruPret(lista* l, float pret_inf, float pret_sup);
int egale(oferta of1, oferta of2);
int comp_pret_cresc(oferta of1, oferta of2);
int comp_pret_descresc(oferta of1, oferta of2);
int comp_dest_cresc(oferta of1, oferta of2);
int comp_dest_descresc(oferta of1, oferta of2);
#endif