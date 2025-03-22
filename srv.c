#include "srv.h"
#include "lista.h"
#include "validator.h"

#include <stdio.h>
#include <string.h>

oferteleAgentiei creazaOfertaAgentie() {
    /**
     *Creaza lista goala de oferte
     *
     *param: NONE
     *return: lista goala de oferte
     */
    oferteleAgentiei ofa;
    ofa.oferte = creazaListaGoala();
    return ofa;
}

void distrugeOfertaAgentie(oferteleAgentiei* ofa) {
    /**
     * Distruge ofertele agentiei
     *
     * param ofa: ofertele agentiei
     * return: none
     * efect: distruge ofertele
     */
    distrugeLista(&ofa->oferte);
}

void adaugare_srv(oferteleAgentiei* ofa, char* tip, char* destinatie, char* data, float pret){
    /**
     *Adauga oferta
     *
     *param l: lista
     *param tip: tipul ofertei
     *param destinatie: destinatia ofertei
     *param data: data ofertei
     *param pret: pretul ofertei
     *effect: adauga oferta
     */
    oferta of = creazaOferta(tip, destinatie, data, pret);
    adaugare_element(&ofa->oferte,of);
}

void actualizare_srv(lista* l, char* tip, char* destinatie, char* data, float pret) {
    /**
     *Actualizeaza oferta oferta
     *
     *param l: lista
     *param tip: tipul ofertei
     *param destinatie: destinatia ofertei
     *param data: data ofertei
     *param pret: pretul ofertei
     *effect: actualizeaza oferta
     */
    actualizare(l, tip, destinatie, data, pret);
}

void stergere_srv(lista* l, char* tip, char* destinatie) {
    /**
     *Adauga oferta
     *
     *param l: lista
     *param tip: tipul ofertei
     *param destinatie: destinatia ofertei
     *effect: sterge oferta
     */
    stergere(l, tip, destinatie);
}

int egale(oferta of1, oferta of2) {
    /**
     * Verifica daca doua oferte sunt aceleasi
     *
     * param of1: prima oferta
     * param of2: a doua oferta
     * return: 1 daca ofertele sunt egale, 0 altfel
     */
    int ok=0;
    if (strcmp(of1.tip, of2.tip) == 0)
        ok++;
    if (strcmp(of1.destinatie, of2.destinatie) == 0)
        ok++;
    if (ok == 2)
        return 1;
    return 0;
}

int comp_pret_cresc(oferta of1, oferta of2) {
    /*
     *compara doua oferte pe baza pretului
     *
     *param of1: prima oferta
     *param of2: a doua oferta
     *return: 1 daca prima oferta are un pret mai mare decat a doua, -1 altfel
     */
    if (of1.pret>of2.pret)
        return 1;
    return -1;
}

int comp_pret_descresc(oferta of1, oferta of2) {
    /*
     *compara doua oferte pe baza pretului
     *
     *param of1: prima oferta
     *param of2: a doua oferta
     *return: -1 daca prima oferta are un pret mai mare decat a doua, 1 altfel
     */
    if (of1.pret>of2.pret)
        return -1;
    return 1;
}

int comp_dest_cresc(oferta of1, oferta of2) {
    /*
     *compara doua oferte pe baza destinatiei
     *
     *param of1: prima oferta
     *param of2: a doua oferta
     *return: 1 daca prima oferta este inainte alfabetic fata de a doua, -1 altfel
     */
    if (strcmp(of1.destinatie, of2.destinatie)>0)
        return 1;
    return -1;
}

int comp_dest_descresc(oferta of1, oferta of2) {
    /*
     *compara doua oferte pe baza destinatiei
     *
     *param of1: prima oferta
     *param of2: a doua oferta
     *return: 1 daca a doua oferta este inainte alfabetic fata de prima, -1 altfel
     */
    if (strcmp(of1.destinatie, of2.destinatie)>0)
        return -1;
    return 1;
}

void sortare(lista* l, FunctieComparare funct) {
    /**
     * Sorteaza elementele listei
     *
     * param l: lista de sortat
     * param key: dupa ce se va face sortarea
     * param ord: 1 daca se doreste sa se afla daca of1>of2, -1 altfel
     * return: none
     * efect: ordoneaza lista dupa un criteriu
     */
    for (int i=0; i<size(l)-1; i++)
        for (int j=i+1; j<size(l); j++) {
            oferta of1 = getElement(l,i);
            oferta of2 = getElement(l,j);
            if (funct(of1, of2)>0) {
                oferta ok = of1;
                setElement(l,i,of2);
                setElement(l,j,ok);
            }
        }
}

lista filtruDestinatie(lista* l, char* dest) {
    /**
     * Filtreaza lista in functie de destinatie
     *
     * param l: lista de filtrat
     * param dest: destinatia aleasa
     * return: lista filtrata
     */
    lista filt = creazaListaGoala();
    for (int i=0; i<size(l); i++) {
        oferta of = getElement(l,i);
        if (strcmp(of.destinatie, dest) == 0)
            adaugare_element(&filt,of);
    }
    return filt;
}

lista filtruTip(lista* l, char* tip) {
    /**
     * Filtreaza lista in functie de tip
     *
     * param l: lista de filtrat
     * param tip: tipul ales
     * return: lista filtrata
     */
    lista filt = creazaListaGoala();
    for (int i=0; i<size(l); i++) {
        oferta of = getElement(l,i);
        if (strcmp(of.tip, tip) == 0)
            adaugare_element(&filt,of);
    }
    return filt;
}

lista filtruPret(lista* l, float pret_inf, float pret_sup) {
    /**
     * Filtreaza lista in functie de pret
     *
     * param l: lista de filtrat
     * param pret_inf: marginea inferioara a pretului
     * param pret_sup: marginea superioara a pretului
     * return: lista filtrata
     */
    lista filt = creazaListaGoala();
    for (int i=0; i<size(l); i++) {
        oferta of = getElement(l,i);
        if (of.pret>pret_inf && of.pret<pret_sup)
            adaugare_element(&filt,of);
    }
    return filt;
}