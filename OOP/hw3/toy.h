/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 8.05.2016
*/
#ifndef TOY_H
#define TOY_H
#include <iostream>
#include <string.h>

using namespace std;

class Toy{
	char label[150];
	double weight;
	double length;
	double width;
	bool containsBattery;
	public:
		Toy(char*,double,double,double,bool);
		Toy();
		void setContainsBattery(bool);
		void print();
		char* get_label();
		double get_weight();
		friend ostream &operator<<(ostream &, Toy &);
		double get_length();
		double get_width();
		bool get_containsBattery;
		~Toy();
};

char* Toy::get_label(){
	return label;
}

double Toy::get_length(){
	return length;
}

double Toy::get_width(){
	return width;
}

double Toy::get_weight(){
	return weight;
}

Toy::Toy(char label[],double weight,double length,double width,bool containsBattery){
	strcpy(this->label,label);
	this->weight = weight;
	this->length = length;
	this->width = width;
	this->containsBattery = containsBattery;
}

Toy::Toy(){
	strcpy(label, " ");
	weight=0;
	length=0;
	width=0;
	containsBattery=false;
}

void Toy::setContainsBattery(bool state){
	this->containsBattery = state;
}

ostream &operator<<(ostream &output, Toy &obj){
	output<<"Toy Label: "<<obj.label<<" # "<<obj.length<<"x"<<obj.width<<" "<<obj.weight<<"kg ";
	if(obj.containsBattery){
		output<<" Contains Battery"<<endl;
	}
	else{
		output<<" No Battery"<<endl;
	}
	return output;
}

Toy::~Toy(){

}
#endif;
