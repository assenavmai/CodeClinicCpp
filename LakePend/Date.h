#ifndef _DATE_H
#define _DATE_H

#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>


class Date {
	int year, day, month;
public:
	Date();
	Date(int, int, int);
	Date(std::string, char);
	~Date();
	void setDay(int d);
	void setMonth(int m);
	void setYear(int yr);
	int getDay();
	int getMonth();
	int getYear();
};

Date::Date() {

	year = 2016;
	day = 01;
	month = 01;
}

Date::Date(int yyyy, int dd, int mm) {

	year = yyyy;
	day = dd;
	month = mm;
}

Date::Date(std::string str, char delim) {

	std::stringstream ss;
	std::string item;

	ss.str(str);

	getline(ss, item, delim);
	year = std::stoi(item);	
	getline(ss, item, delim);
	month = std::stoi(item);	
	getline(ss, item, delim);
	day = std::stoi(item);	
}

Date::~Date() {}

void Date::setDay(int d) {
	day = d;
}

void Date::setMonth(int m) {
	month = m;
}

void Date::setYear(int yr) {
	year = yr;
}

int Date::getDay() {
	return day;
}

int Date::getMonth() {
	return month;
}

int Date::getYear() {
	return year;
}



#endif