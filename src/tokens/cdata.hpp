#ifndef CDATA_HPP
#define CDATA_HPP

#include <string>

#include "../token.hpp"

/** Contains <![CDATA[...]]>
 * Because they wouldnt fil elsewhere
 */
class Cdata : public Token
{
public:
    Cdata (size_t lineNr, const std::string & content)
    : Token (lineNr),
      m_content (content) {}
    
    virtual ~Cdata () {}
    virtual std::string str     (void) const;
    virtual std::string getName    (void) const;
    
private:
    const std::string m_content;
    static const std::string name;
};

#endif /* CDATA_HPP */

