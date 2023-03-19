#ifndef UNKNOWN_HPP
#define UNKNOWN_HPP

#include <string>

#include "../token.hpp"

/** Represents non-html / not implemented / 
 * Foreign elements and also doctype
 * Has elements that cannot be validated,
 * possibly contains nonsense
 */
class Unknown : public Token
{
public:
    Unknown (size_t lineNr, const std::string & content)
    : Token (lineNr),
      m_content (content) {}
    
    virtual ~Unknown () {}
    virtual std::string str     (void) const;
    virtual std::string getName (void) const;
    
private:
    const std::string m_content;
    static const std::string name;
};

#endif /* UNKNOWN_HPP */

