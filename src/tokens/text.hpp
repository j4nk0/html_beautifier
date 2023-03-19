#ifndef TEXT_HPP
#define TEXT_HPP

#include <string>

#include "../token.hpp"

/** contains raw text content of html elements */

class Text : public Token
{
public:
    Text (size_t lineNr, const std::string & content)
    : Token (lineNr),
      m_content (content) {}
    
    virtual ~Text () {}
    virtual std::string str     (void) const;
    virtual std::string getName (void) const;
    
private:
    const std::string m_content;
    static const std::string name;
};

#endif /* TEXT_HPP */

