/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 11.10.2015
*/
#ifndef _WIN32
#define strnicmp strncasecmp
#endif
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <fstream>
#include <string>

#include "fileoperations.h"

using namespace std;


void File::add(book_record *ykptr){
	
	fseek(catalogue, 0, SEEK_END);
	fwrite(ykptr, sizeof(book_record), 1, catalogue);

}

void File::create(){
	
	filename = "catalogue.txt";
	catalogue = fopen(filename, "r+");
	if(!catalogue){
		if(!(catalogue = fopen(filename, "w+"))){
			cerr <<"File can not be opened"<<endl;
			exit(1);
		}
	}

}

void File::close(){
	
	fclose(catalogue);

}

int File::search_type(char word[]){
	
	book_record record;
	bool all=false;
	int count=0;
	int found=0;
	if(strcmp(word, "*") == 0){
		all = true;
	}
	fseek(catalogue, 0, SEEK_SET);
	cout<<"Book records are shown in the format"<<endl;
	cout<<"The format is {RECORD_NUM, NAME, SURNAME, TITLE, ISBN, LOCATION, TYPE}"<<endl;
	while(!feof(catalogue)){
		count++;
		fread(&record, sizeof(book_record), 1, catalogue);
		if(feof(catalogue)) break;
		if(!all && strnicmp(record.bookType, word, strlen(word)) != 0){
			continue;
		}
		cout<<count<<"."<<record.authorName<<", "<<record.authorSurname<<", "<<record.title<<", "<<record.ISBN<<", "<<record.location<<", "<<record.bookType<<endl;
		found++;
	}
	//if given input is '*' the program writes all book records, if not, program writes only the records whose type is 'word'
	//and returns the number of those records
	return found;

}

int File::search_author(char word[]){
	
	book_record record;
	bool all=false;
	int count=0;
	int found=0;
	if(strcmp(word,"*")==0)
			all=true;
	fseek(catalogue, 0, SEEK_SET);
	cout<<"Book records are shown in the format"<<endl;
	cout<<"The format is {RECORD_NUM, NAME, SURNAME, TITLE, ISBN, LOCATION, TYPE}"<<endl;
	while(!feof(catalogue)){
		count++;
		fread(&record, sizeof(book_record), 1, catalogue);
		if(feof(catalogue)) break;
		if(!all && strnicmp(record.authorName, word, strlen(word)) != 0){
			continue;
		}
		cout<<count<<"."<<record.authorName<<", "<<record.authorSurname<<", "<<record.title<<", "<<record.ISBN<<", "<<record.location<<", "<<record.bookType<<endl;
		found++;
	}
	//if given input is '*' the program writes all book records, if not, program writes only the records whose author is 'word'
	//and returns the number of those records
	return found;	

}

//This search function is useful for finding index of the book related to given ISBN
int File::search_ISBN(int isbn){
	
	book_record record;
	int found=0;
	fseek(catalogue, 0, SEEK_SET);
	while(!feof(catalogue)){
		fread(&record, sizeof(book_record), 1, catalogue);
		if(feof(catalogue)) break;
		if(record.ISBN != isbn){
			continue;
		}
		found++;
	}
	//Given 'isbn' is searched in the catalogue and number of found records returned
	return found;	

}

void File::update(int ISBN, book_record *ykptr){
	
	int index=0;
	book_record record;
	while(!feof(catalogue)){
		fread(&record, sizeof(book_record), 1, catalogue);
		if(record.ISBN != ISBN){
			index++;
			continue;
		}
		else if(record.ISBN == ISBN) break;
	}
	// Found the index of the book record in catalogue
	if(fseek(catalogue, sizeof(book_record)*(index), SEEK_SET)==0)
			fwrite(ykptr, sizeof(book_record), 1, catalogue);

}

void File::remove(int ISBN){
	
	int index=0;
	book_record record;
	fseek(catalogue, 0, SEEK_SET);
	while(!feof(catalogue)){
		fread(&record, sizeof(book_record), 1, catalogue);
		if(record.ISBN != ISBN){
			index++;
		}
		else if(record.ISBN == ISBN) break;
	}
	//The index of the book record found in the catalogue
	book_record empty_record = {"","","",0,0,""};
	if(fseek(catalogue, sizeof(book_record)*(index), SEEK_SET) == 0)
		fwrite(&empty_record, sizeof(book_record), 1, catalogue);

}

void File::print(){
	
	int count = 0;
	book_record record;
	fseek(catalogue, 0, SEEK_SET);
	cout<<"Book records are shown in the format"<<endl;
	cout<<"The format is {RECORD_NUM, NAME, SURNAME, TITLE, ISBN, LOCATION, TYPE}"<<endl;
	while(!feof(catalogue)){
		count++;
		fread(&record, sizeof(book_record), 1, catalogue);
		if(feof(catalogue)) break;
		cout<<count<<"."<<record.authorName<<", "<<record.authorSurname<<", "<<record.title<<", "<<record.ISBN<<", "<<record.location<<", "<<record.bookType<<endl;	
	}
	//Prints all the book records
	getchar();

}

//delete_handler function stabilize the program with removing blanks when the user remove a book, the function 
//responses that at the same time.(Without closing and reopenning the program)
void File::delete_handler(){

	FILE *temp;
	filename = "temp.txt";
	temp = fopen(filename, "w+");
	//Firstly, new temporary file is opened.
	book_record record;
	fseek(catalogue, 0, SEEK_SET);
	fseek(temp, 0, SEEK_SET);
	//Cursors in files are set in starting position.
	while(!feof(catalogue) && (fread(&record, sizeof(book_record), 1, catalogue) != 0)){
		if(feof(catalogue)) break;
		if(record.ISBN != 0 && record.location != 0){
			fseek(temp, 0, SEEK_END);
			fwrite(&record, sizeof(book_record), 1, temp);
		}
	}
	//Blank book records are removed by using while loop and if condition.
	fclose(temp);
	//Temporary file is closed.

	std::ifstream    inFile("temp.txt");
    std::ofstream    outFile("catalogue.txt");

    outFile << inFile.rdbuf();
	// The copy from temporary file to main file is completed.

}

