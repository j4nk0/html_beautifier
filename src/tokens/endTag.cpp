#include "endTag.hpp"

std::string EndTag::str     (void) const
{
    std::string res = "</";
    res.append (m_name);
    res.append (">");
    return res;
}

std::string EndTag::getName (void) const { return m_name; }
int EndTag::indentInfluence (void) const { return -1; }
