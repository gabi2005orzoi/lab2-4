#include "console.h"
#include "srv.h"
#include "validator.h"
#include "lista.h"
#include <stdio.h>
#include <string.h>

void meniu(){
    /**
     *Afiseaza meniul
     *param: None
     *return: None
     */
    printf("\n ---MENIU---");
    printf("\n1. Adaugare oferta");
    printf("\n2. Sterge oferta");
    printf("\n3. Actualizare oferta");
    printf("\n4. Vizualizare oferete ordonat dupa pret, destinatie (crescator/descrescator)");
    printf("\n5. Vizualizare oferta filtrate dupa un criteriu (destinatie, tip, pret)");
    printf("\n6. Afisare");
    printf("\n0. Iesire din aplicatie");
}

void afisare(lista* l) {
    if (l->len == 0) {
        printf("Nu s-au gasit oferte");
        return;
    }
    for (int i=0; i<l->len; i++) {
        printf("%s | %s | %s | %f\n", l->arr[i].tip, l->arr[i].destinatie, l->arr[i].data, l->arr[i].pret);
    }
}

void run(){
    oferteleAgentiei ofa = creazaOfertaAgentie();
    meniu();
    int op;
    while(1){
        printf("\n>>>");
        scanf("%d",&op);
        if (op == 1){
            char tip[50], destinatie[50], data[10];
            float pret;
            printf("Tip: ");
            scanf("%s",tip);
            if (!val_tip(tip))
                printf("\nTipul nu este valid");
            else {
                printf("Destinatie: ");
                scanf("%s",destinatie);
                if (!val_destinatie(destinatie))
                    printf("\nDestinatia nu este valid");
                else{
                    printf("Data(DD/MM/YYYY): ");
                    scanf("%s",data);
                    if (!val_data(data))
                        printf("\nData nu este valid");
                    else {
                        printf("Pret: ");
                        scanf("%f",&pret);
                        if (!val_pret(pret))
                            printf("\nPret nu este valid");
                        else
                            adaugare_srv(&ofa,tip,destinatie,data,pret);
                    }
                }
            }
        }
        else if (op == 3){
            char tip[50], destinatie[50], data[10];
            float pret;
            printf("Tip: ");
            scanf("%s",tip);
            printf("Destinatie: ");
            scanf("%s",destinatie);
            printf("Data: ");
            scanf("%s",data);
            printf("Pret: ");
            scanf("%f",&pret);
            actualizare_srv(&ofa.oferte,tip,destinatie,data,pret);
        }
        else if (op == 2) {
            char tip[50], destinatie[50], data[10];
            float pret;
            printf("Tip: ");
            scanf("%s",tip);
            if (!val_tip(tip))
                printf("\nTipul nu este valid");
            else {
                printf("Destinatie: ");
                scanf("%s",destinatie);
                if (!val_destinatie(destinatie))
                    printf("\nDestinatia nu este valid");
                else{
                    printf("Data: ");
                    scanf("%s",data);
                    if (!val_data(data))
                        printf("\nData nu este valid");
                    else {
                        printf("Pret: ");
                        scanf("%f",&pret);
                        if (!val_pret(pret))
                            printf("\nPret nu este valid");
                        else
                            actualizare_srv(&ofa.oferte,tip,destinatie,data,pret);
                    }
                }
            }
        }
        else if (op == 4) {
            char key[20], st[20];
            printf("Doriti sa sortati dupa: ");
            scanf ("%s", key);
            printf("Doriti sa ordonati: ");
            scanf ("%s", st);
            if (strcmp(key, "pret") == 0) {
                if (strcmp(st, "crescatoare") == 0)
                    sortare(&ofa.oferte, comp_pret_cresc);
                else if (strcmp(st, "descrescatoare") == 0)
                    sortare(&ofa.oferte, comp_pret_descresc);
            }
            else if (strcmp(key, "destinatie") == 0) {
                if (strcmp(st, "crescatoare") == 0)
                    sortare(&ofa.oferte, comp_dest_cresc);
                else if (strcmp(st, "descrescatoare") == 0)
                    sortare(&ofa.oferte, comp_dest_descresc);
            }
        }
        else if (op == 5) {
            char criteriu[20];
            printf("Doriti sa filtrati dupa: ");
            scanf("%s", criteriu);
            if (strcmp(criteriu, "destinatie") == 0) {
                char dest[20];
                printf("Introduce-ti destinatia: ");
                scanf("%s", dest);
                lista li=filtruDestinatie(&ofa.oferte, dest);
                afisare(&li);
                distrugeLista(&li);
            }
            else if (strcmp(criteriu, "tip") == 0) {
                char tip[20];
                printf("Introduce-ti tipul: ");
                scanf("%s", tip);
                lista li=filtruTip(&ofa.oferte, tip);
                afisare(&li);
                distrugeLista(&li);
            }
            else if (strcmp(criteriu, "pret") == 0) {
                float pret_inf, pret_sup;
                printf("Introduce-ti marginea inferioara a pretului: ");
                scanf("%f", &pret_inf);
                printf("Introduce-ti marginea superioara a pretului: ");
                scanf("%f", &pret_sup);
                lista li = filtruPret(&ofa.oferte, pret_inf, pret_sup);
                afisare(&li);
                distrugeLista(&li);
            }
        }
        else if (op == 6) {
            afisare(&ofa.oferte);
        }
        else if (op == 0) {
            break;
        }
        else printf("Comanda invalida");
    }
    distrugeOfertaAgentie(&ofa);
}