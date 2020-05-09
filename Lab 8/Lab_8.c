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
#include <time.h>
#include <unistd.h>
#include "uttils.h"
#define MAX_NAME 20
#define SUCCESS 0
#define FAILED 1

char default_view_function[30] = "preorder";

typedef struct Player_Data node;
typedef struct Data_Input input;
struct Player_Data{
    char name[MAX_NAME];
    int num;
    int leftPos; //Calculate how much pointer move to left leaf
    int rightPos; //calculate how much pointer move to right leaf
    node *left;
    node *right;
};
node *root = NULL;
struct Data_Input{
    char name[MAX_NAME];
    int num;
};

void menu();
void view(char *command); //To call this function, ensure fill the parameter, even if empty string would work
void add();
int push(input *input);
void insert(node *root, node *temp);
void order();
void preorder(node *tree);
void inorder(node *tree);
void postorder(node *tree);
void config();

int main(int argc, char const *argv[])
{
    char head[] = "BLUE FOOTBALL MANAGER";
    int ans;
    do{
        header(strlen(head), head, "under");
        menu();
        do{
            printf(">> Input Choice: ");
            scanf("%d", &ans);
            fflush(stdin);
            switch(ans){
            case 1:
                if(root != NULL)
                    view(default_view_function);
                else{
                    printf("No data available!");
                    getch();
                    clrscr;
                }
                break;
            case 2:
                add();
                break;
            case 3:
                /*
                if(root != NULL)
                    remove();
                else{
                    printf("No data available!");
                    getch();
                    clrscr;
                }
                */
                break;
            case 4:
                if(root != NULL)
                    order();
                else{
                    printf("No data available!");
                    getch();
                    clrscr;
                }
                break;
            case 5:
                config();
                break;
            case 6:
                /*
                while(root != NULL)
                    pop();
                */
               return 0;
            default:
                continue;
            }
        break;
        } while(1);
    } while(1);
}
void menu(){
    printf("1. View All Player\n");
    printf("2. Add Player\n");
    printf("3, Remove Player\n");
    printf("4. Inorder, Preorder, Postorder\n");
    printf("5. Config\n");
    printf("6. Exit and Remove All\n\n");
    printf("*note: View All Player using %s Method\nYou can visualize by yourself using position data...\n", default_view_function);
    printf("Position[L,R]: 1,1; Means the node positioned in steps:\nFrom Root, 1x Move to Left Leaf, 1x Move to Right Leaf\n\n");
}
void view(char *command){
    clrscr;
    if(strcmp(command, "preorder") == 0)
        preorder(root);
    else if(strcmp(command, "inorder") == 0)
        inorder(root);
    else if(strcmp(command, "postorder") == 0)
        postorder(root);
    else
        printf("No config available for this option...");
    getch();
    clrscr;
    return;
}
void add(){
    input input;
    int push_status;
    clrscr;
    do{
        printf("Input Player's Name [3..20]: ");
        gets(input.name);
        fflush(stdin);
    } while(strlen(input.name) < 3 || strlen(input.name) > 20);
    printf("\n");
    do{
        printf("Input Player's Back Number [1..99]: ");
        scanf("%d", &input.num);
        fflush(stdin);
    } while(input.num < 1 || input.num > 99);
    printf("\n");
    /* Push */
    push_status = push(&input);
    /********/
    if(push_status == SUCCESS){
        printf("--- Add Player Success ---");
    } else if(push_status == FAILED){
        printf("--- Add Player Failed ---");
    }
    getch();
    clrscr;
}
int push(input *input){
    char node_pos[10];
    int tempLeftPos = 0;
    int tempRightPos = 0;
    node *cur;
    node *temp = (node *) malloc(sizeof(node)); //Memory Allocation fo New
    if(temp == NULL){
        //If memory didn't allocated, return failed status
        perror("Error: ");
        sleep(2);
        return FAILED;
    } else{
        //Input Data to New Node
        strcpy(temp->name, input->name);
        temp->num = input->num;
        //Initialize Left and Right Pointer to NULL
        temp->left = NULL;
        temp->right = NULL;
        /* Scenario 1: If no Node Available */
        if(root == NULL){
            root = temp;
            root->leftPos = 0;
            root->rightPos = 0;
            return SUCCESS;
        }
        /* Scenario 2: If there is a Node Available */ 
        else{
            cur = root;
            //Repetition to ask user for node location
            while(1){
                do{
                    //Ask user to direct the pointer to desired location
                    printf("Will He Be in \'left\' or \'right\' %s?: ", temp->name);
                    gets(node_pos);
                    fflush(stdin);
                } while (strcmp(node_pos, "left") != 0 && strcmp(node_pos, "right") != 0);
                /* Scenario 2.1: If user ask left */
                if(strcmp(node_pos, "left") == 0){
                    /* Scenario 2.1.1: If Left Leaf is not NULL */
                    if(cur->left != NULL){
                        tempLeftPos++;
                        cur = cur->left;
                        printf("This node already booked with player number %d data\n\n", cur->num);
                    } 
                    /* Scenario 2.2.2: If Left Leaf is NULL */
                    else{
                        tempLeftPos++;
                        cur->left = temp;
                        temp->leftPos = tempLeftPos;
                        temp->rightPos = tempRightPos;
                        printf("\n[!] Please Wait... [!]\n");
                        printf("Establishing Link to New Node");
                        for(int i = 0; i < 3; i++){
                            usleep(100000);
                            printf(".");
                        }
                        printf("\nNode Successfully Linked!\n\n");
                        sleep(2);
                        return SUCCESS;
                    }
                } 
                /* Scenario 2.2: If user ask right */
                else if(strcmp(node_pos, "right") == 0){
                    /* Scenario 2.2.1: If Right Leaf is not NULL */
                    if(cur->right != NULL){
                        tempRightPos++;
                        cur = cur->right;
                        printf("This node already booked with player number %d data\n\n", cur->num);
                    } 
                    /* Scenario 2.2.2: If Right Leaf is NULL */
                    else{
                        tempRightPos++;
                        cur->right = temp;
                        temp->leftPos = tempLeftPos;
                        temp->rightPos = tempRightPos;
                        printf("\n[!] Please Wait... [!]\n");
                        printf("Establishing Link to New Node");
                        for(int i = 0; i < 3; i++){
                            usleep(10000);
                            printf(".");
                        }
                        printf("\nNode Successfully Linked!\n\n");
                        sleep(2);
                        return SUCCESS;
                    }
                }
            }
        }
    }
}
void order(){
    int ans;
    clrscr;
    printf("1. Inorder\n");
    printf("2. Preorder\n");
    printf("3. Postorder\n");
    do{
        printf("\n>> Input choice : ");
        scanf("%d", &ans);
        fflush(stdin);
        printf("\n");
        switch(ans){
            case 1:
                inorder(root);
                getch();
                clrscr;
                return;
            case 2:
                preorder(root);
                getch();
                clrscr;
                return;
            case 3:
                postorder(root);
                getch();
                clrscr;
                return;
            default:
                continue;
        }
    } while(1);
}
void preorder(node *tree){
    if(tree != NULL){
        printf("%s <%d> Position[L,R]: %d,%d\n", tree->name, tree->num, tree->leftPos, tree->rightPos);
        preorder(tree->left);
        preorder(tree->right);
    }
    return;
}
void inorder(node *tree){
    if(tree != NULL){
        inorder(tree->left);
        printf("%s <%d> Position[L,R]: %d,%d\n", tree->name, tree->num, tree->leftPos, tree->rightPos);
        inorder(tree->right);
    }
    return;
}
void postorder(node *tree){
    if(tree != NULL){
        postorder(tree->left);
        postorder(tree->right);
        printf("%s <%d> Position[L,R]: %d,%d\n", tree->name, tree->num, tree->leftPos, tree->rightPos);
    }
    return;
}
void config(){
    char ans;
    int a;
    clrscr;
    printf("Change default function view player? [y/n]: ");
    ans = getch();
    printf("\n");
    if(ans == 'y'){
        printf("Current default function: %s\n", default_view_function);
        if(strcmp(default_view_function, "preorder") == 0){
            printf("Change to:\n");
            printf("1. Inorder\n");
            printf("2. Postorder\n\n");
            do{
                printf(">>Input Choice: ");
                scanf("%d", &a);
                fflush(stdin);
                switch(a){
                    case 1:
                        strcpy(default_view_function, "inorder");
                        printf("Sucessfully changed!");
                        sleep(1);
                        return;
                    case 2:
                        strcpy(default_view_function, "postorder");
                        printf("Sucessfully changed!");
                        sleep(1);
                        return;
                    default:
                        continue;
                }
            } while(1);
        }
            else if(strcmp(default_view_function, "inorder") == 0){
            printf("Change to:\n");
            printf("1. Preorder\n");
            printf("2. Postorder\n\n");
            do{
                printf(">>Input Choice: ");
                scanf("%d", &a);
                ffulsh(stdin);
                switch(a){
                    case 1:
                        strcpy(default_view_function, "preorder");
                        printf("Sucessfully changed!");
                        sleep(1);
                        return;
                    case 2:
                        strcpy(default_view_function, "postorder");
                        printf("Sucessfully changed!");
                        sleep(1);
                        return;
                    default:
                        continue;
                }
            } while(1);
        }
            else if(strcmp(default_view_function, "postorder") == 0){
            printf("Change to:\n");
            printf("1. Preorder\n");
            printf("2. Inorder\n\n");
            do{
                printf(">>Input Choice: ");
                scanf("%d", &a);
                fflush(stdin);
                switch(a){
                    case 1:
                        strcpy(default_view_function, "preorder");
                        printf("Sucessfully changed!");
                        sleep(1);
                        return;
                    case 2:
                        strcpy(default_view_function, "inorder");
                        printf("Sucessfully changed!");
                        sleep(1);
                        return;
                    default:
                        continue;
                }
            } while(1);
        }
    } else{
        clrscr;
        return;
    }
}