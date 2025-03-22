
#include "teste.h"
#include "lista.h"
#include "srv.h"
#include "validator.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

void test_val_tip(){
    assert(val_tip("munte") == 1);
    assert(val_tip("dsfg") == 0);
    assert(val_tip("mare") == 1);
    assert(val_tip("city break") == 1);
    assert(val_tip("1234") == 0);
}

void test_val_destinatie() {
    assert(val_destinatie("olanda") == 1);
    assert(val_destinatie("1234") == 0);
    assert(val_destinatie("~1/*") == 0);
    assert(val_destinatie("moldova") == 1);
    assert(val_destinatie("vatican") == 1);
    assert(val_destinatie("") == 0);
}

void test_val_data() {
    assert(val_data("12/02/2026") == 1);
    assert(val_data("17/09/2027") == 1);
    assert(val_data("22/07/2025") == 1);
    assert(val_data("33/09/2025") == 0);
    assert(val_data("29/02/2028") == 1);
    assert(val_data("02/15/2025") == 0);
    assert(val_data("17/09/2000") == 0);
    assert(val_data("wefcs") == 0);
    assert(val_data("22/dfg/2025") == 0);
}

void test_val_pret() {
    assert(val_pret(1234) == 1);
    assert(val_pret(17) == 1);
    assert(val_pret(-100) == 0);
}

void test_oferta() {
    oferta of = creazaOferta("munte", "elvetia", "12/12/2025", 2000);
    assert(strcmp(of.tip, "munte") == 0);
    assert(strcmp(of.destinatie,"elvetia") == 0);
    assert(strcmp(of.data, "12/12/2025") == 0);
    assert(of.pret == 2000);
}

void test_lista(){
    lista l=creazaListaGoala();
    l.len=0;
    oferta of1 = creazaOferta("mare", "monaco", "22/08/2025", 1302);
    oferta of2 = creazaOferta("munte", "elvetia", "12/12/2025", 2000);
    oferta of3 = creazaOferta("city break", "spania", "10/06/2025", 5000);

    adaugare_element(&l, of1);
    adaugare_element(&l, of2);
    adaugare_element(&l, of3);
    assert(strcmp(l.arr[0].data, "22/08/2025") == 0);
    assert(strcmp(l.arr[0].tip, "mare") == 0);
    assert(strcmp(l.arr[0].destinatie, "monaco") == 0);
    assert(l.arr[0].pret == 1302);
    assert(strcmp(l.arr[1].data, "12/12/2025") == 0);
    assert(strcmp(l.arr[1].tip, "munte") == 0);
    assert(strcmp(l.arr[1].destinatie, "elvetia") == 0);
    assert(l.arr[1].pret == 2000);
    assert(strcmp(l.arr[2].data, "10/06/2025") == 0);
    assert(strcmp(l.arr[2].tip, "city break") == 0);
    assert(strcmp(l.arr[2].destinatie, "spania") == 0);
    assert(l.arr[2].pret == 5000);

    assert(size(&l) == 3);

    actualizare(&l, "mare", "monaco", "12/08/2025", 2500);
    assert(strcmp(l.arr[0].data, "12/08/2025") == 0);
    assert(strcmp(l.arr[0].tip, "mare") == 0);
    assert(strcmp(l.arr[0].destinatie, "monaco") == 0);
    assert(l.arr[0].pret == 2500);

    stergere(&l, "mare", "monaco");
    assert(l.len == 2);

    oferta of_get = getElement(&l, 0);
    assert(strcmp(of_get.tip, l.arr[0].tip) == 0);
    assert(strcmp(of_get.destinatie, l.arr[0].destinatie) == 0);
    assert(strcmp(of_get.data, l.arr[0].data) == 0);
    assert(of_get.pret == l.arr[0].pret);

    oferta of_set = creazaOferta("city break", "olanda", "21/05/2025", 3500);
    setElement(&l, 0, of_set);
    assert(strcmp(of_set.tip, l.arr[0].tip) == 0);
    assert(strcmp(of_set.destinatie, l.arr[0].destinatie) == 0);
    assert(strcmp(of_set.data, l.arr[0].data) == 0);
    assert(of_set.pret == l.arr[0].pret);

    distrugeLista(&l);
    assert(l.arr == NULL);
    assert(l.len == 0);
    assert(l.capacity == 2);

    lista l2;
    l2.len=10;
    l2.capacity=5;
    assert(asigura_capacitatea(&l2) == 0);
}

