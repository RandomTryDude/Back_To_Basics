#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "colors.h"
#include <time.h>

#define MAX_CLIENTS 16



int client_number = 0;

struct clients_model{
	char *firstname;
	char *lastname;
	const char *message[16]; // max inbox of 16
	int count_message;
	float balance;
	int number;
	bool is_active;
};

struct client_list{
	struct clients_model client[16]; 
}clients_array;

void banner(void){
printf(
        "\n"
        "|===================================================|\n"
        "|               Welcome To our                      |\n"
        "|           Most honest banking system              |\n"
        "|===================================================|\n"
        "|               You don't trust us?                 |\n"
        "|                 Neither do we                     |\n"
        "|                                    RandomCorpBank |\n"
        "|===================================================|\n"
    );
}

void create_account(void) {
    if (client_number >= MAX_CLIENTS) {
        printf("Sorry, no more accounts can be created.\n");
        return;
    }

    struct clients_model *client = &clients_array.client[client_number];
    client->firstname = calloc(33, sizeof(char));
    client->lastname = calloc(33, sizeof(char));

    if (!client->firstname || !client->lastname) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    printf("Firstname: ");
    scanf("%32s",client->firstname);
    printf("Lastname: ");
    scanf("%32s",client->lastname);

    client->balance = rand() % 5000;
    client->number = client_number;
    client->is_active = true;

    client->count_message = 0;
    client->message[client->count_message++] = strdup("Welcome to RandomCorpBank! Account successfully created.");

    printf("Welcome %s %s! Your client number is: %d",
           client->firstname, client->lastname, client->number);

    client_number++;
}

int login(void) {
    int number = 0;
    
    printf(
        "\n"
        "|===================================================|\n"
        "|               We trust our clients                |\n"
        "|        To only login with their client number     |\n"
        "| 				     RandomCorpBank |\n"
        "|===================================================|\n"
    );
    
    printf("%sEnter your client number: %s",COLOR_GREEN,COLOR_RESET);
    scanf("%i", &number);

    // Validate that the client number is within range
    if (number < 0 || number >= client_number) {
        printf("%sClient doesn't exist, exiting.%s",COLOR_RED,COLOR_RESET);
        return -1;
    }

    // Proceed with login
    printf("Welcome, %s %s!\nYour balance is %.2f$",
           clients_array.client[number].firstname,
           clients_array.client[number].lastname,
           clients_array.client[number].balance);
    return number;
}

void deposit(int acc_number){
	int amount = 0 ;
	printf("Please enter the amount to deposit: ");
	scanf("%i",&amount);
	if(amount < 0){
		printf("%sinvalid amount%s",COLOR_RED,COLOR_RESET);
	}
	else{
		clients_array.client[acc_number].balance += amount;
		printf("%sYour new balance is: %.2f$%s",COLOR_GREEN,clients_array.client[acc_number].balance,COLOR_RESET);
	}
	
}	
void withdraw(int acc_number){
	int amount =0;
	
	printf("Please enter the amount to withdraw: ");
	scanf("%i" ,&amount);
	
	if(amount < 0){
		printf("%sinvalid amount%s",COLOR_RED,COLOR_RESET);
	}
	else if(clients_array.client[acc_number].balance - amount > 0){
		printf("%sYou have sucessfully withdrawed %d$%s",COLOR_GREEN,amount,COLOR_RESET);
		clients_array.client[acc_number].balance -= amount;	
	}
	else{
		printf("It seem you've tried to remove more than you own");
	}
	

}

