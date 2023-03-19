#include "comment.hpp"

const std::string Comment::name = "comment";

std::string Comment::str     (void) const
{
    std::string res = "<";
    res . append (m_content);
    res . append ("->");
    return res;
}

std::string Comment::getName    (void) const { return name; }
