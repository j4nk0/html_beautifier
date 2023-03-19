#include "text.hpp"

const std::string Text::name = "text";

std::string Text::str     (void) const { return m_content; }
std::string Text::getName    (void) const { return name; }

