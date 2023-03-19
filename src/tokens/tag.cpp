#include "tag.hpp"

std::string Tag::str (void) const
{
    std::string res = "<";
    res.append (getName ());
    res.append (" ");
    for (const Attrib & att : m_content) {
        res.append (att.str());
        res.append (" ");
    }
    res . append (">");
    return res;
}

void Tag::checkAttributes (const std::vector <Attrib> & toCheck,
                           const std::unordered_set <std::string> & valid) const
{
    for (const Attrib & att : toCheck) {
        if (globalAttributes.find (att.m_name) != globalAttributes.end()) continue;
        if (valid.find (att.m_name) != valid.end()) continue;
        // att is invalid:
        std::cerr << "WARNING: line: " << getLineNr() << " Invalid attbibute: \""
            << att.m_name << "\" of tag <" << getName() << ">" << std::endl;
    }
}

const std::unordered_set <std::string> Tag::globalAttributes = {
    "accesskey",
    "class",
    "contenteditable",
    "dir",
    "hidden",
    "id",
    "lang",
    "spellcheck",
    "style",
    "tabindex",
    "title",
    "translate",
};

