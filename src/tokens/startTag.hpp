#ifndef STARTTAG_HPP
#define STARTTAG_HPP

#include <string>
#include <locale>
#include <unordered_set>
#include <unordered_map>

#include "tag.hpp"

/** 
 * Class instantiates to all valid (implemented) html start tags.
 * IndentInfluence is +1. Attributes are chcked via calling
 * Tag::checkAttributes with correct set of attributes determined
 * by name, all in constructor.
 * Close on same is also implemented by having set of tagname
 * strings for which to return true.
 * Class contains static set of valid attibutes for each element, 
 * except glogal attributes, which are in member in Tag.
 */

class StartTag : public Tag
{
public:
    StartTag (size_t lineNr,
             const std::string & name,
             const std::vector <Attrib> & content);
    
    virtual ~StartTag () {}
    virtual std::string getName (void) const;
    virtual int indentInfluence (void) const;
    virtual bool closeOnSame    (void) const;

private:
    const std::string m_name;

    //static:
    static const std::unordered_map <std::string, 
            std::unordered_set <std::string> const * > validAttribs;

    static const std::unordered_set <std::string> closeOnSameSet;

    static const std::unordered_set <std::string> aAttribs;
    static const std::unordered_set <std::string> abbrAttribs;
    static const std::unordered_set <std::string> addressAttribs;
    static const std::unordered_set <std::string> articleAttribs;
    static const std::unordered_set <std::string> asideAttribs;
    static const std::unordered_set <std::string> audioAttribs;
    static const std::unordered_set <std::string> bAttribs;
    static const std::unordered_set <std::string> bdiAttribs;
    static const std::unordered_set <std::string> bdoAttribs;
    static const std::unordered_set <std::string> blockquoteAttribs;
    static const std::unordered_set <std::string> bodyAttribs;
    static const std::unordered_set <std::string> buttonAttribs;
    static const std::unordered_set <std::string> canvasAttribs;
    static const std::unordered_set <std::string> captionAttribs;
    static const std::unordered_set <std::string> citeAttribs;
    static const std::unordered_set <std::string> codeAttribs;
    static const std::unordered_set <std::string> colgroupAttribs;
    static const std::unordered_set <std::string> dataAttribs;
    static const std::unordered_set <std::string> datalistAttribs;
    static const std::unordered_set <std::string> ddAttribs;
    static const std::unordered_set <std::string> delAttribs;
    static const std::unordered_set <std::string> dfnAttribs;
    static const std::unordered_set <std::string> divAttribs;
    static const std::unordered_set <std::string> dlAttribs;
    static const std::unordered_set <std::string> dtAttribs;
    static const std::unordered_set <std::string> emAttribs;
    static const std::unordered_set <std::string> fieldsetAttribs;
    static const std::unordered_set <std::string> figcaptionAttribs;
    static const std::unordered_set <std::string> figureAttribs;
    static const std::unordered_set <std::string> footerAttribs;
    static const std::unordered_set <std::string> formAttribs;
    static const std::unordered_set <std::string> h1Attribs;
    static const std::unordered_set <std::string> h2Attribs;
    static const std::unordered_set <std::string> h3Attribs;
    static const std::unordered_set <std::string> h4Attribs;
    static const std::unordered_set <std::string> h5Attribs;
    static const std::unordered_set <std::string> h6Attribs;
    static const std::unordered_set <std::string> headAttribs;
    static const std::unordered_set <std::string> headerAttribs;
    static const std::unordered_set <std::string> htmlAttribs;
    static const std::unordered_set <std::string> iAttribs;
    static const std::unordered_set <std::string> iframeAttribs;
    static const std::unordered_set <std::string> insAttribs;
    static const std::unordered_set <std::string> kbdAttribs;
    static const std::unordered_set <std::string> labelAttribs;
    static const std::unordered_set <std::string> legendAttribs;
    static const std::unordered_set <std::string> liAttribs;
    static const std::unordered_set <std::string> mainAttribs;
    static const std::unordered_set <std::string> mapAttribs;
    static const std::unordered_set <std::string> markAttribs;
    static const std::unordered_set <std::string> meterAttribs;
    static const std::unordered_set <std::string> navAttribs;
    static const std::unordered_set <std::string> noscriptAttribs;
    static const std::unordered_set <std::string> objectAttribs;
    static const std::unordered_set <std::string> olAttribs;
    static const std::unordered_set <std::string> optgroupAttribs;
    static const std::unordered_set <std::string> optionAttribs;
    static const std::unordered_set <std::string> outputAttribs;
    static const std::unordered_set <std::string> pAttribs;
    static const std::unordered_set <std::string> preAttribs;
    static const std::unordered_set <std::string> progressAttribs;
    static const std::unordered_set <std::string> qAttribs;
    static const std::unordered_set <std::string> rbAttribs;
    static const std::unordered_set <std::string> rpAttribs;
    static const std::unordered_set <std::string> rtAttribs;
    static const std::unordered_set <std::string> rtcAttribs;
    static const std::unordered_set <std::string> rubyAttribs;
    static const std::unordered_set <std::string> sAttribs;
    static const std::unordered_set <std::string> sampAttribs;
    static const std::unordered_set <std::string> scriptAttribs;
    static const std::unordered_set <std::string> sectionAttribs;
    static const std::unordered_set <std::string> selectAttribs;
    static const std::unordered_set <std::string> smallAttribs;
    static const std::unordered_set <std::string> spanAttribs;
    static const std::unordered_set <std::string> strongAttribs;
    static const std::unordered_set <std::string> styleAttribs;
    static const std::unordered_set <std::string> subAttribs;
    static const std::unordered_set <std::string> supAttribs;
    static const std::unordered_set <std::string> tableAttribs;
    static const std::unordered_set <std::string> tbodyAttribs;
    static const std::unordered_set <std::string> tdAttribs;
    static const std::unordered_set <std::string> templateAttribs;
    static const std::unordered_set <std::string> textareaAttribs;
    static const std::unordered_set <std::string> tfootAttribs;
    static const std::unordered_set <std::string> thAttribs;
    static const std::unordered_set <std::string> theadAttribs;
    static const std::unordered_set <std::string> timeAttribs;
    static const std::unordered_set <std::string> titleAttribs;
    static const std::unordered_set <std::string> trAttribs;
    static const std::unordered_set <std::string> uAttribs;
    static const std::unordered_set <std::string> ulAttribs;
    static const std::unordered_set <std::string> varAttribs;
    static const std::unordered_set <std::string> videoAttribs;

/* backup without void elems:
a
abbr
address
article
aside
audio
b
bdi
bdo
blockquote
body
button
canvas
caption
cite
code
colgroup
data
datalist
dd
del
dfn
div
dl
dt
em
fieldset
figcaption
figure
footer
form
h1
h2
h3
h4
h5
h6
head
header
html
i
iframe
ins
kbd
label
legend
li
main
map
mark
meter
nav
noscript
object
ol
optgroup
option
output
p
pre
progress
q
rb
rp
rt
rtc
ruby
s
samp
script
section
select
small
span
strong
style
sub
sup
table
tbody
td
template
textarea
tfoot
th
thead
time
title
tr
u
ul
var
video
*/

};

#endif /* STARTTAG_HPP */

