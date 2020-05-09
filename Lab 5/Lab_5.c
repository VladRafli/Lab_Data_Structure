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
#include <unistd.h>
#include <conio.h>
#include "uttils.h"
#define LINE_LEN 64

typedef struct Motorcycle_Parts node;
typedef struct Motorcycle_Input input;

struct Motorcycle_Parts{
    int key;
    char parts[30];
    int qty;
    long int price;
    node *next;
    node *prev;
};
node *front = NULL;
node *rear = NULL;
struct Motorcycle_Input{
    char parts[40];
    int qty;
    long int price;
};

int node_length(){
    int length = 0;
    node *cur;
    if(front == NULL)
        return length;
    else{
        length = 1;
        for(cur = front; cur->next != front; cur = cur->next){
            length++;
        }
        return length;
    }
}

void main_menu();
void view_order(char *__view_mode);
void add_order();
void take_order();
void enqueue(input *input);
void dequeue(int *ans);

int main(int argc, char const *argv[])
{
    main_menu();
    return 0;
}
void main_menu(){
    int ans;
    char head[] = "BLUE MOTORCYCLE PARTS";
    header(strlen(head), head, "under");
    printf("1. View Order List\n");
    printf("2. Add New Order\n");
    printf("3. Take Order\n");
    printf("4. Exit\n");
    printf("\n");
    do{
        printf(">> Input choice : ");
        scanf("%d", &ans);
        fflush(stdin);
        switch(ans){
            case 1:
                view_order("normal");
            case 2:
                add_order();
            case 3:
                take_order();
            case 4:
                while(node_length() != 0){
                    int list_length = node_length();
                    dequeue(&list_length);
                }
                exit(EXIT_SUCCESS);
            default:
                continue;
        }
    } while(1);
}
void view_order(char *__view_mode){
    int num = 1;
    node *cur;
    clrscr;
    line(LINE_LEN);
    printf("\xBA %-5s\xBA %-30s\xBA %-9s\xBA %-11s\xBA\n", "No.", "Name of Parts", "Quantity", "Unit Price");
    line(LINE_LEN);
    if(front == NULL){
        printf("\xBA %3d. \xBA %-29s \xBA %8d \xBA   %-8d \xBA\n", num++, "NULL", 0, 0);
    }
    else{
        for(cur = front; cur->next != front; cur = cur->next)
            printf("\xBA %3d. \xBA %-29s \xBA %8d \xBA   %-8d \xBA\n", num++, cur->parts, cur->qty, cur->price);
        printf("\xBA %3d. \xBA %-29s \xBA %8d \xBA   %-8d \xBA\n", num++, cur->parts, cur->qty, cur->price);
    }
    line(LINE_LEN);
    if(strcmp(__view_mode, "normal") == 0){
        getch();
        clrscr;
        main_menu();
    }
}
void add_order(){
    input input;
    clrscr;
    do{
        printf("Input Name of Motorcycle's Part [3..30]: ");
        gets(input.parts);
        fflush(stdin);
    } while(strlen(input.parts) < 3 || strlen(input.parts) > 30);
    printf("\n");
    do{
        printf("Input Quantity of The Motorcycle's Part [1..20]: ");
        scanf("%d", &input.qty);
        fflush(stdin);
    } while(input.qty < 1 || input.qty > 20);
    printf("\n");
    do{
        printf("Input Price of The Motorcycle's Part : ");
        scanf("%d", &input.price);
        fflush(stdin);
    } while(input.price < 1 || input.price > 99999999);
    printf("\n\n");
    //Enqueue
    enqueue(&input);
    //End of Enqueue
    printf("--- Add New Order Success ---");
    getch();
    clrscr;
    main_menu();
}
void take_order(){
    int ans;
    int list_length = node_length();
    clrscr;
    if(front == NULL){
        printf("--- There is No Order in The List ---");
        getch();
        clrscr;
        main_menu();
    }
    printf("\t\t\t\t--- Order List ---");
    printf("\n\n");
    view_order("view only");
    printf("\n\n");
    do{
        printf("Input Number of The Order [1..%d]: ", list_length);
        scanf("%d", &ans);
    } while(ans < 1 || ans > list_length);
    printf("\n\n");
    //Dequeue
    dequeue(&ans);
    //End of Dequeue
    printf("--- Take Order Success ---");
    getch();
    clrscr;
    main_menu();
}
/**
 Dobuly Circular Linked List (Should not be)
 **/
void enqueue(input *input){
    int key = node_length() + 1; //Variable for Node Keys
    //Allocate Memory for New Node
    node *new = (node *) malloc(sizeof(node));
    /* Input Data to New Node */
    new->key = key; //Key used for locating desired data at take order function
    strcpy(new->parts, input->parts);
    new->qty = input->qty;
    new->price = input->price;
    /* Next and Prev Pointers is NULL */
    new->next = NULL;
    new->prev = NULL;
    /* Scenario 1: If No List Available */
    if(front == NULL){
        front = new; //Point Front to New Node
        front->next = new; //Point Front Node Next to New Node
        front->prev = new; //Point Front Node Prev to New Node
        rear = front; //Point Rear Node to Front Node which is New Node
        return; //Return Function Result
    }
    /* Scenario 2: If List is Available */
    else{
        rear->next = new; //Point Rear Next to New Node
        new->next = front; //Point New Node Next to Front Node
        new->prev = rear; //Point New Node Prev to Rear Node
        rear = rear->next; //Move Pointer Rear to the Next Node
        return; //Return Function Result
    }
}
void dequeue(int *ans){
    node *ptr = front;
    node *preptr = front;
    /* Scenario 1: If There is Just One Node */
    if(front->next == front){
        free(front); //Free Front Node Memory
        front = NULL; //Point Front to NULL
        rear = NULL; //Point Rear to NULL
        return; //Return Function Result
    }
    /* Scenario 2: If There is More than One Node */
    else{
        //Move Pointer to Destination Node
        while(ptr->key != *ans)
            ptr = ptr->next;
        //Move Pre-Pointer to Before Destination Node
        while(preptr->next != ptr)
            preptr = preptr->next;
        /* Scenario 2.1: If Pointer At Front */
        if(ptr == front){
            front = front->next; //Move Pointer Front to the Next Node
            ptr->prev->next = front; //Point Previous Next Pointer to Front Node
            ptr->next->prev = ptr->prev; //Point Next Node Previous Pointer to Node Previous to Pointer
            ptr->next = NULL; //Null Pointer Next
            ptr->prev = NULL; //Null Pointer Prev
            free(ptr); //Free Pointer Memory
            return; //Return Function Result
        }
        /* Scenario 2.2: If Pointer not In Front */
        else{
            preptr->next = ptr->next; //Point Pre-Pointer Next to Next Node to Pointer
            ptr->next->prev = preptr; //Point Next Node to Pointer Previous to Pre-Pointer
            ptr->next = NULL; //Null Pointer Next
            ptr->prev = NULL; //Null Pointer Prev
            free(ptr); //Free Pointer Memory
            return; //Return Function Result
        }
    }
}