#include"exception.h"

InvalidInputException::InvalidInputException(const std::string& message) : std::runtime_error(message) {}

OccupiedCellException::OccupiedCellException(const std::string& message) : std::runtime_error(message) {}

OutOfBoundsException::OutOfBoundsException(const std::string& message) : std::runtime_error(message) {}

InvalidCharacterException::InvalidCharacterException(const std::string& message) : std::runtime_error(message) {}

InvalidQuantityException::InvalidQuantityException(const std::string& message) : std::runtime_error(message) {}

InvalidLocationException::InvalidLocationException(const std::string& message) : std::runtime_error(message) {}