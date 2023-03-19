#include "unknown.hpp"

const std::string Unknown::name = "unknown";

std::string Unknown::str     (void) const
{
    std::string res = "<";
    res . append (m_content);
    res . append (">");
    return res;
}

std::string Unknown::getName    (void) const { return name; }
