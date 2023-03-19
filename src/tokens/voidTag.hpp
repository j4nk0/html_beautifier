#ifndef VOIDTAG_HPP
#define VOIDTAG_HPP

#include <string>
#include <locale>
#include <unordered_set>
#include <unordered_map>

#include "tag.hpp"

/** 
 * Represents void Elements in html
 * Class changes str - the way string representation
 * of void tag looks with self-closing "/>" html tag.
 * Also sets indentInfluence to 0, which is redundant
 * since indentInfluence is not overridden in Tag and set to 0 in Token.
 * Instance of this class can represent any one of VOID elements:
 * area, base, br, col, embed, hr, img, input, keygen,
 * link, meta, param, source, track, wbr
 * Class contains static set of valid attibutes for each element, 
 * except glogal attributes, which are member in Tag which takes 
 * care of validation.
 */

class VoidTag : public Tag
{
public:
    VoidTag (size_t lineNr,
             const std::string & name,
             const std::vector <Attrib> & content);
    
    virtual ~VoidTag () {}
    virtual std::string str     (void) const;
    virtual std::string getName (void) const;
    virtual int indentInfluence (void) const;

private:
    const std::string m_name;
    static const std::unordered_map <std::string, 
            std::unordered_set <std::string> const * > validAttribs;

    static const std::unordered_set <std::string> areaAttribs;
    static const std::unordered_set <std::string> baseAttribs;
    static const std::unordered_set <std::string> brAttribs;
    static const std::unordered_set <std::string> colAttribs;
    static const std::unordered_set <std::string> embedAttribs;
    static const std::unordered_set <std::string> hrAttribs;
    static const std::unordered_set <std::string> imgAttribs;
    static const std::unordered_set <std::string> inputAttribs;
    static const std::unordered_set <std::string> keygenAttribs;
    static const std::unordered_set <std::string> linkAttribs;
    static const std::unordered_set <std::string> metaAttribs;
    static const std::unordered_set <std::string> paramAttribs;
    static const std::unordered_set <std::string> sourceAttribs;
    static const std::unordered_set <std::string> trackAttribs;
    static const std::unordered_set <std::string> wbrAttribs;
};

#endif /* VOIDTAG_HPP */

