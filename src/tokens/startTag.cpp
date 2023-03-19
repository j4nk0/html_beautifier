#include "startTag.hpp"

StartTag::StartTag (size_t lineNr,
                 const std::string & name,
                 const std::vector <Attrib> & content)
: Tag (lineNr, content), 
  m_name (name)
{
    std::string loweCaseName = m_name;
    std::vector <Attrib> attributes = content;
    for (char & c : loweCaseName) c = std::tolower (c);
    checkAttributes (m_content, *(validAttribs.at(loweCaseName)));
}

std::string StartTag::getName (void) const { return m_name; }

int StartTag::indentInfluence (void) const { return 1; }

bool StartTag::closeOnSame (void) const
{
    return closeOnSameSet.find (m_name) != closeOnSameSet.cend();
}

const std::unordered_set <std::string> StartTag::aAttribs = {
     "href",
     "target",
     "download",
     "rel",
     "hreflang",
     "type"
};

const std::unordered_set <std::string> StartTag::abbrAttribs = {
};

const std::unordered_set <std::string> StartTag::addressAttribs = {
};

const std::unordered_set <std::string> StartTag::articleAttribs = {
};

const std::unordered_set <std::string> StartTag::asideAttribs = {
};

const std::unordered_set <std::string> StartTag::audioAttribs = {
    "src",
    "crossorigin",
    "preload",
    "autoplay",
    "mediagroup",
    "loop",
    "muted",
    "controls"
};

const std::unordered_set <std::string> StartTag::bAttribs = {
};

const std::unordered_set <std::string> StartTag::bdiAttribs = {
};

const std::unordered_set <std::string> StartTag::bdoAttribs = {
};

const std::unordered_set <std::string> StartTag::blockquoteAttribs = {
    "cite"
};

const std::unordered_set <std::string> StartTag::bodyAttribs = {
    "onafterprint",
    "onbeforeprint",
    "onbeforeunload",
    "onhashchange",
    "onmessage",
    "onoffline",
    "ononline",
    "onpagehide",
    "onpageshow",
    "onpopstate",
    "onstorage",
    "onunload"
};

const std::unordered_set <std::string> StartTag::buttonAttribs = {
    "autofocus",
    "disabled",
    "form",
    "formaction",
    "formenctype",
    "formmethod",
    "formnovalidate",
    "formtarget",
    "name",
    "type",
    "value"
};

const std::unordered_set <std::string> StartTag::canvasAttribs = {
    "width",
    "height"
};

const std::unordered_set <std::string> StartTag::captionAttribs = {
};

const std::unordered_set <std::string> StartTag::citeAttribs = {
};

const std::unordered_set <std::string> StartTag::codeAttribs = {
};

const std::unordered_set <std::string> StartTag::colgroupAttribs = {
    "span"
};

const std::unordered_set <std::string> StartTag::dataAttribs = {
    "value"
};

const std::unordered_set <std::string> StartTag::datalistAttribs = {
};

const std::unordered_set <std::string> StartTag::ddAttribs = {
};

const std::unordered_set <std::string> StartTag::delAttribs = {
    "cite",
    "datetime"
};

const std::unordered_set <std::string> StartTag::dfnAttribs = {
};

const std::unordered_set <std::string> StartTag::divAttribs = {
};

const std::unordered_set <std::string> StartTag::dlAttribs = {
};

const std::unordered_set <std::string> StartTag::dtAttribs = {
};

const std::unordered_set <std::string> StartTag::emAttribs = {
};

const std::unordered_set <std::string> StartTag::fieldsetAttribs = {
    "disabled",
    "form",
    "name"
};

const std::unordered_set <std::string> StartTag::figcaptionAttribs = {
};

const std::unordered_set <std::string> StartTag::figureAttribs = {
};

const std::unordered_set <std::string> StartTag::footerAttribs = {
};

