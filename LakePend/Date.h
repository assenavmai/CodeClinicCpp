#ifndef _DATE_H
#define _DATE_H


class Date {
	int year, day, month;
public:
	Date();
	Date(int, int, int);
	~Date();
	
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

Date::~Date() {}
#endif