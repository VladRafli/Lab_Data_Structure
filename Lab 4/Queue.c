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
#define line 80
#define DATA 3

typedef struct computer_detail node;
typedef struct input_detail input;

struct computer_detail{
    char name[30];
    char type[20];
    int qty;
    int price;
    node *next;
};

node *front = NULL;
node *rear = NULL;

struct input_detail{
    char name[30];
    char type[20];
    int qty;
    int price;
};

void clrscr(){
    system("cls");
}
void header(int textlen, char *text){
    puts(text);
    for(int i = 0; i < textlen; i++){
        printf("\xCD");
    }
    printf("\n");
}
bool item_cmp(char *type){
    char item [DATA][15] = {
        "processor",
        "graphic card",
        "memory"
    };
    int i, res;
    char cmp[20];
    strcpy(cmp, type);
    strlwr(cmp);
    for(i = 0; i < DATA; i++){
        res = strcmp(cmp, item[i]);
        if(res == 0)
            return true;
    }
    return false;
}

void main_menu();
void queue_list(const char *_command);
void push_item();
void pop_item();
void push(input *input);
void pop();

int main(int argc, const char **argv){
    sleep(2);
    main_menu();
    return 0;
}
void main_menu(){
    int ans;
    char text[] = "COOL COMPUTER ADMINISTRATOR";
    header(strlen(text), text);
    printf("1. Item List\n");
    printf("2. Add <PUSH> New Item\n");
    printf("3. Delete <POP> Recently Added Item\n");
    printf("4. Exit\n\n");
    do{
        printf(">> Input your Choice : ");
        scanf("%d", &ans);
        fflush(stdin);
        switch(ans){
            case 1:
                queue_list("view");
            case 2:
                push_item();
            case 3:
                pop_item();
            case 4:
                while(front != NULL)
                    pop();
                queue_list("exit");
            default:
                continue;
        }
    } while(1);
}
void queue_list(const char *_command){
    int i;
    int num = 1;
    node *cur;
    clrscr();
    printf("\t\t\t\t--- ITEM LIST ---");
    printf("\n\n");
    for(i = 0; i < line; i++){
        printf("\xCD");
    }
    printf("\n");
    printf("\xBA %-4s\xBA %-30s\xBA %-20s\xBA %-9s\xBA %-6s\xBA\n", "No.", "Name", "Type", "Quantity", "Price");
    for(i = 0; i < line; i++){
        printf("\xCD");
    }
    printf("\n");
    if(front == NULL){
        printf("\xBA %-4d\xBA %-30s\xBA %-20s\xBA %8d \xBA $ %-4d\xBA\n", 0, "NULL", "NULL", 0, 0);
    }
    else{
        for(cur = front; cur != NULL; cur = cur->next){
            printf("\xBA %-4d\xBA %-30s\xBA %-20s\xBA %8d \xBA $ %-4d\xBA\n", num++, cur->name, cur->type, cur->qty, cur->price);
        }
    }
    for(i = 0; i < line; i++){
        printf("\xCD");
    }
    if(strcmp(_command, "exit") == 0){
        getch();
        exit(EXIT_SUCCESS);
    }
    getch();
    clrscr();
    main_menu();
}
void push_item(){
    input ipt;
    bool status;
    clrscr();
    do{
        printf("Input Name of The New Item [3..20]: ");
        gets(ipt.name);
        fflush(stdin);
    } while(strlen(ipt.name) < 3 || strlen(ipt.name) > 30);
    printf("\n");
    do{
        printf("Input Type of The New Item [Processor/Graphic Card/Memory]: ");
        gets(ipt.type);
        fflush(stdin);
        status = item_cmp(ipt.type);
    } while(status == false);
    printf("\n");
    do{
        printf("Input Quantity of The New Item [1..20]: ");
        scanf("%d", &ipt.qty);
        fflush(stdin);
    } while(ipt.qty < 1 || ipt.qty > 20);
    printf("\n");
    do{
        printf("Input Price of The New Item [$1..$1000]: $");
        scanf("%d", &ipt.price);
    } while(ipt.price < 1 || ipt.price > 1000);
    printf("\n\n\n");
    push(&ipt);
    printf("--- Add New Item Success ---");
    getch();
    clrscr();
    main_menu();
}
void pop_item(){
    if(front == NULL){
        printf("\n");
        printf("There are no item available.");
        getch();
        clrscr();
        main_menu();
    }
    else{
        printf("\n");
        printf("The recently added item <%s - %s> is being deleted.", rear->name, rear->type);
        pop();
        getch();
        clrscr();
        main_menu();
    }
}
void push(input *input){
    node *new = (node *) malloc(sizeof(node));
    strcpy(new->name, input->name);
    strcpy(new->type, input->type);
    new->qty = input->qty;
    new->price = input->price;
    new->next = NULL;
    if(rear == NULL){
        front = new;
        rear = front;
    }
    else{
        rear->next = new;
        new = rear;
    }
}
void pop(){
    node *temp;
    if(front->next == NULL){
        free(front);
        front = NULL;
        rear = NULL;
    }
    else{
        while(temp->next != rear){
            temp = temp->next;
        }
        free(rear);
        rear = temp;
    }
}