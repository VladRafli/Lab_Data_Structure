/*
    This code written by:
    Rafli Athala Jaskandi
    2301943402
    https://github.com/VladRafli
    This code uploaded on github in this link:
    https://github.com/VladRafli/Lab_Data_Structure
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include "uttils.h"

typedef struct Phone_Data node;
struct Phone_Data{
    char code[10];
    int price;
    node *left;
    node *right;
};
typedef struct Data_Input input;
struct Data_Input{
    char code[10];
    int price;
};

void menu();

int main(int argc, char const *argv[]){
    node *root;
    char head[] = "NOKIYEM CELLULAR PHONE";
    int ans;
    header(strlen(head), head, "under");
    menu();
    do{
        printf("\n>> Input choice: ");
        scanf("%d", &ans);
        fflush(stdin);
        switch(ans){
            case 1:
                //add();
                break;
            case 2:
                /*
                if(root != NULL)
                    update();
                else{
                    printf("There is no data to be updated!");
                    getch();
                    clrscr;
                }
                */
               break;
            case 3:
                /*
                if(root != NULL)
                    order();
                else{
                    printf("There is no data available");
                    getch();
                    clrscr;
                }
                */
               break;
            case 4:
                /*
                while(root != NULL)
                    pop();
                return 0;
                */
            default:
                continue;
        }
    } while(1);
}
void menu(){
    printf("1. Add New Phone\n");
    printf("2. Update Phone Price\n");
    printf("3. InOrder, PreOrder, PostOrder\n");
    printf("4. Exit\n");
}
