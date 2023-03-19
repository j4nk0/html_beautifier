#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

//keywords in config file
/** Default keywords:\n
 * indentwidth\n
 * maxlinelen\n
 * mintextlen\n
 */
#define INDENTWIDTH_KEYWORD "indentwidth"
#define MAXLINELEN_KEYWORD  "maxlinelen"
#define MINTEXTLEN_KEYWORD  "mintextlen"

//default configuration :
#define DEFAULT_INDENTWIDTH   4
#define DEFAULT_MAXLINELEN  150
#define DEFAULT_MINTEXTLEN   20

/** Message to be displayed if config file was specified, but could not have been loaded */
#define CONFIG_FILE_ERROR_MESSAGE "config-file could not be read, continuing with default configuration\n"

/**
 * Class contains settings from config-file.
 * Each configurable option is represented by:
 * \n- private attribute
 * \n- default value macro
 * \n- keyword macro - specifies which keyword to use in config file
 * \n- const getter
 * \n- setter that takes and return istream reference
 * \n- one mapping of keyword to own setter function in setter map
 */

class Configuration
{
public:
    Configuration (void);
    /**
     * Loads configuration from the file of given name.
     * Changes only those attributes of Configuration that are
     * correctly recognized in config file.\n
     * If the config file is to be interpretted correctly,
     * it must have the following structure:\n
     * \n- if there is a keyword on a line,
     * it must be the first word on that line,
     * otherwise its meaning will be ignored
     * \n- the keyword must be immediatelly followed by
     * valid value of corresponding option, otherwise it will be ignored.
     * @param[in] filename the name of config file to load
     */
    Configuration & readFile (const std::string & filename);
    uint getIndentWidth (void) const;
    uint getMaxLineLen  (void) const;
    uint getMinTextLen  (void) const;
private:
    std::istream & setIndentWidth (std::istream & is);
    std::istream & setMaxLineLen  (std::istream & is);
    std::istream & setMinTextLen  (std::istream & is);

    int m_indentWidth;
    int m_maxLineLen;
    int m_minTextLen;
    /** Maps from keyword to setter of the corresponding attribute */
    static const std::unordered_map<std::string,
        std::istream & (Configuration::*)(std::istream &)> setter;
};

#endif /* CONFIGURATION_HPP */

