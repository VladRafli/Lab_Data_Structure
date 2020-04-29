#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "uttils.h"

typedef struct Food_Order node; //Type Definition of struct Food_Order to node
typedef struct Input_Order input; //Type Definition of struct Input_Order to input
struct Food_Order{
    int no;
    char cust[30];
    char food[30];
    char addr[30];
    node *prev;
    node *next;
};

node *front, *rear = NULL; //Declare Pointer Front Node and Rear Node
struct Input_Order{
    int no;
    char cust[30];
    char food[30];
    char addr[30];
};

int node_length(){
    node *cur;
    int length = 0;
    if(front != NULL){
        length = 1;
        for(cur = front; cur->next != front; cur = cur->next)
            length++;
        return length;
    } else{
        return length;
    }
}
void menu();
void view_order(char *command);
void add_order();
void take_order();
int push(input *input);
int pop(int *order_num);

int main(int argc, char const *argv[])
{
    char text[] = "ACE FOOD DELIVERY";
    int ans;
    do
    {
        header(strlen(text), text, "under");
        menu();
        do{
            printf("\n>> Input Choice : ");
            scanf("%d", &ans);
            fflush(stdin);
            switch(ans){
                case 1:
                    view_order("view");
                    break;
                case 2:
                    add_order();
                    break;
                case 3:
                    take_order();
                    break;
                case 4:
                    return 0;
                default:
                    continue;
            }
            break;
        } while(1);
    } while (1);
}
void menu(){
    printf("1. View Order List\n");
    printf("2. Add New Order\n");
    printf("3. Take Order\n");
    printf("4. Exit\n");
}
void view_order(char *command){
    node *cur;
    clrscr;
    printf("\t\t  ");
    printf("--- ACE FOOD DELIVERY ORDER LIST ---");
    printf("\n\n");
    line(80);
    printf("\xBA%3s. \xBA%15s \xBA%16s     \xBA%25s        \xBA\n", "No", "Customer Name", "Food Order", "Delivery Address");
    line(80);
    if(front == NULL){
        printf("\t\t\t  No Data Available!\n");
    } else{
        for(cur = front; cur->next != front; cur = cur->next)
            printf("\xBA %2d. \xBA %-15s\xBA %-20s\xBA %-32s\xBA\n", cur->no, cur->cust, cur->food, cur->addr);
        printf("\xBA %2d. \xBA %-15s\xBA %-20s\xBA %-32s\xBA\n", cur->no, cur->cust, cur->food, cur->addr);
    }
    line(80);
    if(strcmp(command, "view") == 0){
        getch();
        clrscr;
        return;
    }
    printf("\n\n");
    return;
}
void add_order(){
    input input;
    int push_status;
    clrscr;
    do
    {
        printf("Input Customer Name [3..30]: ");
        gets(input.cust);
        fflush(stdin);
    } while (strlen(input.cust) < 3 || strlen(input.cust) > 30);
    printf("\n");
    do
    {
        printf("Input Food Order [3..20]: ");
        gets(input.food);
        fflush(stdin);
    } while (strlen(input.food) < 3 || strlen(input.food) > 20);
    printf("\n");
    do
    {
        printf("Input Delivery Address [6..30]: ");
        gets(input.addr);
        fflush(stdin);
    } while (strlen(input.addr) < 6 || strlen(input.addr) > 30);
    /*          Push        */
    push_status = push(&input);
    /************************/
    printf("\n\n");
    if(push_status == 0)
        printf("--- Add New Order Success ---");
    else
        printf("--- Add New Order Failed ---");
    getch();
    clrscr;
    return;
}
void take_order(){
    int a = 0;
    int b = node_length();
    int ans;
    if(b > 0){
        a = 1;
    }
    clrscr;
    view_order("");
    if(front != NULL){
        printf("Input Number of The Order [%d..%d]: ", a, b);
        scanf("%d", &ans);
        /* Pop */
        pop(&ans);
        /****/
    } else{
        printf("--- No Order to be Taken ---");
        getch();
        clrscr;
        return;
    }
    printf("--- Take Order Success ---");
    getch();
    clrscr;
    return;
}
/**
 Dobuly Circular Linked List
 **/
int push(input *input){
    node *new;
    new = (node *) malloc(sizeof(node));
    if(new == NULL){
        perror("Error: ");
        return 1;
    } else{
        /* Insert Data from Input to Node */
        new->no = node_length() + 1;
        strcpy(new->cust, input->cust);
        strcpy(new->food, input->food);
        strcpy(new->addr, input->addr);
        /* Node Connecting */
        /* Scenario 1: If No List Available */
        if(front == NULL){
            front = rear = new; //Set Pointer Front and Rear to New Node
            front->next = new; //Set Front Pointer Next to New Node
            front->prev = new; //Set Front Pointer Prev to New Node
        }
        /* Scenario 2: If List is Available */
        else{
            rear->next = new; //Point Rear Next to New Node
            new->next = front; //Point New Node Next to Front Node
            new->prev = rear; //Point New Node Prev to Rear Node
            rear = rear->next; //Move Pointer Rear to the Next Node
        }
        return 0;
    }
}

/* This code referencing to https://github.com/VladRafli/Lab_Data_Structure/blob/master/Lab%205/Lab_5.c with some edits*/

int pop(int *order_num){
    node *ptr = front; 
    node *preptr = front;
    node *temp;
    /* Scenario 1: If There is Just One Node */
    if(front->next == front){
        free(front); //Free Front Node Memory
        front = NULL; //Point Front to NULL
        rear = NULL; //Point Rear to NULL
    }
    /* Scenario 2: If There is More than One Node */
    else{
        //Move Pointer to Destination Node
        while(ptr->no != *order_num)
            ptr = ptr->next;
        //Move Pre-Pointer to Before Destination Node
        while(preptr->next != ptr)
            preptr = preptr->next;
        //Point Temp Pointer with Pointer for Numbering
        temp = ptr;
        /* Scenario 2.1: If Pointer At Front */
        if(ptr == front){
            temp = temp->next; //Move Temp Pointer to Next Node
            front = front->next; //Move Pointer Front to the Next Node
            ptr->prev->next = front; //Point Previous Next Pointer to Front Node
            ptr->next->prev = ptr->prev; //Point Next Node Previous Pointer to Node Previous to Pointer
            ptr->next = NULL; //Null Pointer Next
            ptr->prev = NULL; //Null Pointer Prev
            free(ptr); //Free Pointer Memory
            while(temp->next != front){
                if(temp->no != 1)
                    temp->no -= 1;
                temp = temp->next;
            }
            if(temp->no != 1)
                temp->no -= 1;
        }
        /* Scenario 2.2: If Pointer not In Front */
        else{
            temp = temp->next; //Move Temp Pointer to Next Node
            preptr->next = ptr->next; //Point Pre-Pointer Next to Next Node to Pointer
            ptr->next->prev = preptr; //Point Next Node to Pointer Previous to Pre-Pointer
            ptr->next = NULL; //Null Pointer Next
            ptr->prev = NULL; //Null Pointer Prev
            free(ptr); //Free Pointer Memory
            while(temp->next != front){
                if(temp->no != 1)
                    temp->no -= 1;
                temp = temp->next;
            }
            if(temp->no != 1)
                temp->no -= 1;
        }
    }
    return 0;
}