const std::unordered_set <std::string> StartTag::formAttribs = {
    "accept-charset",
    "action",
    "autocomplete",
    "enctype",
    "method",
    "name",
    "novalidate",
    "target"
};

const std::unordered_set <std::string> StartTag::h1Attribs = {
};

const std::unordered_set <std::string> StartTag::h2Attribs = {
};

const std::unordered_set <std::string> StartTag::h3Attribs = {
};

const std::unordered_set <std::string> StartTag::h4Attribs = {
};

const std::unordered_set <std::string> StartTag::h5Attribs = {
};

const std::unordered_set <std::string> StartTag::h6Attribs = {
};

const std::unordered_set <std::string> StartTag::headAttribs = {
};

const std::unordered_set <std::string> StartTag::headerAttribs = {
};

const std::unordered_set <std::string> StartTag::htmlAttribs = {
    "manifest"
};

const std::unordered_set <std::string> StartTag::iAttribs = {
};

const std::unordered_set <std::string> StartTag::iframeAttribs = {
    "src",
    "srcdoc",
    "name",
    "sandbox",
    "width",
    "height"
};

const std::unordered_set <std::string> StartTag::insAttribs = {
    "cite",
    "datetime"
};

const std::unordered_set <std::string> StartTag::kbdAttribs = {
};

const std::unordered_set <std::string> StartTag::labelAttribs = {
    "form",
    "for"
};

const std::unordered_set <std::string> StartTag::legendAttribs = {
};

const std::unordered_set <std::string> StartTag::liAttribs = {
    "value"
};

const std::unordered_set <std::string> StartTag::mainAttribs = {
};

const std::unordered_set <std::string> StartTag::mapAttribs = {
    "name"
};

const std::unordered_set <std::string> StartTag::markAttribs = {
};

const std::unordered_set <std::string> StartTag::meterAttribs = {
    "value",
    "min",
    "max",
    "low",
    "high",
    "optimum"
};

const std::unordered_set <std::string> StartTag::navAttribs = {
};

const std::unordered_set <std::string> StartTag::noscriptAttribs = {
};

const std::unordered_set <std::string> StartTag::objectAttribs = {
    "data",
    "type",
    "typemustmatch",
    "name",
    "usemap",
    "form",
    "width",
    "height"
};

const std::unordered_set <std::string> StartTag::olAttribs = {
    "reversed",
    "start",
    "type"
};

const std::unordered_set <std::string> StartTag::optgroupAttribs = {
    "disabled",
    "label"
};

const std::unordered_set <std::string> StartTag::optionAttribs = {
    "disabled",
    "label",
    "selected",
    "value"
};

const std::unordered_set <std::string> StartTag::outputAttribs = {
    "for",
    "form",
    "name"
};

const std::unordered_set <std::string> StartTag::pAttribs = {
};

const std::unordered_set <std::string> StartTag::preAttribs = {
};

const std::unordered_set <std::string> StartTag::progressAttribs = {
    "value",
    "max"
};

const std::unordered_set <std::string> StartTag::qAttribs = {
    "cite"
};

const std::unordered_set <std::string> StartTag::rbAttribs = {
};

const std::unordered_set <std::string> StartTag::rpAttribs = {
};

const std::unordered_set <std::string> StartTag::rtAttribs = {
};

const std::unordered_set <std::string> StartTag::rtcAttribs = {
};

const std::unordered_set <std::string> StartTag::rubyAttribs = {
};

const std::unordered_set <std::string> StartTag::sAttribs = {
};

const std::unordered_set <std::string> StartTag::sampAttribs = {
};

const std::unordered_set <std::string> StartTag::scriptAttribs = {
    "src",
    "type",
    "charset",
    "async",
    "defer",
    "crossorigin"
};

const std::unordered_set <std::string> StartTag::sectionAttribs = {
};

const std::unordered_set <std::string> StartTag::selectAttribs = {
    "autofocus",
    "disabled",
    "form",
    "multiple",
    "name",
    "required",
    "size"
};

