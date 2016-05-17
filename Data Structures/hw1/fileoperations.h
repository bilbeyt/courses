/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 11.10.2015
*/

#ifndef FILEOPERATIONS_H
#define FILEOPERATIONS_H
#include <stdio.h>
#include "book_record.h"


struct File{
	
	char *filename;
	FILE *catalogue;
	void create();
	void close();
	void add(book_record *);
	int search_type(char []);
	int search_author(char []);
	int search_ISBN(int);
	void remove(int ISBN);
	void update(int ISBN, book_record *);
	void delete_handler();
	void print();

};


#endif