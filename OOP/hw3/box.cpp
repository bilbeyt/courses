/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 8.05.2016
*/
#ifndef BOX_CPP
#define BOX_CPP
#include <iostream>
#include <typeinfo>
#include <string.h>
#include "box.h"
using namespace std;


template <class Type>
double Box<Type>::get_length(){
	return length;
}

template <class Type>
double Box<Type>::get_width(){
	return width;
}

template <class Type>
double Box<Type>::get_weight(){
	return weight;
}

template <class Type>
Box<Type>::Box(double weight,double length, double width, double maximumAllowedWeight){
	this->data = new Type[2];
	this->capacity = 3;
	this->size = 0;
	this->weight = weight;
	this->length = length;
	this->width = width;
	this->maximumAllowedWeight = maximumAllowedWeight;
}

template <class Type>
Box<Type>::Box(){
	this->data = new Type;
	this->capacity = 0;
	this->size = 0;
	this->weight = 0;
	this->length = 0;
	this->width = 0;
	this->maximumAllowedWeight = 0;
}

template <class Type>
Box<Type>::Box(const Box<Type> &obj){
	this->data = new Type[obj.capacity+1];
	this->capacity = obj.capacity;
	this->size = obj.size;
	this->weight = obj.weight;
	this->length = obj.length;
	this->width = obj.width;
	this->maximumAllowedWeight = obj.maximumAllowedWeight;
	if(obj.data){
		for(int i=0;i<obj.size;i++){
			this->data[i] = obj.data[i];
		}
	}
}

template <class Type>
void Box<Type>::add(Type &obj){
	if(calculate_weight() + obj.get_weight() > maximumAllowedWeight){
		throw "The total weight of the contained objects including the box may not exceed the maximum allowed weight for the box!";
	}
	else if((length<obj.get_length() && width<obj.get_length())){
		throw "The dimensions of the contained object should be equal or smaller than those of the box!";
	}
	else if((length<obj.get_width() && width<obj.get_width())){
		throw "The dimensions of the contained object should be equal or smaller than those of the box!";
	}
	if(size+1>capacity){
		capacity *= 2;
		Type *new_arr = new Type[capacity+1];
		for(int i=0;i<size;i++){
			new_arr[i] = data[i];
		}
		delete []data;
		data = new_arr;
	}
	data[size] = obj;

	size++;
}

template <class Type>
void Box<Type>::add(Type *obj,int length){
	for(int i=0;i<length;i++){
		try{
			add(obj[i]);
		}
		catch(const char* &err_msg){
			cout <<"### ERROR ###"<< err_msg << endl;
		}
	}	
}

template <class Type>
double Box<Type>::calculate_weight(){
	double sum = 0;
	for(int i=0;i<size;i++){
		sum += this->data[i].get_weight();
	}
	sum += this->weight;
	return sum;
}

template <class Type>
Box<Type>::~Box(){
	if(data[0].get_weight()>0){
	//	delete[]data;
	}
}

template<class Type>
Type &Box<Type>::operator[](int i){
	if(i>=size){
		throw " Index out of bounds!";
	}
	else 
		return this->data[i];
}

template <class Type>
std::ostream &operator<<(std::ostream &output, Box<Type>&obj){
	output<<"***** Box<"<<typeid(Type).name()<<"> *****"<<endl;
	output<<"Box item count:"<<obj.size<<endl;
	output<<"Size: "<<obj.length<<"x"<<obj.width<<" Box Weight:"<<obj.weight<<"kg Total/Maksimum Allowed Weight:"<<obj.calculate_weight()<<"kg/"<<obj.maximumAllowedWeight<<"kg"<<endl;
	output<<"Items:"<<endl;
	if(obj.data){
		for(int i=0;i<obj.size;i++){
			output<<i+1<<"."<<obj.data[i];
		}
	}
	output<<"********************"<<endl;
	return output;
}

#endif;