void payment(int acc_number) {
    int amount = 0, dest = 0;
    char confirm[4];
    char reason[64] = ""; // Initialize with an empty string

    printf("Please enter the amount you wish to pay: ");
    scanf("%i", &amount);

    printf("Please enter the account number for the payment: ");
    scanf("%i", &dest);

    // Validate input for the destination account
    if (dest < 0 || dest >= MAX_CLIENTS || !clients_array.client[dest].is_active) {
        snprintf(reason, sizeof(reason), "Destination account %d does not exist or is inactive.", dest);
    } else if (amount <= 0) {
        snprintf(reason, sizeof(reason), "Invalid payment amount: %d.", amount);
    } else if (amount > clients_array.client[acc_number].balance) {
        snprintf(reason, sizeof(reason), "Insufficient balance for the payment.");
    } /*else if (clients_array.client[acc_number].number == dest){
    	snprintf(reason , sizeof(reason) , "You cannot pay yourself");
    }*/
    

    // If any validation failed, print reason and exit
    if (strlen(reason) > 0) {
        printf("%sPayment has been voided due to: %s%s", COLOR_RED, reason, COLOR_RESET);
        return;
    }

    // Confirm the transaction
    printf("%sDo you confirm paying %d to account %d (yes/no): %s", COLOR_RED, amount, dest, COLOR_RESET);
    scanf("%3s", confirm);

    if (strcasecmp(confirm, "yes") != 0) {
        printf("%sPayment cancelled by user.%s", COLOR_YELLOW, COLOR_RESET);
        return;
    }

    // Process the payment
    clients_array.client[acc_number].balance -= amount;
    clients_array.client[dest].balance += amount;
    
    char msg[128]; // Allocate a buffer for the message
snprintf(msg, sizeof(msg), "Client %s %s paid you %d$", clients_array.client[acc_number].firstname, clients_array.client[acc_number].lastname, amount);
clients_array.client[dest].message[clients_array.client[dest].count_message++] = strdup(msg);

    

    printf("%sPayment of %d$ to account %d completed successfully!%s", 
           COLOR_GREEN, amount, dest, COLOR_RESET);
}

void pending(int is_logged) {
    struct clients_model *client = &clients_array.client[is_logged];

    for (int i = 0; i < client->count_message; i++) {
        printf("Message %d:\n%s\n", i + 1, client->message[i]);
    }
}

void generate_client(void) {
    char *first_names[] = {"Alice", "Bob", "Charlie", "Diana", "Eve", "Frank", "Grace", "Hank", "Ivy", "Jack"};
    char *last_names[] = {"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Martinez", "Clark"};

    int r = rand() % 10;
    if(r < 3){ r += 5;}
    
    for (int i = 0; i < r; i++) {
        struct clients_model *client = &clients_array.client[i];
        client->firstname = strdup(first_names[rand() % 10]);
        client->lastname = strdup(last_names[rand() % 10]);
        client->balance = rand() % 15000;
        client->number = i;
        client->is_active = true;
        client->count_message = 0;
        client->message[client->count_message++] = strdup("Welcome to RandomCorpBank! Generated account.");

        printf("Account %d: %s %s with balance %.2f$ created.\n", client->number, client->firstname, client->lastname, client->balance);
        client_number++;
    }

 

printf("Account generated with success , press any character\n");


}

void cleanup() {
    for (int i = 0; i < client_number; i++) {
        free(clients_array.client[i].firstname);
        free(clients_array.client[i].lastname);
    }
} // to clean our malloc / calloc, cause the memory leak is insane :D

int main(void) {
	srand(time(NULL));
	int choice;
	int is_logged = -1; // use it to store the user number :D
	atexit(cleanup);
	system("clear");
	generate_client(); // make it seem like there's a few clients y
	getchar();
	
	while(true){
	int exit = 1;
	
	system("clear");
		banner();
		printf(
			"\n"
			"1: Create Account\n"
			"2: Login\n"
			
		);
		printf("Please enter your action(1-2) :");
   		scanf("%1i",&choice);
   		getchar(); // clear the input buffer from the \n generated by entering 1 or 2
   		switch(choice){
   		case 1:
   			create_account();
   			break;
   		case 2: 
   			is_logged = login();
   			break;
   		default:	
   			printf("Failed to understand");
   			break;
   		   		
   		};
   	getchar();
        if(is_logged >=0){
        	while(exit){
   		system("clear");
   		banner();
   		
   		printf(
		"\n"	
		"0: Pending notifications\n"	
		"1: Deposit\n"
		"2: Withdraw\n"
		"3: Payment\n"
		"4: Log_Off\n"
		);
	
   		printf("Please enter your action(1-5) :");
   		scanf("%1i",&choice);
   		getchar(); // same as before
   		switch(choice){
   		
   		case 0:
   			pending(is_logged);
   			break;
   		case 1:
   			deposit(is_logged);
   			break;
   		case 2:
   			withdraw(is_logged);
   			break;
   		case 3:
   			payment(is_logged);
   			break;
   		case 4:
   			exit = 0;
   			is_logged = -1;
   			printf("Logging off...\n");
   			sleep(3);
   			system("clear");
   			
   			break;
  
   		default:
   			printf("Choice misunderstood");
   			break;
	
   		}
   		if(exit == 1){
   		getchar();
   		printf("\nPress any character to continue");
		getchar();
		}
		}
   		   	
   	}
			
	}
	
   	
	
	system("clear");
	
	
	
    return 0;
}
