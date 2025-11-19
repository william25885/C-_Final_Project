#pragma once
#include <stdexcept>
#include <string>

class InvalidInputException : public std::runtime_error {
public:
	InvalidInputException(const std::string& message);
};

class OccupiedCellException : public std::runtime_error {
public:
	OccupiedCellException(const std::string& message);
};

class OutOfBoundsException : public std::runtime_error {
public:
	OutOfBoundsException(const std::string& message);
};

class InvalidCharacterException : public std::runtime_error {
public:
	InvalidCharacterException(const std::string& message);
};

class InvalidQuantityException : public std::runtime_error {
public:
	InvalidQuantityException(const std::string& message);
};

class InvalidLocationException : public std::runtime_error {
public:
	InvalidLocationException(const std::string& message);
};