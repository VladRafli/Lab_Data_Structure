#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
//Batas Linked List 10
/********************
 * Data
 ********************/
struct item_node{
	char name[20];
	int stock;
	struct item_node *next;
};
struct item_node *head = NULL;
/********************
 * Functions
 ********************/
//Main Menu
int main_menu();
//Item Stock
void item_stock();
//Sell Latest Stock
void sell_stock();
//Push
void push(char *input, int *qty){
	struct item_node *new = (struct item_node*) malloc(sizeof(struct item_node));
	strcpy(new->name, input);
	new->stock = *qty;
	new->next = head;
	head = new;
}
//Pop
struct item_node *pop(){
	struct item_node *temp = head;
	head = head->next;
	return temp;
}
//Clear Screen
void clrscr(){
	system("cls");
}
//Check Stack Length
int stack_length(){
	struct item_node node;
	struct item_node *current;
	int len = 0;
	for(current = head; current != NULL; current = current->next){
		len++;
	}
	return len;
}
//View Stack
void view_stack(){
	struct item_node node;
	struct item_node *ptr = head;
	int length = stack_length();
	int i;
	printf("\tCD Stock <STACK>");
	printf("\n\n");
	if(length == 0){
		printf("\tNo Data...");
	}
	for(i = 0; i < length; i++){
		if(i == 0){
			printf("\t[ %-18s%-2s| %2d song<s> ] -> [top]\n", ptr->name, "CD",ptr->stock);
			ptr = ptr->next;
		}
		else{
			printf("\t[ %-18s%-2s| %2d song<s> ]\n", ptr->name, "CD",ptr->stock);
			ptr = ptr->next;
		}
	}
}
void header(int textlen, char *text){
	int i;
	puts(text);
	for(i = 0; i < textlen; i++)
		printf("_");
	printf("\n");
}
//Main Program
int main(int argv, const char *argc[]){
	main_menu();
	return 0;
}
//Main Menu
int main_menu(){
	char text[] = "JACKIE CD STOCK";
	int ans;
	header(strlen(text), text);
	printf("\n");
	view_stack();
	printf("\n\n");
	printf("Option :\n");
	printf("1. Stock of CD\n");
	printf("2. Sell a CD\n");
	printf("3. Exit\n\n");
	do{
		printf(">> Input Choice : ");
		scanf("%d", &ans);
		fflush(stdin);
		switch(ans){
		case 1:
			item_stock();
		case 2:
			sell_stock();
		case 3:
			exit(EXIT_SUCCESS);
		default:
			continue;
		}
	} while(1);
}
void item_stock(){
	struct item_node node;
	struct item_node *ptr = head;
	char input[10];
	int i, qty;
	int datalen = stack_length();
	clrscr();
	if(datalen > 10){
		printf("---The CD Storage is Full ---");
		sleep(2);
		clrscr();
		main_menu();
	}
	printf("Input CD Genre [");
	for(i = 0; i < datalen; i++){
		printf("%s/", ptr->name);
		ptr = ptr->next;
	}
	printf("] : ");
	scanf("%s", input);
	fflush(stdin);
	printf("\n\n");
	do{
		printf("Input the number of songs on the CD [5..12 song<s>]: ");
		scanf("%d", &qty);
		fflush(stdin);
	} while(qty < 5 || qty > 12);
	//Push Proccess
	push(input, &qty);
	//End of Proccess
	printf("\n\n\n");
	printf("--- Add CD Success ---");
	sleep(2);
	clrscr();
	main_menu();
}
void sell_stock(){
	int datalen = stack_length();
	clrscr();
	if(datalen == 0){
		printf("--- The CD Storage is Empty ---");
		sleep(2);
		clrscr();
		main_menu();
	}
	//Pop Proccess
	struct item_node *temp = pop();
	free(temp);
	//End of Proccess
	printf("--- Sell CD Success ---");
	sleep(2);
	clrscr();
	main_menu();
}