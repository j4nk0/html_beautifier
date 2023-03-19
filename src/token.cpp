#include "token.hpp"

#include "tokens/text.hpp"
#include "tokens/comment.hpp"
#include "tokens/tag.hpp"
#include "tokens/cdata.hpp"
#include "tokens/unknown.hpp"
#include "syntaxError.hpp"
#include "tokens/endTag.hpp"
#include "tokens/voidTag.hpp"
#include "tokens/startTag.hpp"


std::string Attrib::str (void) const
{
    std::string res = m_name;
    if ( ! m_value.empty()) {
        res.append ("=");
        res.append (m_value);
    }
    return res;
}

//virtual:
int Token::indentInfluence (void) const { return 0; }
bool Token::closeOnSame    (void) const { return false; }

//non-virtual:
size_t Token::getLineNr  (void) const   { return m_lineNr; }
int    Token::getDepth   (void) const   { return m_depth; }
void   Token::setDepth   (int newDepth) { m_depth = newDepth; }

//static:
Token * Token::makeText     (size_t lineNr, const std::string & content) { return new Text      (lineNr, content); }
Token * Token::makeCdata    (size_t lineNr, const std::string & content) { return new Cdata     (lineNr, content); }
Token * Token::makeComment  (size_t lineNr, const std::string & content) { return new Comment   (lineNr, content); }
Token * Token::makeUnknown  (size_t lineNr, const std::string & content) { return new Unknown   (lineNr, content); }

Token * Token::makeVoidTag  (size_t lineNr, const std::string & name, const std::vector <Attrib> & content)
{
    return new VoidTag (lineNr, name, content);
}

Token * Token::makeStartTag (size_t lineNr, const std::string & name, const std::vector <Attrib> & content)
{
    return new StartTag (lineNr, name, content);
}

Token * Token::makeEndTag (size_t lineNr, const std::string & name)
{
    return new EndTag (lineNr, name);
}

/** 
 * Function ties to determine subtype of Tag to be created.
 * It does so based purely on content of the emitted token. 
 */

Token * Token::makeTag      (size_t lineNr, const std::string & content)
{
    //first, get rid of closing ">"
    std::string toParse = content.substr (0, content.size() -1);
    auto beg = toParse.find_first_of (HTML_WHITE_CHARS_STRING);
    std::string name = toParse.substr (0, beg);
    std::string lowerName = name;
    for (char & c : lowerName) c = std::tolower (c);
    auto end = beg;
    if (name[0] == '/') {
        end = toParse.find_first_not_of (HTML_WHITE_CHARS_STRING, beg);
        if (end == std::string::npos
            && startTags.find(lowerName.substr(1, std::string::npos))
                != startTags.end())
        {
            return makeEndTag (lineNr, name.substr(1, std::string::npos));
        } else {
            return makeUnknown  (lineNr, toParse);
        }
    }
    if (lowerName == "!doctype") return makeUnknown  (lineNr, toParse);
    if (voidTags.find(lowerName) != voidTags.end()
        && toParse.back() != '/')
    {
        return makeUnknown  (lineNr, toParse);
    }
    if (voidTags.find(lowerName) == voidTags.end()
        && startTags.find(lowerName) == startTags.end()) 
    {
        return makeUnknown  (lineNr, toParse);
    }
    std::vector <Attrib> contVec = parseAttr (name, toParse, lineNr);
    if (voidTags.find(lowerName) != voidTags.end()) {
        return makeVoidTag  (lineNr, name, contVec);
    } else {
        return makeStartTag (lineNr, name, contVec);
    }
    
    //return new Tag (lineNr, contVec);
}

/**  Parses attributes according to html standard:\n
 * empty attribute without "=" is possible, so is
 * "name = value" with zero or more spaces around "=",
 * value might not be quoted, if it is a single word,
 * or it may be quoted with single or double quotes.\n
 * Returns vector of parameters which can be reconstructed
 * back to sting. Throws an exception if non-empty attribute
 * lacks value.
 * 
 * @param[in] start position in string where name ends
 * and attributes start
 * @param[in] toParse string to extract parameters from
 */

std::vector <Attrib> Token::parseAttr (const std::string & name,
                                       std::string & toParse,
                                       size_t lineNr)
{
    std::vector <Attrib> vec;
    auto beg = name.size();
    auto end = beg;
    while (beg != std::string::npos) {
        Attrib attr;
        beg = toParse.find_first_not_of (HTML_WHITE_CHARS_STRING, beg);
        if (beg == std::string::npos) break;
        end = toParse.find_first_of (std::string("=") + HTML_WHITE_CHARS_STRING, beg);
        attr.m_name = toParse.substr (beg, end - beg);

        beg = toParse.find_first_not_of (HTML_WHITE_CHARS_STRING, end);
        if (beg == std::string::npos) {
            vec.push_back (attr);
            break;
        }
        if (toParse[beg] != '=') {
            //empty attribute
            vec.push_back (attr);
            continue;
        }
        beg = toParse.find_first_not_of (std::string("=") + HTML_WHITE_CHARS_STRING, beg);
        if (beg == std::string::npos) {
            throw SyntaxError ("line: " + std::to_string(lineNr) + " tag: "
                + name + " attribute: " + attr.m_name + " is missing a value after \"=\"");
        }
        if (toParse[beg] == '\'')
            end = toParse.find_first_of ("'", beg + 1) + 1;
        else if (toParse[beg] == '"')
            end = toParse.find_first_of ("\"", beg + 1) + 1;
        else
            end = toParse.find_first_of (HTML_WHITE_CHARS_STRING, beg);
        attr.m_value = toParse.substr (beg, end - beg);
        vec.push_back (attr);
        beg = end;
    }
    return vec;
}


const std::unordered_set <std::string> Token::voidTags = {
    "area",
    "base",
    "br",
    "col",
    "embed",
    "hr",
    "img",
    "input",
    "keygen",
    "link",
    "meta",
    "param",
    "source",
    "track",
    "wbr"
};

const std::unordered_set <std::string> Token::startTags = {
    "a",            
    "abbr",         
    "address",      
    "article",      
    "aside",        
    "audio",        
    "b",            
    "bdi",          
    "bdo",          
    "blockquote",
    "body",         
    "button",       
    "canvas",       
    "caption",      
    "cite",         
    "code",         
    "colgroup",     
    "data",         
    "datalist",     
    "dd",           
    "del",          
    "dfn",          
    "div",          
    "dl",           
    "dt",           
    "em",           
    "fieldset",     
    "figcaption",
    "figure",       
    "footer",       
    "form",         
    "h1",           
    "h2",           
    "h3",           
    "h4",           
    "h5",           
    "h6",           
    "head",         
    "header",       
    "html",         
    "i",            
    "iframe",       
    "ins",          
    "kbd",          
    "label",        
    "legend",       
    "li",           
    "main",         
    "map",          
    "mark",         
    "meter",        
    "nav",          
    "noscript",     
    "object",       
    "ol",           
    "optgroup",     
    "option",       
    "output",       
    "p",            
    "pre",          
    "progress",     
    "q",            
    "rb",           
    "rp",           
    "rt",           
    "rtc",          
    "ruby",         
    "s",            
    "samp",         
    "script",       
    "section",      
    "select",       
    "small",        
    "span",         
    "strong",       
    "style",        
    "sub",          
    "sup",          
    "table",        
    "tbody",        
    "td",           
    "template",     
    "textarea",     
    "tfoot",        
    "th",           
    "thead",        
    "time",         
    "title",        
    "tr",           
    "u",            
    "ul",           
    "var",          
    "video"        
};

