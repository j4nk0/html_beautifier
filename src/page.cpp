#include "configuration.hpp"
#include "fileError.hpp"
#include "syntaxError.hpp"

#include "page.hpp"

/**
 * Erases leading whitechars, that acts as
 * indentation, form source lines.\n
 * Also replaces newlines inside of content with spaces.\n
 *
 * Returns number of newlines in content prior to processing.\n
 * 
 * @param[in-out] content string possibly containing
 * multiple lines with indentation to be stripped
 * of indentation and concatenated into one line
 */

size_t Page::lineStrip (std::string & content)
{
    if (content.empty()) return 0;
    std::istringstream ss (content);
    std::string line;
    size_t textBegin = 0;
    size_t lineCnt = 0;
    if (content.back() == '\n') lineCnt++;
    content = "";
    while (std::getline(ss, line)) {
        if ( ! content.empty()) content . push_back (' ');
        ++lineCnt;
        textBegin = line.find_first_not_of (HTML_WHITE_CHARS_STRING);
        if (textBegin == std::string::npos) continue;
        content.append (line.substr (textBegin, std::string::npos));
    }
    --lineCnt;
    return lineCnt;
}


/**
 * Implements advanced std::basic_istream::peek.
 * function compares given str to characters that
 * will be available to be subtracted from is
 * after call to this function.\n
 * COMPARES STRINGS CASE INSENSITIVELY\n
 * 
 * Returns true only if characters immediately 
 * available for extraction from is are case insensitive
 * match for str.
 * 
 * @param[in-out] is stream to be peeked to
 * @param[in] str CASE INSENSITIVE string to be found
 */

bool Page::isNext (std::istream & is, const std::string & str)
//Case insensitive comparison
{
    if ( ! is.good() ) return false;
    size_t size = str.size();
    auto origPos = is.tellg();
    const char * cstr = str.c_str();
    //buffer will contain both strings to be compared
    char * buffer = new char [2 * (size + 1)]();
    size_t i = 0;
    for ( ; i < size; i++) {
        is.get(buffer[i]);
        buffer[i] = std::toupper(buffer[i]);
    }
    //buffer[i++] = '\0';   //not needed because array must be initialized
    ++i;
    for ( ; i < 2 * (size + 1); i++) {
        buffer[i] = cstr [i - size -1];
        buffer[i] = std::toupper(buffer[i]);
    }
    // cstring copied including terminating '\0'
    is.clear();
    is.seekg (origPos);
    bool res = true;
    for (size_t j=0; j < size; j++) {
        if (buffer[j] != buffer[j + size + 1]) {
            res = false;
            break;
        }
    }
    delete [] buffer;
    return res;
}

/**
 * Implements simplified html lexer as
 * finite state machine, tries to match these expressions:\n
 * "<tagname...>"\n
 * "<!--...-->"\n
 * "<!DOCTYPE...>"\n
 * "<![CDATA[...]]>"\n
 * "> ... <"\n\n
 * Finite state machine has total of 4 states in contrast with
 * tokenizer described in html standard which is more robust
 * at 69 different states. But this formatter program does not
 * implement document object model (DOM) semantics.
 *
 * Each state corresponds to exactly one distinct character
 * which is to be extracted from is before the state is
 * reevaluated. These characters could be used to identify
 * current state (the state enum is redundant):\n
 * inText    = "<"\n
 * inTag     = ">"\n
 * inCdata   = "]"\n
 * inComment = "-"\n\n
 *
 * Only the token produced inText (the default state) 
 * is guaranteed to have its content always complete.
 * Therefore empty string might be extracted as text token,
 * emiting it is not necessary, but in other states it is.
 * In all other states, 1st char (the searched) is
 * always missing and special handling of multi-character
 * end of content is also needed specific for each token type.
 * 
 * In case of stream state changing from good,
 * currently processed tag may have invalid ending.
 * Lexer does not check for that and regards the tag with
 * proper beginning as correct.
 *
 * Goal of this member function is to break html source
 * stream is into html tokens completely.\n
 * 
 * Extracted tokens are stored in tokenList.
 *
 * @param[in] is stream of ASCII compatible html source code
 *
 */

