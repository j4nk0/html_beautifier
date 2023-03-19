#ifndef ENDTAG_HPP
#define ENDTAG_HPP

#include <string>

#include "../token.hpp"

/** 
 * Representation of all possible end tags.
 * Name of the EndTag is the same as name 
 * name of the start tag it closes.
 * IndentInfluence is always -1.
 * No EndTag shall have any attributes.
 */

class EndTag : public Token
{
public:    
    EndTag (size_t lineNr, const std::string & name)
    : Token (lineNr),
      m_name (name) {}
    virtual ~EndTag () {}
    
    virtual std::string str     (void) const;
    virtual std::string getName (void) const;
    virtual int indentInfluence (void) const;
    
private:
    const std::string m_name;
};

#endif /* ENDTAG_HPP */
