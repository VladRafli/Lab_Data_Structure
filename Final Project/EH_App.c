/*
 * Let's Encrypt and Hash App
 * Ver 0.1 (Alpha Build)
 * Prototype
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <conio.h>
#include "uttils.h"

void readMsg();
void sentMsg();
int readFile(const char *fileDest, char *msgCon);

int main(int argc, char const *argv[]){
    while(1){
        printf("Let's Encrypt and Hash your message...\n");
        printf("Ver 0.1 (Alpha Build)\n\n");
        printf("1. Read Message\n");
        printf("2. Sent Message\n");
        printf("3. Exit\n\n");
        printf(">> Input Choice: ");
        scanf("%d", &argc);
        fflush(stdin);
        switch(argc){
            case 1:
                readMsg();
                break;
            case 2:
                sentMsg();
                break;
            case 3:
                return 0;
            default:
                continue;
        }
    }
}
void readMsg(){
    char fileDest[200];
    char msgCon[200];
    char ans;
    clrscr;
    printf("Read Function...");
     while(1){
        printf("File Destination: ");
        gets(fileDest);
        if((fopen(fileDest, "r")) == NULL){
            printf("File not found!\n");
            do{
                printf("Cancel operation? [y/n]: ");
                ans = getche();
            } while(ans != 'y' || ans != 'n');
            if(ans == 'y')
                return;
            else
                break;
        }
    }
    readFile(fileDest, msgCon);
    getch();
    clrscr;
}
void sentMsg(){
    clrscr;
    printf("Sent Function...\n\n");
    getch();
    clrscr;
}
int readFile(const char *fileDest, char *msgCon){
    FILE *pf;
    pf = fopen(fileDest, "r");
    fgets(msgCon, 200, pf);
}