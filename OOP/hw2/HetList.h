/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 20.04.2016
*/
#ifndef HETLIST_H
#define HETLIST_H
#include "Cards.h"
#include "Score.h"

class HetList{
	Base *head;
	public:
		HetList();
		void insert(Base*);
		Base* get_head();
		void pop();
		bool is_empty();
		void calculate_points(HetList&, Score_List&);
		void print();
		~HetList();
};

HetList::HetList(){
	head = NULL;
}

bool HetList::is_empty(){
	return head==NULL;
}

void HetList::insert(Base* ptr){
	if(is_empty()){
		head = ptr;
	}
	else{
		ptr->next = head;
		head = ptr;
	}
}

void HetList::pop(){
	Base* item = head;
	head = head->next;
	delete item;
}

HetList::~HetList(){
	while(head){
		Base *traverse = head;
		head = head->next;
		delete traverse;
	}
}

void HetList::print(){
	Base *traverse = head;
	while(traverse){
		cout<<traverse->get_abbr()<<" ";
		traverse = traverse->next;
	}
}

void HetList::calculate_points(HetList &list, Score_List &scores){
	Base *other = list.head;
	Base *traverse = head;
	while(other && traverse){
		traverse->compare(other);
		Number *number = new Number;
		number->num = traverse->result;
		scores.push(number);
		other = other->next;
		traverse = traverse->next;
	}
}
#endif;