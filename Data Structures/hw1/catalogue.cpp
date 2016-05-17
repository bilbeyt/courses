/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 11.10.2015
*/

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <ctype.h>
#include <string>

#include "fileoperations.h"

using namespace std;


typedef File DataStructure;
DataStructure catalogue;

void write_menu();
bool make_operation(char);
void search_by_author();
void search_by_type();
void add_book();
void update_book();
void delete_book();
// This function finds the number of digits of the given number
int find_length_of_number(int number){
	
	int length=1;
	while(number/10 > 0){    
        length++;
		number /= 10;
    }
	
	return length;

}

int main(){
	
	catalogue.create();
	bool finish = false;
	char choice;
	while(!finish){
		write_menu();
		cin >> choice;
		finish = make_operation(choice);
	}
	catalogue.close();
	
	return EXIT_SUCCESS;

}

void write_menu(){
	
	system("clear");
	cout<<endl<<endl;
	cout<<"Please select the operation to perform and enter the operation code"<<endl;
	cout<<"(P) Print the whole catalogue,"<<endl;
	cout<<"(A) Search the catalogue by author,"<<endl;
	cout<<"(T) Search the catalogue by type,"<<endl;
	cout<<"(I) Insert a new book record,"<<endl;
	cout<<"(U) Update an existing book record,"<<endl;
	cout<<"(R) Remove a book record,"<<endl;
	cout<<"(E) Exit the program."<<endl;
	cout<<"Your selection is:"<<endl;

}

bool make_operation(char choice){
	
	bool finish = false;
	switch(choice){
		case 'P': case 'p':
			catalogue.print();
			getchar();
			break;
		case 'A': case 'a':
			search_by_author();
			break;
		case 'T': case 't':
			search_by_type();
			break;
		case 'I': case 'i':
			add_book();
			break;
		case 'U': case 'u':
			update_book();
			break;
		case 'R': case 'r':
			delete_book();
			break;
		case 'E': case 'e':
			cout<<"Are you sure that you want to terminate the program? (E/H)"<<endl;
			cin>>choice;
			if(choice=='E' || choice == 'e')
				finish=true;
			break;
		default:
			cout<<"Error: You have made an invalid choice"<<endl;
			cout<<"Try again {P, A, T, I, U, R, E}"<<endl;
			cin>>choice;
			finish = make_operation(choice);
			break;
	}
	
	return finish;

}

void search_by_author(){
	
	char authorName[NAME_LENGTH];
	cout<< "Please enter the name of the author you want to search(press '*' for listing all):"<<endl;
	cin.ignore(1000, '\n');
	cin.getline(authorName, NAME_LENGTH);
	if(catalogue.search_author(authorName)==0){
		cout<<"Author can not be found"<<endl;
	}
	getchar();

}

void search_by_type(){
	
	char type[TYPE_LENGTH];
	cout<< "Please enter the type of the book you want to search(press '*' for listing all):"<<endl;
	cin.ignore(1000, '\n');
	cin.getline(type, TYPE_LENGTH);
	if(catalogue.search_type(type)==0){
		cout<<"Type can not be found"<<endl;
	}
	getchar();

}

void add_book(){
	
	book_record new_record;
	cout<<"Please enter the information of the book you want to save "<<endl;
	cout<<"Author Name: "<<endl;
	cin.ignore(1000, '\n');
	cin.getline(new_record.authorName, NAME_LENGTH);
	cout<<"Author Surname: "<<endl;
	cin.getline(new_record.authorSurname, SURNAME_LENGTH);
	cout<<"Title: "<<endl;
	cin.getline(new_record.title, TITLE_LENGTH);
	cout<<"ISBN: "<<endl;
	cin>>new_record.ISBN;
	while(catalogue.search_ISBN(new_record.ISBN) != 0){
		cout<<"This ISBN is being used. Please enter new one"<<endl;
		cin>>new_record.ISBN;
	}
	//checks if the ISBN is used or not 
	cout<<"Location: "<<endl;
	cin>>setw(4)>>new_record.location;
	while(find_length_of_number(new_record.location) != 4){
		cout<<"The input has not got length 4"<<endl;
		cout<<"Please enter new one"<<endl;
		cin>>setw(4)>>new_record.location;
	}
	//checks if the location has 4 digits
	cout<<"Book Type: "<<endl;
	cin.ignore(1000, '\n');
	cin.getline(new_record.bookType, TYPE_LENGTH);
	catalogue.add(&new_record);
	cout<<"Book has been added"<<endl;
	getchar();

}

void delete_book(){
	
	int record_isbn;
	int choice;
	catalogue.print();	//To see the ISBN of books in the catalogue
	cout << "Please enter the ISBN of the book you want to delete (Press -1 to exit without deletion):" << endl;
	cin>>record_isbn;
	if(record_isbn == -1) return;
	int number_of_book = catalogue.search_ISBN(record_isbn);
	if(number_of_book==0){
		cout << "Book can not be found" << endl;
	}
	else {
		
		cout << "Book has been found." << endl;
		cout << "To submit your choice please enter the ISBN again (Press -1 to exit without deletion): " ;
		cin >> choice;
		if(choice==-1) return;
		catalogue.remove(choice);
		cout << "Book has been deleted" <<endl;
		catalogue.delete_handler(); //To get rid of blank records delete_handler function is invoked.
	}
	getchar();
	getchar();

}

void update_book(){
	
	int record_isbn;
	int choice;
	catalogue.print();
	cout << "Please enter the ISBN of the book you want to update:" << endl;
	cin>>record_isbn;
	int number_of_book=catalogue.search_ISBN(record_isbn);
	if(number_of_book==0){
		cout << "Book can not be found" << endl;
	}
	else {
		if (number_of_book==1){
			cout << "Book has been found." << endl;
			cout << "Please enter the ISBN of the book if you want to update this contact (Press -1 to exit without updating)"<<endl;
		}
		else
			cout << "Please enter the ISBN of the book that you want to update (Press -1 to exit without updating): "<<endl;
		cin >> choice;
		if(choice==-1) return;
		book_record new_record;
		cout << "Please enter the up-to-date information" << endl;
		cout<<"Author Name: "<<endl;
		cin.ignore(1000, '\n');
		cin.getline(new_record.authorName, NAME_LENGTH);
		cout<<"Author Surname: "<<endl;
		cin.getline(new_record.authorSurname, SURNAME_LENGTH);
		cout<<"Title: "<<endl;
		cin.getline(new_record.title, TITLE_LENGTH);
		cout<<"ISBN: "<<endl;
		cin>>new_record.ISBN;
		while(catalogue.search_ISBN(new_record.ISBN) != 0){
			cout<<"This ISBN is being used. Please enter new one"<<endl;
			cin>>new_record.ISBN;
		}
		//check if the ISBN is used 
		cout<<"Location: "<<endl;
		cin>>setw(4)>>new_record.location;
		while(find_length_of_number(new_record.location) != 4){
			cout<<"The input has not got length 4"<<endl;
			cout<<"Please enter new one"<<endl;
			cin>>setw(4)>>new_record.location;
		}
		//checks if location has 4 digits
		cout<<"Book Type: "<<endl;
		cin.ignore(1000,'\n');
		cin.getline(new_record.bookType, TYPE_LENGTH);
		catalogue.update(number_of_book, &new_record);
		cout<<"Book has been updated"<<endl;
	}
	getchar();

}