const std::unordered_set <std::string> StartTag::smallAttribs = {
};

const std::unordered_set <std::string> StartTag::spanAttribs = {
};

const std::unordered_set <std::string> StartTag::strongAttribs = {
};

const std::unordered_set <std::string> StartTag::styleAttribs = {
    "media",
    "type"
};

const std::unordered_set <std::string> StartTag::subAttribs = {
};

const std::unordered_set <std::string> StartTag::supAttribs = {
};

const std::unordered_set <std::string> StartTag::tableAttribs = {
    "border"
};

const std::unordered_set <std::string> StartTag::tbodyAttribs = {
};

const std::unordered_set <std::string> StartTag::tdAttribs = {
    "colspan",
    "rowspan",
    "headers"
};

const std::unordered_set <std::string> StartTag::templateAttribs = {
};

const std::unordered_set <std::string> StartTag::textareaAttribs = {
    "autofocus",
    "cols",
    "dirname",
    "disabled",
    "form",
    "maxlength",
    "minlength",
    "name",
    "placeholder",
    "readonly",
    "required",
    "rows",
    "wrap"
};

const std::unordered_set <std::string> StartTag::tfootAttribs = {
};

const std::unordered_set <std::string> StartTag::thAttribs = {
    "colspan",
    "rowspan",
    "headers",
    "scope",
    "abbr"
};

const std::unordered_set <std::string> StartTag::theadAttribs = {
};

const std::unordered_set <std::string> StartTag::timeAttribs = {
    "datetime"
};

const std::unordered_set <std::string> StartTag::titleAttribs = {
};

const std::unordered_set <std::string> StartTag::trAttribs = {
};

const std::unordered_set <std::string> StartTag::uAttribs = {
};

const std::unordered_set <std::string> StartTag::ulAttribs = {
};

const std::unordered_set <std::string> StartTag::varAttribs = {
};

const std::unordered_set <std::string> StartTag::videoAttribs = {
    "src",
    "crossorigin",
    "poster",
    "preload",
    "autoplay",
    "mediagroup",
    "loop",
    "muted",
    "controls",
    "width",
    "height"
};

