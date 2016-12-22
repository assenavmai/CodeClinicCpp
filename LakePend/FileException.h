#ifndef _FEXCEPTION_H
#define _FEXCEPTION_H

class FileException: public std::exception {
	const char * message;
	FileException(){}

public: 
	//throw modifier: used where you know that you are not throwing an exception
	FileException(const char * s) throw() : message(s){}
	
	const char * what() const throw() { return message; }
};

#endif