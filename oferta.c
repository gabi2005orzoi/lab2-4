#include "oferta.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

oferta creazaOferta(char* tip, char* destinatie, char* data, float pret) {
    /*
     *creaza oferta
     *param tip: tipul ofertei
     *param destinatie: destinatia ofertei
     *param data: data ofertei
     *param pret: pretul ofertei
     *return: oferta
     */
    oferta of;

    if (tip!=NULL) {
        strcpy(of.tip, tip);
    }

    if (destinatie!=NULL) {
        strcpy(of.destinatie, destinatie);
    }

    if (data!=NULL) {
        strcpy(of.data, data);
    }
    of.pret = pret;
    return of;
}

void distrugeOferta(oferta* of) {
    /*
     *distruge oferta
     *param of: oferta de distrus
     *return: none
     *efect: distruge oferta
     */
    strcpy(of->tip, "");
    strcpy(of->destinatie, "");
    strcpy(of->data, "");
    of->pret = -1;
}