#pragma once
#include <stdexcept>
#include <string>

class CustomException : public std::exception {
public:
    // Constructor: Initializes the exception with a message, source file, and line number
    CustomException(const std::string& message, const char* file, int line);

    // Returns the exception message
    const char* what() const noexcept override;

    // Returns the source file where the exception occurred
    const char* getFile() const;

    // Returns the line number where the exception occurred
    int getLine() const;

private:
    std::string message; // The exception message
    const char* file;    // The source file where the exception occurred
    int line;            // The line number where the exception occurred
};

// Macro for throwing a CustomException with the given message, file, and line number
#define THROW_CUSTOM_EXCEPTION(msg) throw CustomException(msg, __FILE__, __LINE__)
