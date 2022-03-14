#include <iostream>
#include "FileMissingException.h"

FileMissingException::FileMissingException() {};

FileMissingException::~FileMissingException() {};

const char* FileMissingException::what() noexcept
{
	return "Error: couldn't load file ";
}
