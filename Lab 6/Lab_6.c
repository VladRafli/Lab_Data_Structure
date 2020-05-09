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
#define MIN_INPUT 5
#define MAX_DATA 30
#define LINE_LENGTH 122

typedef struct Customer_Data node;
typedef struct Customer_Input input;
struct Customer_Data{
    char name[MAX_DATA];
    char addr[MAX_DATA];
    char city[MAX_DATA];
    unsigned long long phone;
    node *prev;
    node *next;
};
node *head = NULL;
struct Customer_Input{
    char name[MAX_DATA];
    char addr[MAX_DATA];
    char city[MAX_DATA];
    unsigned long long phone;
};

void view_node();
void add_node();
void push(input *input);
void pop();

int main(int argc, char const *argv[])
{
    int ans;
    char text[] = "DATABASE CUSTOMER";
    do{
        header(strlen(text), text, "under");
        printf("1. View Customer Database\n");
        printf("2. Add New Customer\n");
        printf("3. Exit\n");
        printf("\n");
        do{
            printf(">> Input Choice : ");
            scanf("%d", &ans);
            fflush(stdin);
            switch(ans){
                case 1:
                    view_node();
                    break; //Break Switch Case
                case 2:
                    add_node();
                    break; //Break Switch Case
                case 3:
                    //Pop everything
                    while(head != NULL)
                        pop();
                    //view_node(); //Check to Ensure the List Completely Wiped Out
                    return 0; //End Program
                default:
                    continue; //Continue the Second Do While Loop
            }
            break; //Break Second Do While Loop
        } while (1); //Infinite Loop
    } while (1); //Infinite Loop
}
void view_node(){
    node *cur = head;
    char text[] = "DATABASE CUSTOMER";
    int num = 1;
    clrscr;
    header(strlen(text), text, "block");
    line(LINE_LENGTH);
    printf("\xBA %-4s \xBA %-30s \xBA %-30s \xBA %-30s \xBA %-12s \xBA\n", "No.", "Company Name", "Address", "City", "Phone Number");
    line(LINE_LENGTH);
    if(head == NULL){
        printf("\xBA %-4s \xBA %-30s \xBA %-30s \xBA %-30s \xBA %-12s \xBA\n", "1.", "NULL", "NULL", "NULL", "NULL");
    } else{
        //To Reverse List Reading, we need to set the Current Pointer to the first node
        while(cur->prev != NULL)
            cur = cur->prev;
        //Print the result
        for(cur; cur != NULL; cur = cur->next)
            printf("\xBA %-3d. \xBA %-30s \xBA %-30s \xBA %-30s \xBA %-12d \xBA\n",num++ ,cur->name, cur->addr, cur->city, cur->phone);
    }
    line(LINE_LENGTH);
    getch();
    clrscr;
}
void add_node(){
    input input;
    clrscr;
    do{
        printf("Input Company Name [5..30]: ");
        gets(input.name);
        fflush(stdin);
    } while(strlen(input.name) < MIN_INPUT || strlen(input.name) > MAX_DATA);
    printf("\n");
    do{
        printf("Input Company Address [5..30]: ");
        gets(input.addr);
        fflush(stdin);
    } while(strlen(input.addr) < MIN_INPUT || strlen(input.addr) > MAX_DATA);
    printf("\n");
    do{
        printf("Input Company City [5..20]: ");
        gets(input.city);
        fflush(stdin);
    } while(strlen(input.city) < MIN_INPUT || strlen(input.city) > MAX_DATA);
    printf("\n");
    do{
        printf("Input Company Phone Number [6..12]: ");
        scanf("%d", &input.phone);
        fflush(stdin);
    } while(input.phone < 0 || input.phone > 999999999999);
    printf("\n");
    //Push Process
    push(&input);
    //End Of Process
    printf("--- Add New Customer Success ---");
    getch();
    clrscr;
}
/*
    Doubly Linked List
*/
void push(input *input){
    //Allocate Memory for New Node
    node *new = (node *) malloc(sizeof(node));
    //Assign Value to New Node
    strcpy(new->name, input->name);
    strcpy(new->addr, input->addr);
    strcpy(new->city, input->city);
    new->phone = input->phone;
    //Assign Pointer Next and Prev to NULL
    new->next = NULL;
    new->prev = NULL;
    //Scenario 1: If there is no list available
    if(head == NULL){
        head = new; //Assign Head to New Node
        return;
    }
    //Scenario 2: If there is a list at least one node
    else{
        head->next = new; //Point New Node with Head Next Pointer
        new->prev = head; //Point Head with New Node Prev Pointer
        head = head->next; //Move Head to Next Node
        return;
    }
}
void pop(){
    node *ptr = head; //Set Pointer to Head
    //Scenario 1: If there is no Node Previous to Head
    if(head->prev == NULL){
        free(ptr); //Free Pointer Memory or Head (Basically Same)
        head = NULL; //Set Head to NULL;
        return;
    }
    //Scenario 2: If there is Node Previous to Head
    else{
        head = head->prev; //Move Head to Previous Node
        head->next = NULL; //Cut Head Link to Next Node
        ptr->prev = NULL; //Cut Pointer Link to Previous Node
        free(ptr); //Free Pointer Memory
        return;
    }
}