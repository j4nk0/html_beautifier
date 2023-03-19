#ifndef COMMENT_HPP
#define COMMENT_HPP

#include <string>

#include "../token.hpp"

/** Contains "<!--" comment "-->"
 */
class Comment : public Token
{
public:
    Comment (size_t lineNr, const std::string & content)
    : Token (lineNr),
      m_content (content) {}
    
    virtual ~Comment () {}
    virtual std::string str     (void) const;
    virtual std::string getName (void) const;
    
private:
    const std::string m_content;
    static const std::string name;
};

#endif /* COMMENT_HPP */

