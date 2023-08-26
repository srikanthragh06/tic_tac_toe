#include "custom_exception.h"

// Constructor: Initializes the CustomException with a message, source file, and line number
CustomException::CustomException(const std::string& message, const char* file, int line)
    : message(message), file(file), line(line) {}

// Returns the exception message
const char* CustomException::what() const noexcept {
    return message.c_str();
}

// Returns the source file where the exception occurred
const char* CustomException::getFile() const {
    return file;
}

// Returns the line number where the exception occurred
int CustomException::getLine() const {
    return line;
}
