/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 29.10.2015
*/
#include <stdio.h>
#include "customer_record.h"

struct Customer_List{

	FILE *input;
	FILE *output;
	char *filename;
	Customer *head;
	Customer * create_node(char*, char*, char, int, char*[]);
	void insert(Customer *);
	void remove(char*, char*, char);
	bool search(char*, char*);
	void do_transaction();
	void makeEmpty();
	void print();
	void create();
	void close();

};