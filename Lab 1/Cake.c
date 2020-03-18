<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define MAX_CODE 6
#define MAX_NAME 30
#define MAX_CAKE 6
/*********************
 * Struct & Global Variables
 *********************/
struct cake_details{
	char cake_code[MAX_CODE];
	char cake_name[MAX_NAME];
	int stock;
	int price;
};
struct cake_details cake[MAX_CAKE] = {
	{"CK001", "Blueberry Cake", 13, 25000},
	{"CK009", "Chocochip Cake", 5, 20000},
	{"CK017", "Mayonaise Cake", 24, 30000},
	{"CK023", "Strawberry ShortCake", 7, 17500}
};
struct cake_details cake[MAX_CAKE];
int index_data = 4;
char head[] = "BLUE CAKE SHOP CASHIER";
/*********************
 * Functions
 *********************/
//Search
int search(char *input){
	int i;
	for(i = 0; i < index_data; i++){
		if(strcmp(cake[i].cake_code, input) == 0){
			return i;
		}
	}
	return -1;
}
void clrscr()
{
	system("cls");
}
void line(int length){
	for(int i = 0; i < length; i++){
		printf("-");
	}
}
void header(int textlen, char *text){
	puts(text);
	for(int i = 0; i < textlen; i++){
		printf("=");
	}
	printf("\n\n");
}
//Show Data
void show_data(){
	int no = 0;
	printf("%-4s| %-10s| %-21s| %-10s| %s\n", "No.", "Cake Code", "Cake Name", "Available", "Price");
	line(63);
	printf("\n");
	if(strcmp(cake[0].cake_code, "") == 0){
		printf("No Data\n");
	}
	else{
		for(int i = 0; i < index_data; i++){
		printf("%-0.2d. | %-10s| %-21s|%10d | Rp. %-5d,-\n", ++no, cake[i].cake_code, cake[i].cake_name, cake[i].stock, cake[i].price);
		}	
	}
	line(63);
	printf("\n\n");
}
/*********************
 * Function Prototypes
 *********************/
//Main Menu
void main_menu();
//Sell Menu
void sell_menu();
//Add Stock Menu
void add_stock_menu();
/*********************
 * Main Code
 *********************/
