/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 29.10.2015
*/
#include "transaction_record.h"
#include <string>


struct Customer{

	char *name,*surname;
	char type;
	int num_of_transactions;
	transaction_record *action;
	Customer *next;
};