const std::unordered_map <std::string, 
    std::unordered_set <std::string> const * > StartTag::validAttribs = {

    {"a",                &  StartTag::aAttribs},
    {"abbr",             &  StartTag::abbrAttribs},
    {"address",          &  StartTag::addressAttribs},
    {"article",          &  StartTag::articleAttribs},
    {"aside",            &  StartTag::asideAttribs},
    {"audio",            &  StartTag::audioAttribs},
    {"b",                &  StartTag::bAttribs},
    {"bdi",              &  StartTag::bdiAttribs},
    {"bdo",              &  StartTag::bdoAttribs},
    {"blockquote",       &  StartTag::blockquoteAttribs},
    {"body",             &  StartTag::bodyAttribs},
    {"button",           &  StartTag::buttonAttribs},
    {"canvas",           &  StartTag::canvasAttribs},
    {"caption",          &  StartTag::captionAttribs},
    {"cite",             &  StartTag::citeAttribs},
    {"code",             &  StartTag::codeAttribs},
    {"colgroup",         &  StartTag::colgroupAttribs},
    {"data",             &  StartTag::dataAttribs},
    {"datalist",         &  StartTag::datalistAttribs},
    {"dd",               &  StartTag::ddAttribs},
    {"del",              &  StartTag::delAttribs},
    {"dfn",              &  StartTag::dfnAttribs},
    {"div",              &  StartTag::divAttribs},
    {"dl",               &  StartTag::dlAttribs},
    {"dt",               &  StartTag::dtAttribs},
    {"em",               &  StartTag::emAttribs},
    {"fieldset",         &  StartTag::fieldsetAttribs},
    {"figcaption",       &  StartTag::figcaptionAttribs},
    {"figure",           &  StartTag::figureAttribs},
    {"footer",           &  StartTag::footerAttribs},
    {"form",             &  StartTag::formAttribs},
    {"h1",               &  StartTag::h1Attribs},
    {"h2",               &  StartTag::h2Attribs},
    {"h3",               &  StartTag::h3Attribs},
    {"h4",               &  StartTag::h4Attribs},
    {"h5",               &  StartTag::h5Attribs},
    {"h6",               &  StartTag::h6Attribs},
    {"head",             &  StartTag::headAttribs},
    {"header",           &  StartTag::headerAttribs},
    {"html",             &  StartTag::htmlAttribs},
    {"i",                &  StartTag::iAttribs},
    {"iframe",           &  StartTag::iframeAttribs},
    {"ins",              &  StartTag::insAttribs},
    {"kbd",              &  StartTag::kbdAttribs},
    {"label",            &  StartTag::labelAttribs},
    {"legend",           &  StartTag::legendAttribs},
    {"li",               &  StartTag::liAttribs},
    {"main",             &  StartTag::mainAttribs},
    {"map",              &  StartTag::mapAttribs},
    {"mark",             &  StartTag::markAttribs},
    {"meter",            &  StartTag::meterAttribs},
    {"nav",              &  StartTag::navAttribs},
    {"noscript",         &  StartTag::noscriptAttribs},
    {"object",           &  StartTag::objectAttribs},
    {"ol",               &  StartTag::olAttribs},
    {"optgroup",         &  StartTag::optgroupAttribs},
    {"option",           &  StartTag::optionAttribs},
    {"output",           &  StartTag::outputAttribs},
    {"p",                &  StartTag::pAttribs},
    {"pre",              &  StartTag::preAttribs},
    {"progress",         &  StartTag::progressAttribs},
    {"q",                &  StartTag::qAttribs},
    {"rb",               &  StartTag::rbAttribs},
    {"rp",               &  StartTag::rpAttribs},
    {"rt",               &  StartTag::rtAttribs},
    {"rtc",              &  StartTag::rtcAttribs},
    {"ruby",             &  StartTag::rubyAttribs},
    {"s",                &  StartTag::sAttribs},
    {"samp",             &  StartTag::sampAttribs},
    {"script",           &  StartTag::scriptAttribs},
    {"section",          &  StartTag::sectionAttribs},
    {"select",           &  StartTag::selectAttribs},
    {"small",            &  StartTag::smallAttribs},
    {"span",             &  StartTag::spanAttribs},
    {"strong",           &  StartTag::strongAttribs},
    {"style",            &  StartTag::styleAttribs},
    {"sub",              &  StartTag::subAttribs},
    {"sup",              &  StartTag::supAttribs},
    {"table",            &  StartTag::tableAttribs},
    {"tbody",            &  StartTag::tbodyAttribs},
    {"td",               &  StartTag::tdAttribs},
    {"template",         &  StartTag::templateAttribs},
    {"textarea",         &  StartTag::textareaAttribs},
    {"tfoot",            &  StartTag::tfootAttribs},
    {"th",               &  StartTag::thAttribs},
    {"thead",            &  StartTag::theadAttribs},
    {"time",             &  StartTag::timeAttribs},
    {"title",            &  StartTag::titleAttribs},
    {"tr",               &  StartTag::trAttribs},
    {"u",                &  StartTag::uAttribs},
    {"ul",               &  StartTag::ulAttribs},
    {"var",              &  StartTag::varAttribs},
    {"video",            &  StartTag::videoAttribs}
};

const std::unordered_set <std::string> StartTag::closeOnSameSet = {
    "li",
    "dd",
    "dt",
    "p",
    "rb",
    "rt",
    "rtc",
    "rp",
    "optgroup",
    "option",
    "tbody",
    "tr",
    "td",
    "th"
};