void Page::tokenize (std::istream & is)
{
    size_t lineNumber = 1;
    std::string content, part;
    char toFind = '<';
    enum {
        inText,
        inTag,
        inComment,
        inCdata,
    } state = inText;
    /** enum state Represents all possible states of the lexer */
    while (std::getline (is, part, toFind)) {
        content.append(part);
        lineNumber += lineStrip (content);
        switch (state) {
        case inText:
        {
            if ( ! isNext (is, "!")) {
                state = inTag;
                toFind = '>';
            } else if (isNext (is, "!--")) {
                state = inComment;
                toFind = '-';
            //  <! but not <!--
            } else if (isNext (is, "![CDATA[")) {
                state = inCdata;
                toFind = ']';
            } else if (isNext (is, "!DOCTYPE")) {
                state = inTag;
                toFind = '>';
            } else {
                //riddle me this: <!... but not a <!DOCTYPE nor <!-- not even <![CDATA[
                throw SyntaxError ("line: " + std::to_string (lineNumber) + " invalid token \"<!\"");
            }
            //all ifs but the last else clause lead here:
            if ( ! content.empty())
                tokenList.push_back (Token::makeText (lineNumber, content));
            content = "";
            break;
        }
        case inTag: 
        {
            content.append(& toFind, 1);
            // is > in quotes?
            int quotesCnt = std::count(content.begin(), content.end(), '"');
            if (quotesCnt % 2 != 0) break;
            quotesCnt +=  std::count(content.begin(), content.end(), '\'');
            if (quotesCnt % 2 != 0) break;
            // > not in quotes
            state = inText;
            toFind = '<';

            tokenList.push_back (Token::makeTag (lineNumber, content));
            content = "";
            break;
        }
        case inComment:
        {
            content.append(& toFind, 1);
            //has --> been found or just -
            if ( ! isNext (is, "->")) break;
            //  -->  confirmed
            state = inText;
            toFind = '<';
            is.seekg (2, std::ios_base::cur);

            tokenList.push_back (Token::makeComment (lineNumber, content));
            content = "";
            break;
        }
        case inCdata:
        {
            content.append(& toFind, 1);
            //has ]]> been found or just ]
            if ( ! isNext (is, "]>")) break;
            //  ]]>  confirmed
            state = inText;
            toFind = '<';
            is.seekg (2, std::ios_base::cur);

            tokenList.push_back (Token::makeCdata (lineNumber, content));
            content = "";
        }
        }
    }
}

/**
 *  Checks for misnested (crossed) "elements"
 * and sets each token its indentation depth.
 * May throw SyntaxError or issue warning throught
 * std::cerr
 */
void Page::setIndentation (void)
{
    size_t currInLevel = 0;
    std::stack <Token*> opened;
    for (Token* tpt : tokenList) {
        switch(tpt -> indentInfluence()) {
        case 0:
            tpt -> setDepth (currInLevel);
            break;
        case -1:
            if (opened.empty()) throw SyntaxError (std::to_string(tpt -> getLineNr())
                    + " : " + tpt -> str() + " occured before startTag");
            if (tpt -> getName() == opened.top() -> getName()) {
                tpt -> setDepth (--currInLevel);
                opened.pop();
            } else {
                throw SyntaxError (std::to_string(tpt -> getLineNr()) + " : " + tpt -> str()
                    + " misnested in "+std::to_string(opened.top()->getLineNr())
                    + " : "+opened.top()->str());
            }
            break;
        case 1:
            if (opened.empty() 
                || opened.top() -> getName() != tpt -> getName()
                || tpt -> closeOnSame() == false)
            {
                tpt -> setDepth (currInLevel++);
                opened.push(tpt);
            } else {
                std::cerr << "WARNING: " << opened.top() -> str()
                    << " at: " << opened.top() -> getLineNr()
                    << " not closed before " << tpt -> str()
                    << " at " << tpt -> getLineNr() << std::endl;
                tpt -> setDepth (opened.top() -> getDepth());
                opened.pop();
                opened.push (tpt);                
            }
        }
    }
    while ( ! opened.empty()) {
        std::cerr << "Warning: tag not closed: " 
            << opened.top() -> str() << " from line: "
            << opened.top() -> getLineNr() << std::endl;
        opened.pop();
    }
}

Page::Page (const std::string & fileName)
{
    std::ifstream is (fileName);
    if ( ! is.good()) throw FileError(fileName + ": file could not be read"); 
    try {
        tokenize (is);
        setIndentation();
    } catch (FileError & e) {
        for (Token * tpt : tokenList) delete tpt;
        throw e;
    } catch (SyntaxError & e) {
        for (Token * tpt : tokenList) delete tpt;
        throw e;
    }
}

Page::~Page (void)
{
    for (Token * tpt : tokenList) delete tpt;
}

void Page::writeToFile (const std::string & fileName,
                      const Configuration & cfg) const
{
    std::ofstream os (fileName, std::ofstream::out | std::ofstream::trunc);
    if ( ! os.good()) throw FileError(fileName + ": file could not be opened");
    std::string buffer;
    size_t spaceCnt;
    size_t pos;
    for (Token* tpt : tokenList) {
        spaceCnt = cfg.getIndentWidth() * tpt -> getDepth();
        for (size_t i = 0; i < spaceCnt; i++) buffer.push_back(' ');
        buffer.insert(0, spaceCnt, ' ');
        buffer.append(tpt -> str());
        if (buffer.size() < cfg.getMaxLineLen()) {
            os << buffer.append("\n");
        } else {
            while (buffer.size() > cfg.getMaxLineLen()) {
                pos = buffer.find_last_of (HTML_WHITE_CHARS_STRING,
                                           cfg.getMaxLineLen());
                if (pos == std::string::npos || pos < cfg.getMinTextLen() + spaceCnt)
                    pos = buffer.find_first_of (HTML_WHITE_CHARS_STRING,
                                               cfg.getMaxLineLen());
                if (pos == std::string::npos) {
                    os << buffer.append("\n");
                    break;
                }
                buffer[pos] = '\n';
                os << buffer.substr(0, pos +1);
                buffer.erase(0, pos +1);
                if (buffer.empty()) break;
                buffer.insert(0, spaceCnt, ' ');
            }
            if ( ! buffer.empty()) os << buffer.append("\n");
        }
        buffer = "";
        if ( ! os.good()) throw FileError (fileName + " : Couldn't be written");
    }
    os.flush();
    if ( ! os.good()) throw FileError (fileName + " : Couldn't be written");
}

