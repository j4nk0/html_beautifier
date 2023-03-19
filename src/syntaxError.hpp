#ifndef SYNTAXERROR_HPP
#define SYNTAXERROR_HPP

#include <string>

/**
 * Exception related to fatal error in html processing
 * which contains description of the error in what string.
 */

class SyntaxError
{
public:
    SyntaxError (const std::string & description = "")
    : what (description)
    {
    }
    const std::string what;
};

#endif /* SYNTAXERROR_HPP */

