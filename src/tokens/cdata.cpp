#include "cdata.hpp"

const std::string Cdata::name = "cdata";

std::string Cdata::str     (void) const
{
    std::string res = "<";
    res . append (m_content);
    res . append ("]>");
    return res;
}

std::string Cdata::getName    (void) const { return name; }
