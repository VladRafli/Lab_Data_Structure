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
#include "uttils.h"
#define MAX_CODE 10

_Bool random_status = true;

typedef struct Phone_Data node;
struct Phone_Data{
    char code[MAX_CODE];
    int price;
    node *left;
    node *right;
};
typedef struct Data_Input input;
struct Data_Input{
    char code[MAX_CODE];
    int price;
};

void menu();
int add(node **root, input *input);
void randomCode(input *input); //This random string only used for this code only
void randomPrice(input *input); //This random string only used for this code only
_Bool check(node **root, input *input);
int push(node **root, input *input);
void order(node *root);
void preorder(node *tree);
void inorder(node *tree);
void postorder(node *tree);

int main(int argc, char const *argv[]){
    node *root = NULL;
    input input;
    char head[] = "NOKIYEM CELLULAR PHONE";
    int ans;
    do{
        header(strlen(head), head, "under");
        menu();
        do{
            printf("\n>> Input choice: ");
            scanf("%d", &ans);
            fflush(stdin);
            switch(ans){
                case 1:
                    add(&root, &input);
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
                    if(root != NULL)
                        order(root);
                    else{
                        printf("There is no data available");
                        getch();
                        clrscr;
                    }
                break;
                case 4:
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
    printf("1. Add New Phone\n");
    printf("2. Update Phone Price\n");
    printf("3. InOrder, PreOrder, PostOrder\n");
    printf("4. Exit\n");
}
int add(node **root, input *input){
    int status;
    _Bool flag, check_status;
    clrscr;
    /* This method using ASCII Values for parameters in if statement, input safety inspired by linux terminal when inputing password before sudo mode 
    And how I compare the input with my if statement, I compare the input based on Character based on ASCII Numbering, check https://www.asciitable.com/ 
    Simple explanation: Each char has it own ASCII Number, so you can compare based on ASCII, example in line 125, try to figure it out... thx */
    do{
        if(random_status == false){
            //Input Code
            do{
                printf("Input Phone Code N[1-9][0-9][0-9][0-9]: ");
                //First Array
                do{
                    input->code[0] = getch();
                    fflush(stdin);
                    if(input->code[0] == 'N'){
                        printf("%c", input->code[0]);
                        break;
                    }
                } while(1);
                //Second Array
                do{
                    input->code[1] = getch();
                    fflush(stdin);
                    if(input->code[1] >= '1' && input->code[1] <= '9'){
                        printf("%c", input->code[1]);
                        break;
                    }
                } while(1);
                //Third Array
                do{
                    input->code[2] = getch();
                    fflush(stdin);
                    if(input->code[2] >= '0'  && input->code[2] <= '9'){
                        printf("%c", input->code[2]);
                        break;
                    }
                } while(1);
                //Fourth Array
                do{
                    input->code[3] = getch();
                    fflush(stdin);
                    if(input->code[3] >= '0' && input->code[3] <= '9'){
                        printf("%c", input->code[3]);
                        break;
                    }
                } while(1);
                //Fifth Array
                do{
                    input->code[4] = getch();
                    fflush(stdin);
                    if(input->code[4] >= '0' && input->code[4] <= '9'){
                        printf("%c", input->code[4]);
                        flag = true;
                        break;
                    }
                } while(1);
                if(flag == true){
                    break;
                }
            } while(1);
            printf("\n\n");
            //Input Price
            do{
                printf("Input Phone Price [$50..$999]: $");
                scanf("%d", &input->price);
                fflush(stdin);
            } while(input->price < 50 || input->price > 999);
        } else{
            printf("Input Phone Code N[1-9][0-9][0-9][0-9]: ");
            randomCode(input);
            printf("\n\n");
            printf("Input Phone Price [$50..$999]: $");
            randomPrice(input);
        }
        //Debug
        //Check if Data is not exist in tree
        check_status = check(root, input);
        if(check_status == true){
            fprintf(stderr, "Error: Phone Code Already Exists...");
            sleep(1);
            continue;
        }
        else
            break;
    } while(1);
    printf("\n\n\n");
    /* Push */
    status = push(root, input);
    /********/
    if(status == SUCCESS)
        printf("--- Add New Phone Success ---");
    else if(status == FAILED)
        printf("--- Add New Phone Failure ---");
    getch();
    clrscr;
}
void randomCode(input *input){
    //Random code: min + rand() % (max+1 - min);
    char a[10] = "";
    srand(time(0));
    a[0] = 78; // 'N' (In ASCII Character)
    a[1] = 49 + rand() % (57 + 1 - 49); // 1 - 9 (In ASCII Character)
    a[2] = 48 + rand() % (57 + 1 - 48); // 0 - 9 (In ASCII Character)
    a[3] = 48 + rand() % (57 + 1 - 48); // 0 - 9 (In ASCII Character)
    a[4] = 48 + rand() % (57 + 1 - 48); // 0 - 9 (In ASCII Character)
    strcpy(input->code, a);
    printf("%s", input->code);
}
void randomPrice(input *input){
    //Random code: min + rand() % (max+1 - min);
    input->price = 50 + rand() % (999 + 1 - 50);
    printf("%d", input->price);
}
_Bool check(node **root, input *input){
    /* I compare the code data based on ASCII Numbering, check https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm */
    node *ptr = *root;
    while(1){
        if(ptr == NULL)
            return false;
        else if(strcmp(ptr->code, input->code) == 0)
            return true;
        else if(strcmp(ptr->code, input->code) < 0)
            ptr = ptr->left;
        else if(strcmp(ptr->code, input->code) > 0)
            ptr = ptr->right;
    }
}
int push(node **root, input *input){
    node *temp = (node *) malloc(sizeof(node));
    node *ptr;
    /* Scenario 1: If Memory didn't allocated */
    if(temp == NULL){
        perror("Error: ");
        sleep(2);
        return FAILED; //Return failed status
    }
    /* Scenario 2: If memory allocated */
    else{
        /* Insert data to new node and declare left and right leaf as NULL */
        strcpy(temp->code, input->code);
        temp->price = input->price;
        temp->left = NULL;
        temp->right = NULL;
        /* Looping for moving pointer, if node location established, return success status
        And to be noted: I compare the code data based on ASCII Numbering, check https://www.tutorialspoint.com/c_standard_library/c_function_strcmp.htm */
        while(1){
            /* Scenario 2.1: If there is no Node available */
            if(root == NULL){
                *root = temp; //Place root pointer to new node
                return SUCCESS; //Return success status
            } 
            /* Scenario 2.2: If there is node available */
            else{
                ptr = *root;
                /* Scenario 2.2.1: If code in temp is smaller than code in pointer location and left leaf is empty */
                if(strcmp(ptr->code, temp->code) < 0 && ptr->left == NULL){
                    ptr->left = temp;
                    return SUCCESS;
                } 
                /* Scenario 2.2.2: If code in temp is bigger than code in pointer location and right leaf is empty */
                else if(strcmp(ptr->code, temp->code) > 0 && ptr->right == NULL){
                    ptr->right = temp;
                    return SUCCESS;
                } 
                /* Scenario 2.2.3: If code in temp is smaller than code in pointer location and left leaf is not empty */
                else if(strcmp(ptr->code, temp->code) < 0 && ptr->left != NULL)
                    ptr = ptr->left;
                /* Scenario 2.2.4: If code in temp is bigger than code in pointer location and right leaf is not empty */
                else if(strcmp(ptr->code, temp->code) > 0 && ptr->right != NULL)
                    ptr = ptr->right;
            }
            
        }
    }
}
void order(node *root){
    clrscr;
    printf("Preorder :\n");
    preorder(root);
    printf("\n\n");
    printf("Inorder :\n");
    inorder(root);
    printf("\n\n");
    printf("Postorder :\n");
    postorder(root);
    getch();
    clrscr;
}
void preorder(node *tree){
    node *ptr = tree;
    if(ptr != NULL){
        printf("%s [ $ %d ]\n", ptr->code,  ptr->price);
        preorder(ptr->left);
        preorder(ptr->right);
    }
    return;
}
void inorder(node *tree){
    node *ptr = tree;
    if(ptr != NULL){
        inorder(ptr->left);
        printf("%s [ $ %d ]\n", ptr->code,  ptr->price);
        inorder(ptr->right);
    }
    return;
}
void postorder(node *tree){
    node *ptr = tree;
    if(ptr != NULL){
        postorder(ptr->left);
        postorder(ptr->right);
        printf("%s [ $ %d ]\n", ptr->code,  ptr->price);
    }
    return;
}
/*
    Note:
    The program didn't run as I expected
    In Push function seem there is a logic error, but I didn't found it
    And my check function for checking if input data not same as data
    Who already in node, is not working
    But when run the program, the Push function return success status
    and check function runs as normal, but its like just get bypassed
    Nothing happened...
    But when try to look the data, the root still in NULL condition
    Need someone to take a look at this...
*/