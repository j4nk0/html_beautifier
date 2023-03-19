#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <locale>
#include <string>
#include <vector>
#include <unordered_set>

/** 
 * All characters, that are considered white when parsing
 * tokens and attributes
 */
#define HTML_WHITE_CHARS_STRING " \n\v\f\r\t"

#define DEFAULT_TOKEN_DEPTH -1

/** Represents tags attributes with their values */
struct Attrib
{
    /** returns string (printable) representation
     * to be written to file
     */
    std::string str (void) const;

    std::string m_name;
    std::string m_value;
};

/**
 * Class defines tokens interface as seen by page.
 * Also implements simple parser to determine 
 * some limited semantics of tokens emitted by lexer
 * Also holds factory functions to instantiate its subclasses
 * Must be aware of all instantiable subclasses.
 * Also contsins static sets of names of void and start tokens
 * so they can be properly instantiated.
 */

class Token
{
public:
    Token (size_t lineNr)
    : m_depth  (DEFAULT_TOKEN_DEPTH),
      m_lineNr (lineNr) {}

    virtual ~Token() {}
    
    /** Returns printable representation of token*/
    virtual std::string str     (void) const = 0;
    
    /** Returns tagName - special value to identify 
     * semantically different instances of the same subclass
     */
    virtual std::string getName (void) const = 0;
    
    /** Describes how token relates to tokens "under" 
     * it in page: +1 - following token should be
     * more indented; -1 less; 0 same;
     */
    virtual int indentInfluence (void) const;
    
    /** Aims to implement simple version of tag ommision.
     * If true, then if there are two opening tags in succesion,
     * the first tag is regarded as closed, indentation stays same.
     * Only applies to some tags - those that return true */
    virtual bool closeOnSame    (void) const;
        
    /** Returns line number in original file, used for error localization */
    size_t getLineNr  (void) const;
    
    /** Returns number of relative indentations to be made before writing token*/
    int    getDepth   (void) const;
    
    /** Sets indentation to given level*/
    void   setDepth   (int newDepth);

    static Token * makeText     (size_t lineNr, const std::string & content);
    static Token * makeCdata    (size_t lineNr, const std::string & content);
    static Token * makeComment  (size_t lineNr, const std::string & content);
    static Token * makeUnknown  (size_t lineNr, const std::string & content);
    static Token * makeTag      (size_t lineNr, const std::string & content);
    
    /** Factory functions. Allocated memory is to be freed by Page destructor*/
    static Token * makeEndTag (size_t lineNr, const std::string & name);
    
    static Token * makeVoidTag (size_t lineNr, const std::string & name,
                                const std::vector <Attrib> & content);
    
    static Token * makeStartTag (size_t lineNr, const std::string & name, 
                                const std::vector <Attrib> & content);
    
    static std::vector <Attrib> parseAttr (const std::string & name,
                                           std::string & toParse,
                                           size_t lineNr);
    
protected:
    int m_depth;
    const size_t m_lineNr;

private:
    static const std::unordered_set <std::string> voidTags;
    static const std::unordered_set <std::string> startTags;
};

#endif /* TOKEN_HPP */

