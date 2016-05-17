/*

	Name: Tolga Bilbey
	Number: 150130045

*/
#ifndef _WIN32
#define strnicmp strncasecmp
#endif
#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;


class Instructor{
	string title, first_name, last_name, telephone_number, room_number, username, email;
	char **courses;
	public:
		Instructor(string="",string="",string="",string="",string="",string="",string="",char** = NULL);
		Instructor(Instructor &);
		~Instructor();
		string get_title();
		string get_first_name();
		string get_last_name();
		string get_telephone_number();
		string get_room_number();
		string get_username();
		string get_email();
		char** get_courses();
		void set_title(string);
		void set_first_name(string);
		void set_last_name(string);
		void set_telephone_number(string);
		void set_room_number(string);
		void set_username(string);
		void set_email(string);
		void set_courses(char**);
		void print_instructor();
};

Instructor::Instructor(string title, string name, string surname, string telephone, string room, string username, string email,char **courses){
	set_title(title);
	set_first_name(name);
	set_last_name(surname);
	set_telephone_number(telephone);
	set_room_number(room);
	set_username(username);
	set_email(email);	
	set_courses(courses);
}

Instructor::Instructor(Instructor &obj){
	set_title(obj.title);
	set_first_name(obj.first_name);
	set_last_name(obj.last_name);
	set_telephone_number(obj.telephone_number);
	set_room_number(obj.room_number);
	set_username(obj.username);
	set_email(obj.email);	
}

Instructor::~Instructor(){
}

void Instructor::set_first_name(string name){
	this->first_name = name;
}

void Instructor::set_last_name(string surname){
	this->last_name = surname;
}

void Instructor::set_title(string title){
	this->title = title;
}

void Instructor::set_telephone_number(string telephone){
	this->telephone_number = telephone;
}

void Instructor::set_username(string username){
	this->username = username;
}

void Instructor::set_email(string email){
	this->email = email;
}

void Instructor::set_courses(char **courses_arr){
	if (courses_arr){
		courses = courses_arr;
	}
	else{
		courses = NULL;
	}
}

void Instructor::set_room_number(string room){
	this->room_number = room;
}


string Instructor::get_title(){
	return title;
}

string Instructor::get_first_name(){
	return first_name;
}

string Instructor::get_last_name(){
	return last_name;
}

string Instructor::get_telephone_number(){
	return telephone_number;
}

char** Instructor::get_courses(){
	if (courses){
		return courses;
	}
	else{
		return NULL;
	}
}

string Instructor::get_email(){
	return email;
}

string Instructor::get_room_number(){
	return room_number;
}

string Instructor::get_username(){
	return username;
}

void Instructor::print_instructor(){
	cout<<"Title: "<<get_title()<<endl;
	cout<<"Name: "<<get_first_name()<<endl;
	cout<<"Surname: "<<get_last_name()<<endl;
	cout<<"Telephone Number: "<<get_telephone_number()<<endl;
	cout<<"Room Number: "<<get_room_number()<<endl;
	cout<<"E Mail: "<<get_email()<<endl;
	cout<<"Courses: [";
	if (courses){
		int i = 0;
		while (courses[i]){
			if (strnicmp(courses[i], "***", strlen(courses[i])) == 0) break;
			if (strnicmp(courses[i+1], "***", strlen(courses[i+1])) == 0){
				cout << courses[i];
			}
			else{
				cout << courses[i] << ",";
			}
			i++;
		}
	}
	cout << "]" << endl;
}
