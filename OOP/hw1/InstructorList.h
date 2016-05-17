/*

	Name: Tolga Bilbey
	Number: 150130045

*/
#ifndef _WIN32
#define strnicmp strncasecmp
#endif
#include "Instructor.h"
#include <string>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class InstructorList{
	int count,capacity;
	Instructor *list;
	public:
		InstructorList();
		InstructorList(int);
		~InstructorList();
		void add_instructor(Instructor &);
		void delete_instructor(string,string);
		int search_by_first_name(string);
		int search_by_last_name(string);
		int search_by_room_number(string);
		int search_by_telephone_number(string);
		void print_all();
};

InstructorList::InstructorList(){
	count = 0;
	capacity = 3;
	list = new Instructor[3];
}

InstructorList::InstructorList(int capacity){
	count=0;
	this->capacity = capacity;
	list = new Instructor[this->capacity];
}

InstructorList::~InstructorList(){
	delete[] list;
}

void InstructorList::add_instructor(Instructor &obj){
	if(count==capacity){
		capacity = capacity*2;
		InstructorList temp(capacity);
		temp.count = this->count;
		for(int i=0;i<count;i++){
			temp.list[i] = list[i];
		}
		delete []list;
		list = new Instructor[capacity];
		for(int i=0;i<count;i++){
			list[i].set_title(temp.list[i].get_title());
			list[i].set_first_name(temp.list[i].get_first_name());
			list[i].set_last_name(temp.list[i].get_last_name());
			list[i].set_telephone_number(temp.list[i].get_telephone_number());
			list[i].set_room_number(temp.list[i].get_room_number());
			list[i].set_email(temp.list[i].get_email());
			list[i].set_username(temp.list[i].get_username());
			list[i].set_courses(temp.list[i].get_courses());
		}
		
	}
	
	if(search_by_first_name(obj.get_first_name()) !=0 && search_by_last_name(obj.get_last_name()) != 0){
		cout<<"Can not be added"<<endl;
	}
	else{
		list[count].set_title(obj.get_title());
		list[count].set_first_name(obj.get_first_name());
		list[count].set_last_name(obj.get_last_name());
		list[count].set_telephone_number(obj.get_telephone_number());
		list[count].set_room_number(obj.get_room_number());
		list[count].set_email(obj.get_email());
		list[count].set_username(obj.get_username());
		list[count].set_courses(obj.get_courses());
		count++;
	}
}

void InstructorList::delete_instructor(string name, string surname){
	int index = -2;
	for(int i=0;i<count;i++){
		if(strnicmp(list[i].get_first_name().c_str(),name.c_str(),strlen(list[i].get_first_name().c_str()))==0 && strnicmp(list[i].get_last_name().c_str(),surname.c_str(),strlen(list[i].get_last_name().c_str()))==0){
			index = i;
			break;
		}
	}
	if(index==-2){
		cout<<"--------------------Record can not be found---------------------------"<<endl;
		return;
	}
	int counter = 0;
	InstructorList new_list(capacity);
	for(int i=0;i<count;i++){
		if(i == index){
			continue;
		}
		else{
			new_list.list[counter] = list[i];
			counter++;
		}
	}
	count--;
	delete[] list;
	list = new Instructor[capacity];
	for(int i=0;i<count;i++){
		list[i].set_title("");
		list[i].set_title(new_list.list[i].get_title());
		list[i].set_first_name(new_list.list[i].get_first_name());
		list[i].set_last_name(new_list.list[i].get_last_name());
		list[i].set_telephone_number(new_list.list[i].get_telephone_number());
		list[i].set_room_number(new_list.list[i].get_room_number());
		list[i].set_email(new_list.list[i].get_email());
		list[i].set_username(new_list.list[i].get_username());
		list[i].set_courses(new_list.list[i].get_courses());
	}
}

void InstructorList::print_all(){
	cout<<"----------List of all Instructors in Computer Engineering of ITU----------"<<endl;
	for(int i=0;i<count;i++){
		list[i].print_instructor();
		cout<<"--------------------------------------"<<endl;
	}
}

int InstructorList::search_by_first_name(string name){
	int counter=0;
	for(int i=0;i<count;i++){
		if(strnicmp(list[i].get_first_name().c_str(),name.c_str(),strlen(list[i].get_first_name().c_str()))==0){
			list[i].print_instructor();
			counter++;
		}
	}
	return counter;
}

int InstructorList::search_by_last_name(string surname){
	int counter=0;
	for(int i=0;i<count;i++){
		if(strnicmp(list[i].get_last_name().c_str(),surname.c_str(),strlen(list[i].get_last_name().c_str()))==0){
			list[i].print_instructor();
			counter++;
		}
	}
	return counter;
}

int InstructorList::search_by_room_number(string room){
	int counter=0;
	for(int i=0;i<count;i++){
		if(strnicmp(list[i].get_room_number().c_str(),room.c_str(),strlen(list[i].get_room_number().c_str()))==0){
			list[i].print_instructor();
			counter++;
		}
	}
	return counter;
}

int InstructorList::search_by_telephone_number(string telephone){
	int counter=0;
	for(int i=0;i<count;i++){
		if(strnicmp(list[i].get_telephone_number().c_str(),telephone.c_str(),strlen(list[i].get_telephone_number().c_str()))==0){
			list[i].print_instructor();
			counter++;
		}
	}
	return counter;
}

