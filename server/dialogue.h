#ifndef DIALOGUE_H
#define DIALOGUE_H

//Structure Dialogue (stock les réponses/données du fichier qr.txt)
typedef struct Dialogue DIALOGUE;
struct Dialogue
{
	char question[128];
	char reponse[128];
};

//Prototypes
DIALOGUE *stock_dialogue(char *filePath);
int line_number(char *filePath);

#endif