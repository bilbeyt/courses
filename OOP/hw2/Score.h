/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 20.04.2016
*/
#ifndef SCORE_H
#define SCORE_H
#include <iostream>
#include "Cards.h"
using namespace std;

class Number{
	friend class Score_List;
	friend class HetList;
	outcome num;
	Number *next;
	public:
		Number();
		~Number();
};

Number::Number(){
	next = NULL;
}

Number::~Number(){
	
}

class Score_List{
	Number *head;
	Number *back;
	int total_score,total_lose,total_tie,total_win;
	public:
		Score_List();
		~Score_List();
		void push(Number*);
		int get_total_score();
		int get_total_lose();
		int get_total_tie();
		int get_total_win();
		void calculate_totals();
		void print_totals();
		bool is_empty();
		void print();
};

Score_List::Score_List(){
	head = NULL;
	back = NULL;
	total_score = 0;
	total_tie = 0;
	total_lose = 0;
	total_win = 0;
}

Score_List::~Score_List(){
	Number *number;
	while(head){
		number = head;
		head = head->next;
		delete number;
	}
}

int Score_List::get_total_lose(){
	return total_lose;
}

int Score_List::get_total_tie(){
	return total_tie;
}

int Score_List::get_total_win(){
	return total_win;
}

int Score_List::get_total_score(){
	return total_score;
}

void Score_List::push(Number *num){
	if(is_empty()){
		head = num;
		back = head;
	}
	else{
		back->next = num;
		back = num;
	}
}

bool Score_List::is_empty(){
	return head==NULL;
}

void Score_List::print(){
	Number *number = head;
	while(number){
		cout<<number->num<<" ";
		number = number->next;
	}
}

void Score_List::calculate_totals(){
	Number *temp = head;
	while(temp){
		if(temp->num == Lose){
			total_lose++;
		}
		else if(temp->num == Tie){
			total_tie++;
			total_score++;
		}
		else if(temp->num == Win){
			total_win++;
			total_score += 2;
		}
		temp = temp->next;
	}
}

void Score_List::print_totals(){
	cout<<"Lose: "<<total_lose<<" Tie: "<<total_tie<<" Win: "<<total_win;
}

#endif;