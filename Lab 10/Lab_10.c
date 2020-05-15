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
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <windows.h>
#include "uttils.h"

void menu();

int main(int argc, char const *argv[])
{
    int ans;
    char text[] = "Directed Graph Representation";
    do{
        header(strlen(text), text, "under");
        menu();
        do
        {
            printf(">> Input choice: ");
            scanf("%d", &ans);
            switch(ans){
                case 1:
                    //adj();
                    break;
                case 2:
                    //deg();
                    break;
                case 3:
                    return 0;
                default:
                    continue;
            }
            break;
        } while (1);
        
    } while(1);
}
void menu(){
    printf("1. Show Adjacency Matrix\n");
    printf("Show Degree of all vetrices\n");
    printf("3. Exit\n\n");
}
