<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#define LIMIT 30
typedef struct printer_services node;
struct printer_services{
    char cust[LIMIT];
    char print[LIMIT];
    char type[LIMIT];
    char desc[LIMIT];
    node *next;
};
node *head = NULL;
struct cust_input{
    char cust[LIMIT];
    char print[LIMIT];
    char type[LIMIT];
    char desc[LIMIT];
};
void clrscr(){
    system("cls");
}
void header(int textlen, char *text){
    for(int i = 0; i < textlen + 4; i++)
        printf("\xCD");
    printf("\n");
    printf("\xBA %s \xBA", text);
    printf("\n");
    for(int i = 0; i < textlen + 4; i++)
        printf("\xCD");
    printf("\n");
}
bool brand_comp(char *input){
    char arr[3][10] = {"canon", "epson", "hp"};
    int res;
    *input = tolower(*input);
    for(int i = 0; i < 3; i++){
        res = strcmp(input, arr[i]);
        if(res == 0){
            return true;
        }
    }
    return false;
}
void recipt_print(){
    node *cur = head;
    printf("---------------------------------------------------------------------\n");
    printf("| Printer Service Malang                 Contact: +62 xxx-xxxx-xxxx |\n");
    printf("|                                                                   |\n");
    printf("|                                                                   |\n");
    printf("| Customer Name: %-51s|\n", cur->cust);
    printf("| Customer Printer\'s Brand: %-40s|\n", cur->print);
    printf("| Customer Printer\'s Type:  %-40s|\n", cur->type);
    printf("| Damaged Part: %-52s|\n", cur->desc);
    printf("|                                                                   |\n");
    printf("|                                                                   |\n");
    printf("|    Reciever                                           Engineer    |\n");
    printf("|                                                                   |\n");
    printf("| ______________                                     ______________ |\n");
    printf("|                                                                   |\n");
    printf("|                                                                   |\n");
    printf("| Thank you for servicing to our shop!                              |\n");
    printf("---------------------------------------------------------------------\n");
}
void main_menu();
void service_list();
void add_service();
void take_service();
void insert_data(struct cust_input *input);
void delete_data();
int main(int argc, char **argv){
    main_menu();
    return 0;
}
void main_menu(){
    int ans;
    char text[] = "PRINTER SERVICES";
    header(strlen(text), text);
    printf("\n");
    printf("1. Service List\n");
    printf("2. Add Service\n");
    printf("3. Take Service\n");
    printf("4. Exit\n");
    printf("\n");
    do{
        printf(">> Input your choice : ");
        scanf("%d", &ans);
        fflush(stdin);
        switch(ans){
            case 1:
                service_list();
            case 2:
                add_service();
            case 3:
                take_service();
            case 4:
                exit(EXIT_SUCCESS);
            default:
                continue;
        }
    } while(1);
}
void service_list(){
    clrscr();
    node *cur = head;
    int i;
    int num = 1;
    printf("\t\t\t\t--- Printer Services ---");
    printf("\n\n");
    for(i = 0; i < 106; i++){
        printf("\xCD");
    }
    printf("\n");
    printf("\xBA %-5s\xBA %-25s\xBA %-20s\xBA %-20s\xBA %-25s\xBA", "No.", "Customer Name", "Printer's Brand", "Type", "Damaged");
    printf("\n");
    for(i = 0; i < 106; i++){
        printf("\xCD");
    }
    //Data
    printf("\n");
    if(head != NULL){
        while(cur->next != head){
            printf("\xBA %3d. \xBA %-25s\xBA %-20s\xBA %-20s\xBA %-25s\xBA\n", num++, cur->cust, cur->print, cur->type, cur->desc);
        cur = cur->next;
        }
        printf("\xBA %3d. \xBA %-25s\xBA %-20s\xBA %-20s\xBA %-25s\xBA\n", num++, cur->cust, cur->print, cur->type, cur->desc);
    }
    for(i = 0; i < 106; i++){
        printf("\xCD");
    }
    getch();
    clrscr();
    main_menu();
}
void add_service(){
    clrscr();
    bool status;
    struct cust_input input;
    do
    {
        printf("Input Customer\'s Name: ");
        gets(input.cust);
        fflush(stdin);
    } while(strlen(input.cust) == 0 || strlen(input.cust) >= 25);
    printf("\n\n");
    do{
        //Fortunately, this section input not case sensitive, so no problem if your input all lowercase or uppercase or mix
        printf("Input Printer\'s Brand [Canon/Epson/HP]: ");
        scanf("%s", input.print);
        fflush(stdin);
        status = brand_comp(input.print);
    } while(status == false);
    printf("\n\n");
    do{
        printf("Input Printer\'s Type [4..20]: ");
        gets(input.type);
        fflush(stdin);
    } while(strlen(input.type) < 4 || strlen(input.type) > 20);
    printf("\n\n");
    do{
        printf("Input Damaged [5..30]: ");
        gets(input.desc);
        fflush(stdin);
    } while(strlen(input.desc) < 5 || strlen(input.desc) > 30);
    //Input data to list / Push Process
    insert_data(&input);
    printf("\n\n\n");
    printf("--- Add New Order Success ---");
    getch();
    clrscr();
    main_menu();
}
void take_service(){
    char ans;
    clrscr();
    if(head != NULL){
        recipt_print();
        do{
            printf("Have you finished this order? [y/n]: ");
            ans = getch();
            switch(ans){
                case 'y':
                    //Pop Process
                    delete_data();
                    printf("\n\nPrinter has been repaired");
                    getch();
                    clrscr();
                    main_menu();
                case 'n':
                    printf("\n\nFinish the order first!");
                    getch();
                    clrscr();
                    main_menu();
                default:
                    continue;
            }
        } while(1);
    }
    else{
        printf("There is no printer to repair");
        getch();
        clrscr();
        main_menu();
    }
}

