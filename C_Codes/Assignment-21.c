#include <stdio.h>
#include "colors.h"



struct employe_model {
	char first_name[20];
	char last_name[20];
	int id;
	int SSN;
	char title[20];
};


struct employe_list{
	struct employe_model employe[2];
}employees;

int main(void){

	for(int i=0; i< 2 ; i++){
		printf("Enter the employee's first name: ");
		scanf("%19s",&employees.employe[i].first_name);
		printf("Enter the employee's last name: ");
		scanf("%19s",&employees.employe[i].last_name);
		printf("Enter the employee's ID number: ");
		scanf("%3i",&employees.employe[i].id);
		printf("Enter the employee's 4 digits of SSN: ");
		scanf("%4i",&employees.employe[i].SSN);
		printf("Enter the employee's Job title : ");
		scanf("%19s",&employees.employe[i].title);
		printf("\n");

	}

	for(int i=0; i<2 ; i++){
		printf("Employee information for %s %s:\n",&employees.employe[i].first_name,&employees.employe[i].last_name);
		printf("ID: %d\nSSN: %d\nTitle:%s\n",employees.employe[i].id,employees.employe[i].SSN,&employees.employe[i].title);
	
	
	}

	return 0;
}
