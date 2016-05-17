/*

	Name: Tolga Bilbey
	Number: 150130045

*/
#ifndef _WIN32
#define strnicmp strncasecmp
#endif
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include "InstructorList.h"

using namespace std;


class AddressBook{
	InstructorList list;
	public:
		AddressBook();
		void main();
		void print_menu();
		bool make_operations(int);
		void add_instructor();
		void delete_instructor();
		void search_by_first_name();
		void search_by_last_name();
		void search_by_telephone_number();
		void search_by_room_number();
		void print_all_instructors();
};

int get_number_of_courses(string);
char** get_courses_array(string);

AddressBook::AddressBook(){

	string Ins1_arr = "BLG212E";
	Instructor Ins1("Prof.Dr.", "Esref", "Adali", "02122853586", "4322", "adali", "adali@itu.edu.tr", get_courses_array(Ins1_arr));
	list.add_instructor(Ins1);
	string Ins2_arr = "MAT271E,BLG477E,BLG492,BLG492E";
	Instructor Ins2("Prof.Dr.", "Ulug", "Beyazit", "02122853591", "4308", "ulugbayazit", "ulugbayazit@itu.edu.tr", get_courses_array(Ins2_arr));
	list.add_instructor(Ins2);
	string Ins3_arr = "BLG322E,BLG468E";
	Instructor Ins3("Assoc.Prof.Dr.", "Feza", "Buzluca", "02122853502", "5310", "buzluca", "buzluca@itu.edu.tr", get_courses_array(Ins3_arr));
	list.add_instructor(Ins3);

}

void AddressBook::main(){

	bool end=false;
	int choice;
	while (!end) {
		print_menu();
		cout<<"Enter the number of operation you want to perform:"<<endl;
		cin >> choice;
		end = make_operations(choice);
	}
}

void AddressBook::print_menu(){
	system("clear");
	cout<<"1. Add a new instructor"<<endl;
	cout<<"2. Delete an instructor"<<endl;
	cout<<"3. List all instructors"<<endl;
	cout<<"4. Search by Name"<<endl;
	cout<<"5. Search by Surname"<<endl;
	cout<<"6. Search by Telephone Number"<<endl;
	cout<<"7. Search by Room Number"<<endl;
	cout<<"8. Exit"<<endl;
}

bool AddressBook::make_operations(int choice){
	bool end = false;
	switch(choice){
		case 1:
			add_instructor();
			break;
		case 2:
			delete_instructor();
			break;
		case 3:
			print_all_instructors();
			break;
		case 4:
			search_by_first_name();
			break;
		case 5:
			search_by_last_name();
			break;
		case 6:
			search_by_telephone_number();
			break;
		case 7:
			search_by_room_number();
			break;
		case 8:
			end = true;
			break;
		default:
			cout << "Error: You have made an invalid choice" << endl;
			cout << "Try again {1, 2, 3, 4, 5, 6, 7, 8} :" ;
			cin >> choice;
			end = make_operations(choice);
			break; 	
	}
	return end;
}

void AddressBook::add_instructor(){
	string title, first_name, last_name, telephone_number, room_number,username, email;
	string courses;
	cout<<"Enter Title:"<<endl;
	cin>>title;
	cout<<"Enter First Name:"<<endl;
	cin>>first_name;
	cout<<"Enter Last Name:"<<endl;
	cin>>last_name;
	cout<<"Enter Telephone Number:"<<endl;
	cin>>telephone_number;
	cout<<"Enter Room Number:"<<endl;
	cin>>room_number;
	cout<<"Enter User Name:"<<endl;
	cin>>username;
	cout<<"Enter Email:"<<endl;
	cin>>email;
	cout << "Enter Courses with commas for example BLG111,BLG112,BLG113" << endl;
	cin >> courses;
	Instructor new_instructor(title, first_name, last_name, telephone_number, room_number, username, email, get_courses_array(courses));
	list.add_instructor(new_instructor); 
}

int get_number_of_courses(string arr){
	char *course_arr;
	int counter=0;
	course_arr = new char[arr.length()+1];
	strcpy(course_arr, arr.c_str());
	char *token;
	token = strtok(course_arr, ",");
	if (token)	counter++;
	while (token){
		token = strtok(NULL, ",");
		if (token)	counter++;
	}
	delete[] course_arr;
	return counter;
}

char** get_courses_array(string arr){
	int number_of_rows = get_number_of_courses(arr);
	char **courses_arr;
	courses_arr = new char*[number_of_rows+1];
	for (int i = 0; i < number_of_rows+1; i++){
		courses_arr[i] = new char[7];
	}
	char *course_list = new char[arr.length()+1];
	strcpy(course_list, arr.c_str());
	char *token;
	int counter = 0;
	token = strtok(course_list, ",");
	if (token){
		strcpy(courses_arr[counter], token);
		counter++;
	}
	while (token){
		token = strtok(NULL, ",");
		if (token){
			strcpy(courses_arr[counter], token);
			counter++;
		}
	}
	strcpy(courses_arr[counter], "***");
	delete[] course_list;
	return courses_arr;

}

void AddressBook::delete_instructor(){
	string name,surname;
	cout<<"Enter the first name of the record to be deleted:"<<endl;
	cin>>name;
	cout<<"Enter the last name of the record to be deleted:"<<endl;
	cin>>surname;
	system("clear");
	cout<<"--------------------List before deletion-------------------"<<endl<<endl;
	list.print_all();
	getchar();
	list.delete_instructor(name,surname);
	cout<<endl<<"--------------------List after deletion-------------------"<<endl<<endl;
	list.print_all();
	getchar();
}

void AddressBook::print_all_instructors(){
	list.print_all();
	getchar();
	getchar();
}

void AddressBook::search_by_first_name(){
	string name;
	int found;
	cout<<"Enter the first name:"<<endl;
	cin>>name;
	cout<<"----------Search Results----------"<<endl;
	found=list.search_by_first_name(name);
	if(found == 0){
		cout<<"Record can not be found"<<endl;
	}
	getchar();
	getchar();
}

void AddressBook::search_by_last_name(){
	string surname;
	int found;
	cout<<"Enter the last name:"<<endl;
	cin>>surname;
	cout<<"----------Search Results----------"<<endl;
	found=list.search_by_last_name(surname);
	if(found == 0){
		cout<<"Record can not be found"<<endl;
	}
	getchar();
	getchar();
}

void AddressBook::search_by_telephone_number(){
	string telephone_number;
	int found;
	cout<<"Enter the telephone number:"<<endl;
	cin>>telephone_number;
	cout<<"----------Search Results----------"<<endl;
	found=list.search_by_telephone_number(telephone_number);
	if(found == 0){
		cout<<"Record can not be found"<<endl;
	}
	getchar();
	getchar();
}

void AddressBook::search_by_room_number(){
	string room;
	int found;
	cout<<"Enter the room number:"<<endl;
	cin>>room;
	cout<<"----------Search Results----------"<<endl;
	found = list.search_by_room_number(room);
	if(found == 0){
		cout<<"Record can not be found"<<endl;
	}
	getchar();
	getchar();
	
}

int main(){
	
	AddressBook address;
	address.main();
	return EXIT_SUCCESS;
}