//Main Program
int main(int argv, const char *argc[]){
	main_menu();
	return 0;
}
//Main Menu
void main_menu(){
	int ans;
	header(strlen(head), head);
	show_data();
	printf("1. Sell\n");
	printf("2. Add Stock\n");
	printf("3. Exit\n");
	do{
		printf("Answer: ");
		scanf("%d", &ans);
		fflush(stdin);
		switch(ans)
		{
			case 1:
				sell_menu();
			case 2:
				add_stock_menu();
			case 3:
				exit(EXIT_SUCCESS);
			default:
				continue;
		}
	}while(1);
}
//Sell Menu
void sell_menu(){
	int i, res, ans;
	long int pay;
	char input[MAX_CODE];
	clrscr();
	header(strlen(head), head);
	show_data();
	printf("Input Cake Code [5 chars]: ");
	scanf("%s", input);
	fflush(stdin);
	res = search(input);
	if(res == -1){
		printf("Data not Found!");
		sleep(1);
		clrscr();
		main_menu();
	}
	else if(cake[res].stock == 0){
		printf("#Error 2: Insufficient Stock");
		sleep(2);
		clrscr();
		main_menu();
	}
	do{
		printf("Input Quantity [0..%d]: ", cake[res].stock);
		scanf("%d", &ans);
		fflush(stdin);
		if (ans == 0)
		{
			printf("#Warning 1: You can't enter zero quantity\n");
		}
	}while(ans < 0 || ans > cake[res].stock || ans == 0);
	cake[res].stock -= ans;
	printf("\n\n");
	printf("Total Price is : Rp. %d,- x %d = Rp. %d,-\n\n", cake[res].price, ans, cake[res].price * ans);
	do
	{
		printf("Your Payment: ");
		scanf("%d", &pay);
		printf("\n");
		if (pay < cake[res].price * ans)
		{
			printf("#Warning 2: You can't pay less than the price\n");
			sleep(1);
			continue;
		}
		printf("Return: %d", pay - (cake[res].price * ans));
		break;
	}while (1);
	printf("\n\n");
	printf("--- Thank You ---");
	sleep(2);
	clrscr();
	main_menu();
}
//Add Stock Menu
void add_stock_menu(){
	int i, res, ans;
	char input[MAX_CODE];
	clrscr();
	header(strlen(head), head);
	show_data();
	printf("Input Cake Code [5 chars]: ");
	scanf("%s", input);
	fflush(stdin);
	res = search(input);
	if(res == -1){
		printf("Data not Found!");
		sleep(1);
		clrscr();
		main_menu();
	}
	if (cake[res].stock == INT_MAX)
	{
		printf("#Error 1: Integer maximum value reached. System cannot store more number...");
		sleep(2);
		clrscr();
		main_menu();
	}
	do
	{
		printf("Input Quantity [1..%d]: ", INT_MAX - cake[res].stock);
		scanf("%d", &ans);
		fflush(stdin);
	}while (ans < 0 || ans == 0 || ans > INT_MAX - cake[res].stock);
	cake[res].stock += ans;
	printf("\n\n");
	printf("--- Adding Stock Success ---");
	sleep(2);
	clrscr();
	main_menu();
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define MAX_CODE 6
#define MAX_NAME 30
#define MAX_CAKE 6
/*********************
 * Struct & Global Variables
 *********************/
struct cake_details{
	char cake_code[MAX_CODE];
	char cake_name[MAX_NAME];
	int stock;
	int price;
};
struct cake_details cake[MAX_CAKE] = {
	{"CK001", "Blueberry Cake", 13, 25000},
	{"CK009", "Chocochip Cake", 5, 20000},
	{"CK017", "Mayonaise Cake", 24, 30000},
	{"CK023", "Strawberry ShortCake", 7, 17500}
};
struct cake_details cake[MAX_CAKE];
int index_data = 4;
char head[] = "BLUE CAKE SHOP CASHIER";
/*********************
 * Functions
 *********************/
//Search
int search(char *input){
	int i;
	for(i = 0; i < index_data; i++){
		if(strcmp(cake[i].cake_code, input) == 0){
			return i;
		}
	}
	return -1;
}
void clrscr()
{
	system("cls");
}
void line(int length){
	for(int i = 0; i < length; i++){
		printf("-");
	}
}
void header(int textlen, char *text){
	puts(text);
	for(int i = 0; i < textlen; i++){
		printf("=");
	}
	printf("\n\n");
}
//Show Data
void show_data(){
	int no = 0;
	printf("%-4s| %-10s| %-21s| %-10s| %s\n", "No.", "Cake Code", "Cake Name", "Available", "Price");
	line(63);
	printf("\n");
	if(strcmp(cake[0].cake_code, "") == 0){
		printf("No Data\n");
	}
	else{
		for(int i = 0; i < index_data; i++){
		printf("%-0.2d. | %-10s| %-21s|%10d | Rp. %-5d,-\n", ++no, cake[i].cake_code, cake[i].cake_name, cake[i].stock, cake[i].price);
		}	
	}
	line(63);
	printf("\n\n");
}
/*********************
 * Function Prototypes
 *********************/
//Main Menu
void main_menu();
//Sell Menu
void sell_menu();
//Add Stock Menu
void add_stock_menu();
/*********************
 * Main Code
 *********************/
//Main Program
int main(int argv, const char *argc[]){
	main_menu();
	return 0;
}
//Main Menu
void main_menu(){
	int ans;
	header(strlen(head), head);
	show_data();
	printf("1. Sell\n");
	printf("2. Add Stock\n");
	printf("3. Exit\n");
	do{
		printf("Answer: ");
		scanf("%d", &ans);
		fflush(stdin);
		switch(ans)
		{
			case 1:
				sell_menu();
			case 2:
				add_stock_menu();
			case 3:
				exit(EXIT_SUCCESS);
			default:
				continue;
		}
	}while(1);
}
//Sell Menu
void sell_menu(){
	int i, res, ans;
	long int pay;
	char input[MAX_CODE];
	clrscr();
	header(strlen(head), head);
	show_data();
	printf("Input Cake Code [5 chars]: ");
	scanf("%s", input);
	fflush(stdin);
	res = search(input);
	if(res == -1){
		printf("Data not Found!");
		sleep(1);
		clrscr();
		main_menu();
	}
	else if(cake[res].stock == 0){
		printf("#Error 2: Insufficient Stock");
		sleep(2);
		clrscr();
		main_menu();
	}
	do{
		printf("Input Quantity [0..%d]: ", cake[res].stock);
		scanf("%d", &ans);
		fflush(stdin);
		if (ans == 0)
		{
			printf("#Warning 1: You can't enter zero quantity\n");
		}
	}while(ans < 0 || ans > cake[res].stock || ans == 0);
	cake[res].stock -= ans;
	printf("\n\n");
	printf("Total Price is : Rp. %d,- x %d = Rp. %d,-\n\n", cake[res].price, ans, cake[res].price * ans);
	do
	{
		printf("Your Payment: ");
		scanf("%d", &pay);
		printf("\n");
		if (pay < cake[res].price * ans)
		{
			printf("#Warning 2: You can't pay less than the price\n");
			sleep(1);
			continue;
		}
		printf("Return: %d", pay - (cake[res].price * ans));
		break;
	}while (1);
	printf("\n\n");
	printf("--- Thank You ---");
	sleep(2);
	clrscr();
	main_menu();
}
//Add Stock Menu
void add_stock_menu(){
	int i, res, ans;
	char input[MAX_CODE];
	clrscr();
	header(strlen(head), head);
	show_data();
	printf("Input Cake Code [5 chars]: ");
	scanf("%s", input);
	fflush(stdin);
	res = search(input);
	if(res == -1){
		printf("Data not Found!");
		sleep(1);
		clrscr();
		main_menu();
	}
	if (cake[res].stock == INT_MAX)
	{
		printf("#Error 1: Integer maximum value reached. System cannot store more number...");
		sleep(2);
		clrscr();
		main_menu();
	}
	do
	{
		printf("Input Quantity [1..%d]: ", INT_MAX - cake[res].stock);
		scanf("%d", &ans);
		fflush(stdin);
	}while (ans < 0 || ans == 0 || ans > INT_MAX - cake[res].stock);
	cake[res].stock += ans;
	printf("\n\n");
	printf("--- Adding Stock Success ---");
	sleep(2);
	clrscr();
	main_menu();
>>>>>>> 1385834671422780531e4d5ec5ba4129c4fca5d7
}