#ifndef FILEMISSINGEXCEPTION_H_INCLUDED
#define FILEMISSINGEXCEPTION_H_INCLUDED

#include <exception>

class FileMissingException : public std::exception
{
public:
	/*destructor for FileMissingException*/
	FileMissingException();

	/*destructor for FileMissingException*/
	virtual ~FileMissingException();

	const char* what() noexcept;
};

#endif