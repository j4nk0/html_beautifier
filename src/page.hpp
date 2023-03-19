#ifndef PAGE_HPP
#define PAGE_HPP

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>
#include <cstring>
#include <fstream>

#include "token.hpp"

/**
 * Represents html page in memory
 * as a list of tokens.
 */

class Page
{
public:

    /**
     * Constructs page from file of given name
     * and checks the file for errors.
     * @param[in] filename name of html 
     * source file in ASCII compatible encoding
     */

    Page (const std::string & fileName);
    ~Page (void);
   
    /**
     * Writes html source to file, overwriting it
     * @param[in] filename html source to be created
     * @param[in] cfg Configuration object containing
     * values of configurable options describing
     * formating of the html source text
     */

    void writeToFile (const std::string & fileName,
                      const Configuration & cfg) const;
private:
    void tokenize (std::istream & is);
    void setIndentation (void);
    
    static size_t lineStrip (std::string & content);
    static bool isNext (std::istream & is, const std::string & str);
    
    std::vector<Token*> tokenList;
};

#endif /* PAGE_HPP */

