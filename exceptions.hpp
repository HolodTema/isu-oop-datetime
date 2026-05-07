#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

class InvalidDateException : public std::exception {
public:

	const char * what() const noexcept override {
		return "Error: DateTime object has invalid date-time fields.";
	};
};
#endif