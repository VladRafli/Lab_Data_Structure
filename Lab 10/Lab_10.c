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
#include <conio.h>
#include "uttils.h"

/* Define this for Debug */
// #define DEBUG
/* --------------------- */
#define MATRIX_SIZE 10

typedef struct Node node;
struct Node{
    int vertex;
    node *next;
};
typedef struct Graph graph;
struct Graph{
    node *head;
    int inDeg;
    int outDeg;
    int totDeg;
    graph *next;
};

graph *graphHead = NULL;

void menu();
void inputVertices(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz);
void adjMatrix();
void adjList();
void deg();
void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz);
void createGraph(int *vertSiz);
void connectVertices(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz);
void printAdjList();
void countVertDeg();
void printVertDeg();

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
    inputVertices(matrix, &vertSiz); //Input Vertex Adjecency
    printMatrix(matrix, &vertSiz); //Print Adjecency Matrix
    getch();
    clrscr;
}
void adjList(){
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int vertSiz; //Vertices Size
    inputVertices(matrix, &vertSiz); //Input Vertex Adjecency
    createGraph(&vertSiz); //Create Graph
    connectVertices(matrix, &vertSiz); //Connect Vertices
    printAdjList(); //Print Adjecency List
    getch();
    clrscr;
}
void deg(){
    int matrix[MATRIX_SIZE][MATRIX_SIZE];
    int vertSiz; //Vertices Size
    inputVertices(matrix, &vertSiz); //Input Vertex Adjecency
    createGraph(&vertSiz); //Create Graph
    connectVertices(matrix, &vertSiz); //Connect Vertices
    countVertDeg(); //Count Vertex Degree
    printVertDeg(); //Print Vertex Degree
    getch();
    clrscr;
}
//Before: inputVertices(int *matrix, int *vertSiz)
void inputVertices(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz){
    char ans;
    printf("\n\n");
    //Ask number of vertices needed
    do
    {
        printf("How Many Vertices ? <max = 10> : ");
        scanf("%d", vertSiz);
        fflush(stdin);
    } while (*vertSiz < 2 || *vertSiz > 10);
    //Ask if vertex one and another is adjecent or not
    for(int i = 0; i < *vertSiz; i++){
        for(int j = 0; j < *vertSiz; j++){
            do{
                //If matrix[0][0], [1][1], etc. The vertex is not adjecent because you can't give edge to its own vertex
                if(i == j && j == i){
                    matrix[i][j] = 0;
                    break;
                } else{
                    printf("Vertices %d & %d are Adjacent ? <Y/N> : ", i + 1, j + 1); //Use i + 1 and j + 1, because the array reading is from index 0, but the vertex numbering is start from 1
                    ans = getch();
                    fflush(stdin);
                    if(ans == 'y' || ans == 'n'){
                        printf("%c", ans);
                        /* Set Vertice Adjacent */
                        if(ans == 'y'){
                            matrix[i][j] = 1; //Adjecent
                        } else if(ans == 'n'){
                            matrix[i][j] = 0; //Not Adjecent
                        }
                        /* ---------------------- */
                        printf("\n\n");
                        break;
                    }
                    printf("\n");
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
    //Print the matrix
    for(i = 0; i < *vertSiz; i++){
        printf("    %d      ", i + 1);
        for(j = 0; j < *vertSiz; j++){
            printf("%d  ", matrix[i][j]);
        }
        printf("\n\n");
    }
}
void createGraph(int *vertSiz){
    node *temp;
    graph *newHeads, *graphPtr;
    //Create Node and Insert Number of each Vertices
    for(int i = 0; i < *vertSiz; i++){
        temp = (node *) malloc(sizeof(node)); //Horizontal Linked List
        newHeads = (graph *) malloc(sizeof(graph)); //Vertical Linked List
        temp->vertex = i + 1; //Vertex numbering is start from 1, so i + 1
        temp->next = NULL; //For Linked List read limiter
        //Debug
        #ifdef DEBUG
        printf("Graph Head: ");
        #endif
        //First Graph
        if(i == 0){
            newHeads->head = temp; //Point Vertex with Head from Graph
            newHeads->next = NULL; //Limiter
            graphHead = newHeads; //Set Graph Head to First Vertex Head
            //Debug
            #ifdef DEBUG
            printf("%d\n", graphHead->head->vertex);
            #endif
        } 
        //Another Graph
        else{
            graphPtr = graphHead; //Set Pointer to Head
            //Move graph pointer before NULL
            while(graphPtr->next != NULL)
                graphPtr = graphPtr->next;
            graphPtr->next = newHeads; //Link New Vertex Head to Graph
            newHeads->head = temp; //Point Vertex with Head from Graph
            newHeads->next = NULL; //Limiter
            //Debug
            #ifdef DEBUG
            printf("%d\n", graphPtr->next->head->vertex);
            #endif
        }
    }
}
void connectVertices(int matrix[MATRIX_SIZE][MATRIX_SIZE], int *vertSiz){
    graph *graphPtrSrc;
    graph *graphPtrDest;
    node *temp, *nodePtr;
    //Debug
    #ifdef DEBUG
    printf("\nHey, I'm at Connecting Vertices Now!\n\n");
    #endif
    for(int i = 0; i < *vertSiz; i++){
        for(int j = 0; j < *vertSiz; j++){
            if(matrix[i][j] == 1){
                graphPtrSrc = graphHead; //Set Pointer Search to Head
                graphPtrDest = graphHead; //Set Pointer Destination to Head
                //Debug
                #ifdef DEBUG
                printf("graphPtrSrc Vertex = %d , graphPtrDest Vertex = %d\n\n", graphPtrSrc->head->vertex, graphPtrDest->head->vertex);
                printf("Adjecent = %d Src = %d Dest = %d\n\n", matrix[i][j], i + 1, j + 1);
                #endif
                //While Searched Vertex not i + 1, move pointer
                while(graphPtrSrc->head->vertex != i + 1){
                    //Debug
                    #ifdef DEBUG
                    printf("%d != %d\n", graphPtrSrc->head->vertex, i + 1);
                    #endif
                    graphPtrSrc = graphPtrSrc->next;
                    //Debug
                    #ifdef DEBUG
                    printf("I'm now moving pointer graphPtrSrc!\n");
                    #endif
                }
                //While Destination Vertex not j + 1, move pointer
                while(graphPtrDest->head->vertex != j + 1){
                    //Debug
                    #ifdef DEBUG
                    printf("%d != %d\n", graphPtrDest->head->vertex, j + 1);
                    #endif
                    graphPtrDest = graphPtrDest->next;
                    //Debug
                    #ifdef DEBUG
                    printf("I'm now moving pointer graphPtrDest\n");
                    #endif
                }
                //Create Node Represent Searched Vertex is Adjecent to Destiation Vertex and Connect it
                nodePtr = graphPtrSrc->head; //Declare Node Pointer at Searched Vertex Head
                //Move Node Pointer while not NULL
                while(nodePtr->next != NULL)
                    nodePtr = nodePtr->next;
                temp = (node *) malloc(sizeof(node)); //Assign Memory for New Node
                temp->vertex = graphPtrDest->head->vertex; //Fill New Node Vertex with Vertex from Destination Vertex, represent if Searched Vertex is Adjecent with Destination Vertex
                temp->next = NULL; //Limiter
                nodePtr->next = temp; //Connect representation of Searched Vertex and Destination Vertex
                //Debug
                #ifdef DEBUG
                printf("\nI'm now connecting Vertices together\n\n");
                #endif
            }
        }
    }
}
void printAdjList(){
    graph *graphPtr;
    node *nodePtr;
    //Debug
    #ifdef DEBUG
    printf("Hey, I'm at Print Adjecent List Now!\n");
    #endif
    static const char text[] = "Adjacency List of This Graph";
    header(strlen(text), text, "under");
    printf("Vertex\n\n");
    for(graphPtr = graphHead; graphPtr != NULL; graphPtr = graphPtr->next){
        printf("    %d      ", graphPtr->head->vertex);
        for(nodePtr = graphPtr->head; nodePtr != NULL; nodePtr = nodePtr->next){
            if(nodePtr->vertex != graphPtr->head->vertex)
                printf("-> %d  ", nodePtr->vertex);
        }
        printf("\n\n");
    }
}
void countVertDeg(){
    graph *graphPtr, *graphPtrDest;
    node *nodePtr;
    //Initiate Degree counter to zero
    for(graphPtr = graphHead; graphPtr != NULL; graphPtr = graphPtr->next){
        graphPtr->inDeg = 0;
        graphPtr->outDeg = 0;
        graphPtr->totDeg = 0;
    }
    //Count the Vertices In Degree and Out Degree
    for(graphPtr = graphHead; graphPtr != NULL; graphPtr = graphPtr->next){
        for(nodePtr = graphPtr->head->next; nodePtr != NULL; nodePtr = nodePtr->next){
            graphPtr->outDeg += 1;
            for(graphPtrDest = graphHead; graphPtrDest->head->vertex != nodePtr->vertex; graphPtrDest = graphPtrDest->next);
            graphPtrDest->inDeg += 1;
        }
    }
    //Count the Vertices Total Degree
    for(graphPtr = graphHead; graphPtr != NULL; graphPtr = graphPtr->next)
        graphPtr->totDeg = graphPtr->inDeg + graphPtr->outDeg;
}
void printVertDeg(){
    graph *graphPtr;
    printf("Vertex            In_Degree      Out_degree      Total_Degree\n\n");
    for(graphPtr = graphHead; graphPtr != NULL; graphPtr = graphPtr->next){
        printf("  %d                   %d              %d                %d\n\n", graphPtr->head->vertex, graphPtr->inDeg, graphPtr->outDeg, graphPtr->totDeg);
    }
}