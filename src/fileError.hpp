#ifndef FILEERROR_HPP
#define FILEERROR_HPP

#include <string>

/**
 * Exception related to file reading / writing error
 * which contains description of the error in what string.
 */

class FileError
{
public:
    FileError (const std::string & description = "")
    : what (description)
    {
    }
    const std::string what;
};

#endif /* FILEERROR_HPP */

