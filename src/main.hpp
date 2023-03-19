#ifndef REFINE_HPP
#define REFINE_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>

/**
 * @mainpage refine HTML
 * 
 * This program beautifies HTML source code.\n
 *
 * Program should be called like:
 * 
 * gadijan input-file [output-file] [-c config-file]
 * 
 * Input file is first checked for errors and then
 * the source is formatted in accordance with settings specified in the config file.
 * 
 */

/** The command line switch prepending config-file */
#define CONFIG_FILE_SWITCH "-c"

#define DERIVED_FILENAME_PREFIX "~"

#define USAGE_MESSAGE "gajdijan: invalid argument\nUSAGE:\ngajdijan input-file [output-file] [-c config-file]"

#define DERIVED_FILENAME_EXISTS_MESSAGE ": file already exists, please specify output file name"

#define FATAL_ERROR "ERROR: "

// return values:
/** Return value */
#define SUCCESS         0
/** Return value */
#define BAD_ARGUMENT    1
/** Return value */
#define FILE_ERROR      2
/** Return value */
#define SYNTAX_ERROR      3

#endif /* REFINE_HPP */

