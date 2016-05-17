/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 29.10.2015
*/
#include <iostream>
#include <stdio.h>
#include <cstdio>
#include <string>
#include <string.h>
#include "list.h"
#include <stdlib.h>

//Getting all information
struct Information{
	char *name, *surname;
	char type;
	int number;
	char *action[100];
};

using namespace std;

char get_command(FILE *, int);
int get_line_number(FILE *);
Information* get_info(FILE *, int);
bool make_operations(char, int);
void add_customer(int);
void search_customer(int);
void remove_customer(int);
void process_transaction();
void print_customers();
void get_name_surname(int);

typedef Customer_List Datastructure;
Datastructure list;


int main(){

	list.create();				//List is created
	bool end = false;
	char choice;
	int counter = 1, line_number = get_line_number(list.input);
	while(!end && counter<line_number){
		choice = get_command(list.input, counter);	//Command is taken from input
		end = make_operations(choice, counter);		//Operating choice according to the line, line number is an extra ending statement
		counter++;
	}
	cout<<"Program exits"<<endl;
	list.close();
	return EXIT_SUCCESS;
}

bool make_operations(char choice, int line){

	bool finish = false;
	switch(choice){
		case 'A':case 'a':
			add_customer(line);
			cout<<endl;
			break;
		case 'S':case 's':
			search_customer(line);
			cout<<endl;
			break;
		case 'V':case 'v':
			process_transaction();
			cout<<endl;
			break;
		case 'R':case 'r':
			remove_customer(line);
			cout<<endl;
			break;
		case 'P':case 'p':
			print_customers();
			cout<<endl;
			break;
		case 'E':case 'e':
			finish = true;
			break;
		default:
			cout<<"Invalid command"<<endl;
			break;
	}

	return finish;
}

void add_customer(int line){

	Information *person;
	person = get_info(list.input, line);
	Customer* new_customer;
	//Creating new person
	new_customer = list.create_node(person->name, person->surname, person->type, person->number, person->action);
	//Inserting created person
	list.insert(new_customer);
	//Information is deleted
	delete person;
	cout<<"New customer is added"<<endl;

}

void search_customer(int line){

	Information *person;
	bool found;
	//Getting all information
	person = get_info(list.input, line);
	found = list.search(person->name, person->surname);
	if(found == false){
		cout<<person->name<<" "<<person->surname<<" can not be found"<<endl;
	}
	//Information is deleted
	delete person;
}

void process_transaction(){

	list.do_transaction();
	cout<<"Next transaction is processed"<<endl;

}

void remove_customer(int line){

	Information *person;
	person = get_info(list.input, line);
	list.remove(person->name, person->surname, person->type);
	//Deleting information
	delete person;
}

void print_customers(){

	list.print();

}

char get_command(FILE* file, int line){

	int line_start[500];
	char str[500];
	fseek(file, 0, SEEK_SET);
	line_start[0] = 0;
	int line_index = 1;
	//Finding all starting line characters and number of lines in input file
	while(!feof(file)){
		fgets(str, 500, file);
		if(feof(file)) break;
		line_start[line_index] = ftell(file);
		line_index++;
	}
	int count = 0, number;
	char command;
	string name, surname, type;
	char actions[100][500];
	int action_index = 0;
	//Getting proper information according to the line
	fseek(file, line_start[line-1], SEEK_SET);
	fgets(str, 500, file);
	char *token;
	token = strtok(str, ";");
	//Tokens are creating according to the deliminiter ';'
	while(token != NULL){
		if(count == 0){
			command = *token;
		}
		else if(count == 1){
			name.append(token);
		}
		else if(count == 2){
			surname.append(token);
		}
		else if(count == 3){
			type.append(token);
		}
		else if(count == 4){
			number = *token;
		}
		else{
			strcpy(actions[action_index], token);
			action_index++;
		}
		token = strtok(NULL, ";");
		count++;
	}
	return command;
}

//Getting total line number for switch choice statement
int get_line_number(FILE* file){

	int line_start[500];
	char str[500];
	fseek(file, 0, SEEK_SET);
	line_start[0] = 0;
	int line_index = 1;
	//Getting line starting characters number and total line number
	while(!feof(file)){
		fgets(str, 500, file);
		if(feof(file)) break;
		line_start[line_index] = ftell(file);
		line_index++;
	}
	return line_index;
}

//Getting all information per line 
Information *get_info(FILE* file, int line){

	int line_start[500];
	char str[500];
	fseek(file, 0, SEEK_SET);
	line_start[0] = 0;
	int line_index = 1;
	while(!feof(file)){
		fgets(str, 500, file);
		if(feof(file)) break;
		line_start[line_index] = ftell(file);
		line_index++;
	}
	int count = 0, number;
	char command, type;
	string name, surname;
	char actions[500][500];
	int action_index = 0;
	fseek(file, line_start[line-1], SEEK_SET);
	fgets(str, 500, file);
	char *token;
	token = strtok(str, ";");
	while(token != NULL){
		if(count == 0){
			command = *token;
		}
		else if(count == 1){
			name.append(token);
		}
		else if(count == 2){
			surname.append(token);
		}
		else if(count == 3){
			type = *token;
		}
		else if(count == 4){
			number = *token;
		}
		else{
			strcpy(actions[action_index], token);
			action_index++;
		}
		token = strtok(NULL, ";");
		count++;
	}
	//To return all of the value struct 'Information' is created at the top, and used here
	Information *new_info;
	new_info = new Information;
	new_info->name = new char[name.length()];
	new_info->surname = new char[surname.length()];
	strcpy(new_info->name, name.c_str());
	strcpy(new_info->surname, surname.c_str());
	// The line endings with '\n' ,so when printing without using endl, it creates new line. To get rid of it,
	new_info->surname[strcspn(new_info->surname, "\n")] = '\0';
	//is used
	new_info->type = type;
	new_info->number = action_index;
	for(int i=0;i<action_index;i++){
		// The line endings with '\n' ,so when printing without using endl, it creates new line. To get rid of it,
		actions[i][strcspn(actions[i], "\n")] = '\0';
		//is used
		new_info->action[i] = actions[i];
	}	

	return new_info;
}
