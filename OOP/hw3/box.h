/*
* @Author
* Student Name: Tolga Bilbey
* Student ID : 150130045
* Date: 8.05.2016
*/
#ifndef BOX_H
#define BOX_H
#include <iostream>

template<class Type>
class Box{
	Type *data;
	int size;
	int capacity;
	double maximumAllowedWeight;
	double weight;
	double length;
	double width;
	public:
		Box(double,double,double,double);
		Box();
		Box(const Box<Type> &);
		double calculate_weight();
		void add(Type&);
		void add(Type*,int);
		Type &operator[] (int);
		template <class U>
		friend std::ostream &operator<<(std::ostream &, Box<U> &);
		double get_width();
		double get_length();
		double get_weight();
		~Box();
};

#endif;