#ifndef TAG_HPP
#define TAG_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

#include "../token.hpp"

/**
 * Abstract class, takes care of instantiiation and
 * validation of tag attributes but only in tags with attributes.
 * Does not throw exceptions, but issues error messages to 
 * std::cerr when invalid attribute is found.
 */

class Tag : public Token
{
public:
    Tag (size_t lineNr, const std::vector <Attrib> & content)
    : Token (lineNr),
      m_content (content) {}
    
    virtual ~Tag () {}
    virtual std::string str     (void) const;
    virtual std::string getName (void) const = 0;
    
protected:
    /** attibute checks as valid if it is in globalAttributes or in given set */
    void checkAttributes (const std::vector <Attrib> & toCheck,
                          const std::unordered_set <std::string> & valid) const;
    const std::vector <Attrib> m_content;
    
private:        
    //static const std::string name;
    static const std::unordered_set <std::string> globalAttributes;
};

#endif /* TAG_HPP */