void test_srv(){
    oferteleAgentiei ofa = creazaOfertaAgentie();
    adaugare_srv(&ofa, "munte", "elvetia", "04/07/2026", 1500);
    assert(strcmp(ofa.oferte.arr[0].tip, "munte") == 0);
    assert(strcmp(ofa.oferte.arr[0].destinatie, "elvetia") == 0);
    assert(strcmp(ofa.oferte.arr[0].data, "04/07/2026") == 0);
    assert(ofa.oferte.arr[0].pret == 1500);

    actualizare_srv(&ofa.oferte, "munte", "elvetia", "22/06/2025", 1700);
    assert(strcmp(ofa.oferte.arr[0].tip, "munte") == 0);
    assert(strcmp(ofa.oferte.arr[0].destinatie, "elvetia") == 0);
    assert(strcmp(ofa.oferte.arr[0].data, "22/06/2025") == 0);
    assert(ofa.oferte.arr[0].pret == 1700);

    adaugare_srv(&ofa, "mare", "moldova", "20/10/2025", 100);
    adaugare_srv(&ofa, "city break", "spania", "13/08/2026", 3000);
    adaugare_srv(&ofa, "mare", "italia", "30/06/2025", 1500);

    oferta of1 = creazaOferta("munte", "elvetia", "22/06/2025", 1700);
    oferta of2 = creazaOferta("mare", "moldova", "20/20/2025", 100);
    oferta of3 = creazaOferta("city break", "spania", "13/08/2026", 3000);
    oferta of4 = creazaOferta("mare", "italia", "30/06/2025", 1500);

    sortare(&ofa.oferte, comp_pret_cresc);
    assert(egale(ofa.oferte.arr[0], of2) == 1);
    assert(egale(ofa.oferte.arr[1], of4) == 1);
    assert(egale(ofa.oferte.arr[2], of1) == 1);
    assert(egale(ofa.oferte.arr[3], of3) == 1);
    assert(egale(ofa.oferte.arr[1], of2) == 0);

    sortare(&ofa.oferte, comp_pret_descresc);
    assert(egale(ofa.oferte.arr[0], of3) == 1);
    assert(egale(ofa.oferte.arr[1], of1) == 1);
    assert(egale(ofa.oferte.arr[2], of4) == 1);
    assert(egale(ofa.oferte.arr[3], of2) == 1);

    sortare(&ofa.oferte, comp_dest_cresc);
    assert(egale(ofa.oferte.arr[0], of1) == 1);
    assert(egale(ofa.oferte.arr[1], of4) == 1);
    assert(egale(ofa.oferte.arr[2], of2) == 1);
    assert(egale(ofa.oferte.arr[3], of3) == 1);

    sortare(&ofa.oferte, comp_dest_descresc);
    assert(egale(ofa.oferte.arr[0], of3) == 1);
    assert(egale(ofa.oferte.arr[1], of2) == 1);
    assert(egale(ofa.oferte.arr[2], of4) == 1);
    assert(egale(ofa.oferte.arr[3], of1) == 1);

    lista l1 = filtruTip(&ofa.oferte, "mare");
    assert(egale(l1.arr[0], of2) == 1);
    assert(egale(l1.arr[1], of4) == 1);
    assert(l1.len == 2);
    distrugeLista(&l1);

    lista l2=filtruDestinatie(&ofa.oferte, "italia");
    assert(egale(l2.arr[0], of4) == 1);
    assert(l2.len == 1);
    distrugeLista(&l2);

    lista l3=filtruPret(&ofa.oferte, 1000, 2000);
    assert(egale(l3.arr[0], of4) == 1);
    assert(egale(l3.arr[1], of1) == 1);
    assert(l3.len == 2);
    distrugeLista(&l3);

    stergere_srv(&ofa.oferte, "mare", "moldova");
    assert(ofa.oferte.len == 3);
    stergere(&ofa.oferte, "munte", "elvetia");
    assert(ofa.oferte.len == 2);
    distrugeOfertaAgentie(&ofa);
}

void ruleaza_teste(){

    test_val_tip();
    test_val_destinatie();
    test_val_data();
    test_val_pret();
    test_oferta();
    test_lista();
    test_srv();

}