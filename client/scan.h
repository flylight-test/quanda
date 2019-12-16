#ifndef SCAN_H
#define SCAN_H

//Prototypes des fonctions améliorées de scanf

int my_string_scanf(char *chaine, int longueur); //Lire une chaine de caractère
int my_int_scanf(); //Lire un int
void viderBuffer(); //Permet d'éviter le buffer overflow

#endif