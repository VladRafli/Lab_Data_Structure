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

#define MATRIX_SIZE 10

typedef struct Node node;
struct Node{
    int vertex;
    node *next;
};
typedef struct Graph graph;
struct Graph{
    node *head;
    graph *next;
};

graph *graphHead = NULL;

void menu();
void inputVertices(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz);
void adjMatrix();
void adjList();
void deg();
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz);
void graphAdj(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz);

int main(int argc, char const *argv[])
{
    int ans;
    static const char text[] = "Directed Graph Representation";
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
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int vertSiz; //Vertices Size
    inputVertices(matrix, &vertSiz);
    printMatrix(matrix, &vertSiz);
    getch();
    clrscr;
}
void adjList(){
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int vertSiz; //Vertices Size
    inputVertices(matrix, &vertSiz);
    graphAdj(matrix, &vertSiz);
    getch();
    clrscr;
}
void deg(){
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int vertSiz; //Vertices Size
    inputVertices(matrix, &vertSiz);
    getch();
    clrscr;
}
//Before: inputVertices(int *matrix, int *vertSiz)
void inputVertices(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz){
    char ans;
    printf("\n\n");
    do
    {
        printf("How Many Vertices ? <max = 10> : ");
        scanf("%d", vertSiz);
        fflush(stdin);
    } while (*vertSiz < 2 || *vertSiz > 10);
    for(int i = 0; i < *vertSiz; i++){
        for(int j = 0; j < *vertSiz; j++){
            do{
                if(i == j && j == i){
                    matrix[i][j] = 0;
                    break;
                } else{
                    printf("Vertices %d & %d are Adjacent ? <Y/N> : ", i, j);
                    ans = getch();
                    fflush(stdin);
                    if(ans == 'y' || ans == 'n'){
                        printf("%c", ans);
                        /* Set Vertice Adjacent */
                        if(ans == 'y'){
                            matrix[i][j] = 1;
                        } else if(ans == 'n'){
                            matrix[i][j] = 0;
                        }
                        /* ---------------------- */
                        printf("\n\n");
                        break;
                    }
                }
            } while (1);
        }
    }
}
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz){
    int i, j;
    static const char text[] = "Adjacency Matrix of this Graph";
    printf("\n\n");
    header(strlen(text), text, "under");
    printf("Vertex     ");
    for(i = 1; i <= *vertSiz; i++){
        printf("%d  ", i);
    }
    printf("\n\n");
    for(i = 0; i < *vertSiz; i++){
        printf("    %d      ", i + 1);
        for(j = 0; j < *vertSiz; j++){
            printf("%d  ", matrix[i][j]);
        }
        printf("\n\n");
    }
}
void graphAdj(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz){
    int i, j;
    node *temp;
    graph *newHeads, *graphPtr;
    //Create Node and Insert Number of each Vertices
    for(i = 0; i < *vertSiz; i++){
        temp = (node *) malloc(sizeof(node));
        newHeads = (graph *) malloc(sizeof(graph));
        temp->vertex = i + 1;
        temp->next = NULL;
        printf("Graph Head:\n");
        if(i == 0){
            newHeads->head = &temp;
            newHeads->next = NULL;
            graphHead = newHeads;
            printf("%d\n", graphHead->head); //Prints the Address
        } else{
            graphPtr = graphHead;
            while(graphPtr->next != NULL)
                graphPtr = graphPtr->next;
            graphPtr->next = newHeads;
            newHeads->head = &temp;
            newHeads->next = NULL;
            printf("%d\n", graphPtr->head); //Prints the Address
        }
    }
    /*
    //Look for Matrix Adjacency each Node
    for(i = 0; i < *vertSiz; i++){
        for(j = 0; j < *vertSiz; j++){
            if(i == j && j == i){
                //Not Connect anything because its connecting to own node
            } else if(matrix[i][j] == 0){
                //Not Connect anything because its not adjecent
            } else{
                graphPtr = graphHead;
                //Linked List Linear Search
            }
        }
    }
    */
}