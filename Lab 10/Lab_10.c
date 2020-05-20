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
#include <conio.h>
#include "uttils.h"

typedef struct Node node;
struct Node{
    int vertex;
    node *next;
};
struct Graph {
    node **heads;
};

void menu();
void inputVertices();
void adjMatrix();
void adjList();
void deg();

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
                    adjMatrix();
                    break;
                case 2:
                    adjList();
                    break;
                case 3:
                    deg();
                    break;
                case 4:
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
    printf("2. Show Adjacency List\n");
    printf("3. Show Degree of all vetrices\n");
    printf("4. Exit\n\n");
}
void adjMatrix(){
    inputVertices();
    getch();
    clrscr;
}
void adjList(){
    inputVertices();
    getch();
    clrscr;
}
void deg(){
    inputVertices();
    getch();
    clrscr;
}
void inputVertices(){
    int vertSiz; //Vertices Size
    char ans;
    printf("\n\n");
    do
    {
        printf("How Many Vertices ? <max = 10> : ");
        scanf("%d", &vertSiz);
        fflush(stdin);
    } while (vertSiz < 2 || vertSiz > 10);
    for(int i = 1; i <= vertSiz; i++){
        for(int j = 1; j <= vertSiz; j++){
            if(j != i){
                do{
                    printf("Vertices %d & %d are Adjacent ? <Y/N> : ", i, j);
                    ans = getch();
                    fflush(stdin);
                    if(ans == 'y' || ans == 'n'){
                        printf("%c", ans);
                        /* Set Vertice Adjacent */
                        //Here
                        /* */
                        printf("\n\n");
                        break;
                    }
                } while (1);
            }
        }
    }
}