void insert_data(struct cust_input *input){
    //Allocate Memory for new Node
    node *new = (node *) malloc(sizeof(node));
    node *ptr;
    //Insert Data to New Node
    strcpy(new->cust, input->cust);
    strcpy(new->print, input->print);
    strcpy(new->type, input->type);
    strcpy(new->desc, input->desc);
    //Initialize New Node Pointer Next to NULL
    new->next = NULL;
    //Node Connection
    //If Head is Empty, Create New List
    if(head == NULL){
        //Assign Pointer Head to New Node
        head = new;
        //assign Pointer Head Next to New Node (Circular Self)
        head->next = new;
    }
    //If List was Established
    else{
        //Assign Pointer to Head
        ptr = head;
        //Move Pointer At the End of List
        while(ptr->next != head)
            ptr = ptr->next;
        //Insert New Node to End of List
        ptr->next = new;
        //Link Last Node to Head
        new->next = head;
    }
}
void delete_data(){
    node *cur;
    node *temp;
    //If List was Established
    if(head->next != head){
        //Initialize Pointer Current to Head
        cur = head;
        //Initialize Pointer Temporary to Head (For Freeing Memory)
        temp = head;
        //Move Pointer Current to Tail
        while(cur->next != head){
            cur = cur->next;
        }
        //Assign Tail Next Pointer to Head Next Node
        cur->next = head->next;
        //Assign Head to Next Node
        head = head->next;
        //Free Node (Memory)
        free(temp);
    }
    //If List only have One Node
    else{
        //Empty Head Node
        head = NULL;
        //Free Node (Memory)
        free(head);
    }
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <conio.h>
#include <ctype.h>
#define LIMIT 30
typedef struct printer_services node;
struct printer_services{
    char cust[LIMIT];
    char print[LIMIT];
    char type[LIMIT];
    char desc[LIMIT];
    node *next;
};
node *head = NULL;
struct cust_input{
    char cust[LIMIT];
    char print[LIMIT];
    char type[LIMIT];
    char desc[LIMIT];
};
void clrscr(){
    system("cls");
}
void header(int textlen, char *text){
    for(int i = 0; i < textlen + 4; i++)
        printf("\xCD");
    printf("\n");
    printf("\xBA %s \xBA", text);
    printf("\n");
    for(int i = 0; i < textlen + 4; i++)
        printf("\xCD");
    printf("\n");
}
bool brand_comp(char *input){
    char arr[3][10] = {"canon", "epson", "hp"};
    int res;
    *input = tolower(*input);
    for(int i = 0; i < 3; i++){
        res = strcmp(input, arr[i]);
        if(res == 0){
            return true;
        }
    }
    return false;
}
void recipt_print(){
    node *cur = head;
    printf("---------------------------------------------------------------------\n");
    printf("| Printer Service Malang                 Contact: +62 xxx-xxxx-xxxx |\n");
    printf("|                                                                   |\n");
    printf("|                                                                   |\n");
    printf("| Customer Name: %-51s|\n", cur->cust);
    printf("| Customer Printer\'s Brand: %-40s|\n", cur->print);
    printf("| Customer Printer\'s Type:  %-40s|\n", cur->type);
    printf("| Damaged Part: %-52s|\n", cur->desc);
    printf("|                                                                   |\n");
    printf("|                                                                   |\n");
    printf("|    Reciever                                           Engineer    |\n");
    printf("|                                                                   |\n");
    printf("| ______________                                     ______________ |\n");
    printf("|                                                                   |\n");
    printf("|                                                                   |\n");
    printf("| Thank you for servicing to our shop!                              |\n");
    printf("---------------------------------------------------------------------\n");
}
void main_menu();
void service_list();
void add_service();
void take_service();
void insert_data(struct cust_input *input);
void delete_data();
int main(int argc, char **argv){
    main_menu();
    return 0;
}
void main_menu(){
    int ans;
    char text[] = "PRINTER SERVICES";
    header(strlen(text), text);
    printf("\n");
    printf("1. Service List\n");
    printf("2. Add Service\n");
    printf("3. Take Service\n");
    printf("4. Exit\n");
    printf("\n");
    do{
        printf(">> Input your choice : ");
        scanf("%d", &ans);
        fflush(stdin);
        switch(ans){
            case 1:
                service_list();
            case 2:
                add_service();
            case 3:
                take_service();
            case 4:
                exit(EXIT_SUCCESS);
            default:
                continue;
        }
    } while(1);
}
void service_list(){
    clrscr();
    node *cur = head;
    int i;
    int num = 1;
    printf("\t\t\t\t--- Printer Services ---");
    printf("\n\n");
    for(i = 0; i < 106; i++){
        printf("\xCD");
    }
    printf("\n");
    printf("\xBA %-5s\xBA %-25s\xBA %-20s\xBA %-20s\xBA %-25s\xBA", "No.", "Customer Name", "Printer's Brand", "Type", "Damaged");
    printf("\n");
    for(i = 0; i < 106; i++){
        printf("\xCD");
    }
    //Data
    printf("\n");
    if(head != NULL){
        while(cur->next != head){
            printf("\xBA %3d. \xBA %-25s\xBA %-20s\xBA %-20s\xBA %-25s\xBA\n", num++, cur->cust, cur->print, cur->type, cur->desc);
        cur = cur->next;
        }
        printf("\xBA %3d. \xBA %-25s\xBA %-20s\xBA %-20s\xBA %-25s\xBA\n", num++, cur->cust, cur->print, cur->type, cur->desc);
    }
    for(i = 0; i < 106; i++){
        printf("\xCD");
    }
    getch();
    clrscr();
    main_menu();
}
void add_service(){
    clrscr();
    bool status;
    struct cust_input input;
    do
    {
        printf("Input Customer\'s Name: ");
        gets(input.cust);
        fflush(stdin);
    } while(strlen(input.cust) == 0 || strlen(input.cust) >= 25);
    printf("\n\n");
    do{
        //Fortunately, this section input not case sensitive, so no problem if your input all lowercase or uppercase or mix
        printf("Input Printer\'s Brand [Canon/Epson/HP]: ");
        scanf("%s", input.print);
        fflush(stdin);
        status = brand_comp(input.print);
    } while(status == false);
    printf("\n\n");
    do{
        printf("Input Printer\'s Type [4..20]: ");
        gets(input.type);
        fflush(stdin);
    } while(strlen(input.type) < 4 || strlen(input.type) > 20);
    printf("\n\n");
    do{
        printf("Input Damaged [5..30]: ");
        gets(input.desc);
        fflush(stdin);
    } while(strlen(input.desc) < 5 || strlen(input.desc) > 30);
    //Input data to list / Push Process
    insert_data(&input);
    printf("\n\n\n");
    printf("--- Add New Order Success ---");
    getch();
    clrscr();
    main_menu();
}
void take_service(){
    char ans;
    clrscr();
    if(head != NULL){
        recipt_print();
        do{
            printf("Have you finished this order? [y/n]: ");
            ans = getch();
            switch(ans){
                case 'y':
                    //Pop Process
                    delete_data();
                    printf("\n\nPrinter has been repaired");
                    getch();
                    clrscr();
                    main_menu();
                case 'n':
                    printf("\n\nFinish the order first!");
                    getch();
                    clrscr();
                    main_menu();
                default:
                    continue;
            }
        } while(1);
    }
    else{
        printf("There is no printer to repair");
        getch();
        clrscr();
        main_menu();
    }
}

void insert_data(struct cust_input *input){
    //Allocate Memory for new Node
    node *new = (node *) malloc(sizeof(node));
    node *ptr;
    //Insert Data to New Node
    strcpy(new->cust, input->cust);
    strcpy(new->print, input->print);
    strcpy(new->type, input->type);
    strcpy(new->desc, input->desc);
    //Initialize New Node Pointer Next to NULL
    new->next = NULL;
    //Node Connection
    //If Head is Empty, Create New List
    if(head == NULL){
        //Assign Pointer Head to New Node
        head = new;
        //assign Pointer Head Next to New Node (Circular Self)
        head->next = new;
    }
    //If List was Established
    else{
        //Assign Pointer to Head
        ptr = head;
        //Move Pointer At the End of List
        while(ptr->next != head)
            ptr = ptr->next;
        //Insert New Node to End of List
        ptr->next = new;
        //Link Last Node to Head
        new->next = head;
    }
}
void delete_data(){
    node *cur;
    node *temp;
    //If List was Established
    if(head->next != head){
        //Initialize Pointer Current to Head
        cur = head;
        //Initialize Pointer Temporary to Head (For Freeing Memory)
        temp = head;
        //Move Pointer Current to Tail
        while(cur->next != head){
            cur = cur->next;
        }
        //Assign Tail Next Pointer to Head Next Node
        cur->next = head->next;
        //Assign Head to Next Node
        head = head->next;
        //Free Node (Memory)
        free(temp);
    }
    //If List only have One Node
    else{
        //Empty Head Node
        head = NULL;
        //Free Node (Memory)
        free(head);
    }
}
>>>>>>> 1385834671422780531e4d5ec5ba4129c4fca5d7
