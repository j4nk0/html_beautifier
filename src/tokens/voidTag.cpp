#include "voidTag.hpp"

VoidTag::VoidTag (size_t lineNr,
                 const std::string & name,
                 const std::vector <Attrib> & content)
: Tag (lineNr, content), 
  m_name (name)
{
    std::string loweCaseName = m_name;
    std::vector <Attrib> attributes = content;
    for (char & c : loweCaseName) c = std::tolower (c);
    attributes.pop_back();  //getting rid of "/"
    checkAttributes (attributes, *(validAttribs.at(loweCaseName))); 
}

std::string VoidTag::str (void) const
{
    std::string res = Tag::str ();
    //erase the space between "/" and ">"
    res.erase(res.size() -2, 1);
    return res;
}    

std::string VoidTag::getName (void) const { return m_name; }

int VoidTag::indentInfluence (void) const { return 0; }

const std::unordered_set <std::string> VoidTag::areaAttribs = {
    "alt",
    "coords",
    "download",
    "href",
    "hreflang",
    "rel",
    "shape",
    "target",
    "type"
};

const std::unordered_set <std::string> VoidTag::baseAttribs = {
    "href",
    "target"
};

const std::unordered_set <std::string> VoidTag::brAttribs = {};

const std::unordered_set <std::string> VoidTag::colAttribs = {
    "span"
};

const std::unordered_set <std::string> VoidTag::embedAttribs = {
    "src",
    "type",
    "width",
    "height"
};

const std::unordered_set <std::string> VoidTag::hrAttribs = {};

const std::unordered_set <std::string> VoidTag::imgAttribs = {
    "alt",
    "src",
    "crossorigin",
    "usemap",
    "ismap",
    "width",
    "height"
};

const std::unordered_set <std::string> VoidTag::inputAttribs = {
    "accept",
    "alt",
    "autocomplete",
    "autofocus",
    "checked",
    "dirname",
    "disabled",
    "form",
    "formaction",
    "formenctype",
    "formmethod",
    "formnovalidate",
    "formtarget",
    "height",
    "inputmode",
    "list",
    "max",
    "maxlength",
    "min",
    "minlength",
    "multiple",
    "name",
    "pattern",
    "placeholder",
    "readonly",
    "required",
    "size",
    "src",
    "step",
    "type",
    "value",
    "width"
};

const std::unordered_set <std::string> VoidTag::keygenAttribs = {
    "autofocus",
    "challenge",
    "disabled",
    "form",
    "keytype",
    "name"
};

const std::unordered_set <std::string> VoidTag::linkAttribs = {
    "href",
    "crossorigin",
    "rel",
    "media",
    "hreflang",
    "type",
    "sizes"
};

const std::unordered_set <std::string> VoidTag::metaAttribs = {
    "name",
    "http-equiv",
    "content",
    "charset"
};

const std::unordered_set <std::string> VoidTag::paramAttribs = {
    "name",
    "value"
};

const std::unordered_set <std::string> VoidTag::sourceAttribs = {
    "src",
    "type"
};

const std::unordered_set <std::string> VoidTag::trackAttribs = {
    "kind",
    "src",
    "srclang",
    "label",
    "default"
};

const std::unordered_set <std::string> VoidTag::wbrAttribs = {};

const std::unordered_map <std::string, 
    std::unordered_set <std::string> const * > VoidTag::validAttribs = {

    {"area",    & VoidTag::areaAttribs},
    {"base",    & VoidTag::baseAttribs},
    {"br",      & VoidTag::brAttribs},
    {"col",     & VoidTag::colAttribs},
    {"embed",   & VoidTag::embedAttribs},
    {"hr",      & VoidTag::hrAttribs},
    {"img",     & VoidTag::imgAttribs},
    {"input",   & VoidTag::inputAttribs},
    {"keygen",  & VoidTag::keygenAttribs},
    {"link",    & VoidTag::linkAttribs},
    {"meta",    & VoidTag::metaAttribs},
    {"param",   & VoidTag::paramAttribs},
    {"source",  & VoidTag::sourceAttribs},
    {"track",   & VoidTag::trackAttribs},
    {"wbr",     & VoidTag::wbrAttribs}
};

