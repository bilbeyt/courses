/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 8.05.2016
*/
#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string.h>

using namespace std;

class Book{
	char label[150];
	double weight;
	double length;
	double width;
	public:
		Book(char[],double,double,double);
		Book();
		void print();
		~Book();
		char* get_label();
		friend ostream &operator <<(ostream &, Book &);
		double get_weight();
		double get_length();
		double get_width();
};

char* Book::get_label(){
	return label;
}

double Book::get_length(){
	return length;
}

double Book::get_width(){
	return width;
}

double Book::get_weight(){
	return weight;
}

ostream &operator<<(ostream &output, Book &obj){
	output<<"Book Label: "<<obj.label<<" # "<<obj.length<<"x"<<obj.width<<" "<<obj.weight<<"kg "<<endl;
	return output;
}

Book::Book(char label[],double weight,double length,double width){
	strcpy(this->label,label);
	this->weight = weight;
	this->length = length;
	this->width = width;
}

Book::Book(){
	strcpy(label, " ");
	weight=0;
	length=0;
	width=0;
}

Book::~Book(){

}
#endif;
