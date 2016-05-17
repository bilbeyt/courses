/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 29.10.2015
*/
#ifndef _WIN32
#define strnicmp strncasecmp
#endif
#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include "list.h"

using namespace std;

// creating list and opening files
void Customer_List::create(){

	head = NULL;
	filename = "input_file.txt";
	input = fopen(filename, "r");
	filename = "output_file.txt";
	output = freopen(filename, "w", stdout);		//cout redirection to the output file

}

//deleting list
void Customer_List::makeEmpty(){

	Customer *node;
	transaction_record *record;
	while(head){
		node = head;
		head = head->next;
		record = node->action;
		while(record){
			node->action = node->action->next;
			delete record;
			record = node->action;
		}
		delete node;
	}
}

//closing files and the list
void Customer_List::close(){

	makeEmpty();
	fclose(input);
	fclose(output);

}

//initialize and create new customer for the bank
Customer *Customer_List::create_node(char* name, char* surname, char type,int size, char *action[]){

	Customer *new_person;
	new_person = new Customer;
	int counter =0;
	new_person->name = new char[strlen(name)+1];
	new_person->surname = new char[strlen(surname)+1];
	strcpy(new_person->name, name);
	strcpy(new_person->surname, surname);
	new_person->type = type;
	new_person->next = NULL;
	new_person->action = NULL;
	transaction_record *new_record, *traverse, *tail;	
	while(action){                                //This while is used for creating all transactions according to the file

		if(counter == size)	break;
		new_record = new transaction_record;
		new_record->type = new char[strlen(action[counter])+1];
		strcpy(new_record->type, action[counter]);
		new_record->next = NULL;
		if(new_person->action == NULL){
			new_person->action = new_record;  
		}
		else{
			traverse = new_person->action;
			tail = new_person->action;
			while(traverse){
				tail = traverse;
				traverse = traverse->next;
			}
			if(traverse){
				tail->next = new_record;
				new_record->next = traverse;
			}
			else{
				tail->next = new_record;
			}
		}
		counter++;
		new_record = new_record->next;
	}
	new_person->num_of_transactions = size;
	return new_person;
}

//Created customers inserting to the list for waiting
void Customer_List::insert(Customer *person){
	
	Customer *toadd, *traverse, *tail;
	toadd = new Customer;
	*toadd = *person;
	toadd->next = NULL;

	// If the list is empty
	if(head == NULL){
		head = toadd;
		return;
	}
	// If head's type is N and current customer's type is P
	// Add to the beginning. Head is changing.
	if(head->type == 'N' && toadd->type == 'P'){
		toadd->next = head;
		head = toadd;
		return;
	}
	// If head's type is P and current customer's type is P
	// Adds to the end of the P type customers
	if(head->type == 'P' && toadd->type == 'P'){
		traverse = head;
		while(traverse->type == 'P'){
			tail = traverse;
			traverse = traverse->next;
		}
		if(traverse){
			tail->next = toadd;
			toadd->next = traverse;
		}
		else{
			tail->next = toadd;
		}
	}
	// If head's type is P and current customer's type is N
	// Pass all P type customers and adds to the end of the N type customers
	if(head->type == 'P' && toadd->type == 'N'){
		traverse = head;
		while(traverse->type == 'P' || traverse->type == 'N'){
			tail = traverse;
			traverse = traverse->next;
		}
		if(traverse){
			tail->next = toadd;
			toadd->next = traverse;
		}
		else{
			tail->next = toadd;
		}
	}
	// If head's type is N and current customer's type is N
	// Adds to the end
	if(head->type == 'N' && toadd->type == 'N'){
		traverse = head;
		while(traverse){
			tail = traverse;
			traverse = traverse->next;
		}
		if(traverse){
			tail->next = toadd;
			toadd->next = traverse;
		}
		else{
			tail->next = traverse;
		}
	}
	
}

//printing all customers
void Customer_List::print(){
	
	Customer *person;
	transaction_record *record;
	person = head;
	while(person){
		record = person->action;
		cout<<person->name<<" "<<person->surname<<" "<<person->type<<" ";
		while(record){
			cout<<record->type<<" ";
			record = record->next;
		}
		cout<<endl;
		person = person->next;
	}
}

void Customer_List::remove(char *name, char *surname, char type){

	Customer *traverse, *person, *tail;
	traverse = head;
	tail = head;

	//Searching for the given criterias
	while(traverse){
		if(strnicmp(traverse->name, name, strlen(name))==0 && strnicmp(traverse->surname, surname, strlen(surname))==0 && traverse->type == type){
			person = traverse;
			break;
		}
		tail = traverse;
		traverse = traverse->next;
	}
	transaction_record *record;
	
	//Firstly, deleting all transactions related to found person
	while(person->action){
		record = person->action;
		person->action = person->action->next;
		delete record;
	}
	cout<<person->name<<" "<<person->surname<<" is removed"<<endl;
	//Found person is taken out of the list
	tail->next = person->next;
	//Found person is deleted
	delete person;

}

bool Customer_List::search(char *name, char *surname){

	Customer *traverse;
	bool found = false;
	transaction_record *record;
	traverse = head;

	//Searching for criterias
	while(traverse){
		if(strnicmp(traverse->name, name, strlen(name))==0 && strnicmp(traverse->surname, surname, strlen(surname))==0){
			record = traverse->action;
			cout<<traverse->name<<" "<<traverse->surname<<" "<<traverse->type<<" ";
			while(record){
				cout<<record->type<<" ";
				record = record->next;
			}
			found = true;
		}
		traverse = traverse->next;
	}
	return found;
}
//Performing transactions according to the line in this case 'head'
void Customer_List::do_transaction(){

	Customer *person;
	person = head;
	transaction_record *record;
	//Deleting only first transaction for P type customers, and send him/her to the end of the P line
	if(person->type == 'P'){
		record = person->action;
		person->action = person->action->next;
		delete record;
		head = head->next;
		person->next = NULL;
		insert(person);
	}
	//Deleting all transaction if the customer type is N, and person is deleted
	else{
		while(person->action){
			record = person->action;
			person->action = person->action->next;
			delete record;
		}
		head = head->next;
		delete person;
	}
}
