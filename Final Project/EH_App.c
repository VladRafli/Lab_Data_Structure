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

#define MAX_DATA 225

typedef struct Graph_Tree graph;
typedef struct Database_Nodes node;
typedef struct User_Data data;
typedef struct Date_Of_Birth dob;
typedef struct Input_Data input;

struct Graph_Tree{
    node *head[10];
};
struct Database_Nodes{
    data *dataPtr;
    node *next;
};
struct User_Data{
    char name[MAX_DATA];
    dob date;
    char username[MAX_DATA];
    char password[MAX_DATA];
};
struct Date_Of_Birth{
    int day;
    int month;
    int year;
};
struct Input_Data{
    char name[MAX_DATA];
    dob date;
    char username[MAX_DATA];
    char password[MAX_DATA];
};

void secureData();
void openData();
void inputData();

int main(int argc, char const *argv[]){
    while(1){
        printf("Let's Encrypt, Hash, Salt your Personal Info...\n");
        printf("Ver 0.1 (Alpha Build)\n\n");
        printf("1. Secure Info\n");
        printf("2. Read Info\n");
        printf("3. Exit\n\n");
        printf(">> Input Choice: ");
        scanf("%d", &argc);
        fflush(stdin);
        switch(argc){
            case 1:
                secureData();
                break;
            case 2:
                openData();
                break;
            case 3:
                return 0;
            default:
                continue;
        }
    }
}