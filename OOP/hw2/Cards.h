/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 20.04.2016
*/
#ifndef CARDS_H
#define CARDS_H
#include <iostream>
#include <string.h>


enum outcome{Lose,Tie,Win};


class Base{
	friend class Score_List;
	friend class HetList;
	outcome result;
	Base *next;
	public:
		Base();
		virtual char get_abbr()=0;
		virtual void compare(Base*t)=0;
		void set_result(outcome);
		outcome get_result();
		~Base();
};

Base::Base(){
	next = NULL;
}

Base::~Base(){
}

void Base::set_result(outcome score){
	result = score;
}

outcome Base::get_result(){
	return result;
}

void Base::compare(Base*t){
	this->compare(t);
}

class Red: public Base{
	char abbr;
	public:
		Red(char);
		char get_abbr();
		void compare(Base*t);
		~Red();
};

Red::Red(char type){
	abbr = type;
}

Red::~Red(){}

void Red::compare(Base*t){
	char oppenent=t->get_abbr();
	if(oppenent == 'R'){
		set_result(Tie);
	}
	else if(oppenent == 'D'){
		set_result(Lose);
	}
	else if(oppenent == 'B'){
		set_result(Lose);
	}
	else if(oppenent == 'G'){
		set_result(Win);
	}
}

char Red::get_abbr(){
	return abbr;
}

class DarkRed: public Red{
	public:
		DarkRed(char);
		void compare(Base*);
		~DarkRed();
};

DarkRed::DarkRed(char type):Red(type){}
DarkRed::~DarkRed(){}

void DarkRed::compare(Base*t){
	char oppenent = t->get_abbr();
	if(oppenent == 'R'){
		set_result(Win);
	}
	else if(oppenent == 'D'){
		set_result(Tie);
	}
	else if(oppenent == 'B'){
		set_result(Win);
	}
	else if(oppenent == 'G'){
		set_result(Lose);
	}
}

class Blue: public Base{
	char abbr;
	public:
		Blue(char);
		char get_abbr();
		void compare(Base*t);
		~Blue();
};

Blue::Blue(char type){
	abbr = type;
}

Blue::~Blue(){}

void Blue::compare(Base*t){
	char oppenent=t->get_abbr();
	if(oppenent == 'R'){
		set_result(Win);
	}
	else if(oppenent == 'D'){
		set_result(Lose);
	}
	else if(oppenent == 'B'){
		set_result(Tie);
	}
	else if(oppenent == 'G'){
		set_result(Lose);
	}
}

char Blue::get_abbr(){
	return abbr;
}

class Green: public Base{
	char abbr;
	public:
		Green(char);
		char get_abbr();
		void compare(Base*t);
		~Green();
};

Green::Green(char type){
	abbr = type;
}

Green::~Green(){}

char Green::get_abbr(){
	return abbr;
}

void Green::compare(Base *t){
	char oppenent = t->get_abbr();
	if(oppenent == 'R'){
		set_result(Lose);
	}
	else if(oppenent == 'D'){
		set_result(Win);
	}
	else if(oppenent == 'B'){
		set_result(Win);
	}
	else if(oppenent == 'G'){
		set_result(Tie);
	}
}
#endif;