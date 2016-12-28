/** \file FileException.h
 * Contains the class that throws exceptions for files.
 */
#ifndef _FEXCEPTION_H
#define _FEXCEPTION_H

/*!  \class FileException
 * \brief Class to throw exceptions when the file cannot be opened.
 *
 * Details about FileException.
 */

/*! \fn st char * what() const throw()
 * \brief A member function.
 * \return a string containing the exception message
 */
class FileException: public std::exception {
	const char * message;
	FileException(){}

public: 
	FileException(const char * s) throw() : message(s){} //!< Throw modifer, used where you know you are not throwing an exception
	const char * what() const throw() { return message; }
};

#endif