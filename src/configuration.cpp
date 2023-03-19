#include "configuration.hpp"
#include "fileError.hpp"

const std::unordered_map<std::string, std::istream & (Configuration::*)(std::istream &)> 
    Configuration::setter = {
        {INDENTWIDTH_KEYWORD, & Configuration::setIndentWidth},
        {MAXLINELEN_KEYWORD,  & Configuration::setMaxLineLen},
        {MINTEXTLEN_KEYWORD,  & Configuration::setMinTextLen}
};

Configuration::Configuration (void)
: m_indentWidth (DEFAULT_INDENTWIDTH),
  m_maxLineLen  (DEFAULT_MAXLINELEN),
  m_minTextLen  (DEFAULT_MINTEXTLEN)
{
}

Configuration & Configuration::readFile (const std::string & filename)
{
    if (filename == "") return *this;
    std::ifstream conf (filename);
    if (!conf.good()) throw FileError(CONFIG_FILE_ERROR_MESSAGE);
    std::string line, keyword;
    std::istringstream lineStream;
    while (std::getline(conf, line)) {
        lineStream.str(line);
        lineStream >> keyword;
        try {
            (this ->* setter.at(keyword)) (lineStream);
        } catch (std::out_of_range) {
            //the first word in lineStream is not really a keyword
        }
        lineStream.clear();
    }
    return *this;
}

uint Configuration::getIndentWidth (void) const
{
    return m_indentWidth;
}

uint Configuration::getMaxLineLen  (void) const
{
    return m_maxLineLen;
}

uint Configuration::getMinTextLen  (void) const
{
    return m_minTextLen;
}

std::istream & Configuration::setIndentWidth (std::istream & is)
{
    uint tmp;
    is >> tmp;
    //if (tmp < 0) return is;
    if (!is.fail()) m_indentWidth = tmp;
    return is;
}

std::istream & Configuration::setMaxLineLen (std::istream & is)
{
    uint tmp;
    is >> tmp;
    //if (tmp < 0) return is;
    if (!is.fail()) m_maxLineLen = tmp;
    return is;
}

std::istream & Configuration::setMinTextLen (std::istream & is)
{
    uint tmp;
    is >> tmp;
    if (tmp < DEFAULT_MINTEXTLEN) return is;
    if (!is.fail()) m_minTextLen = tmp;
    return is;
}

