#ifndef OFERTA_H
#define OFERTA_H

typedef struct {
    char tip[15];
    char destinatie[15];
    char data[15];
    float pret;
} oferta;

oferta creazaOferta(char* tip, char* destinatie, char* data, float pret);
void distrugeOferta(oferta* oferta);

#endif