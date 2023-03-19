#include "main.hpp"
#include "configuration.hpp"
#include "fileError.hpp"
#include "syntaxError.hpp"
#include "page.hpp"

/**
 * Function tries to parse command line arguments provided to program.
 * Returns true if parameters are valid and inFileName was set.
 * The constants in this function serve merely to enumerate all the possible
 * ways of invoking the program, changing any one of the constants would
 * require that the whole function is completely rewritten.
 *
 * @param[in] argc from main
 * 
 * @param[in] argv from main
 * 
 * @param[out] inFileName filename of input file, this is guaranteed to be set
 * if the function return true
 * 
 * @param[out] outFileName filename of output file, if none is provided as
 * command line parameter, then this value is left unchanged
 *
 * @param[out] confFileName filename of configuration file, if none is provided
 * as command line parameter, then this value is left unchanged
 */

static bool resolveArguments(int argc, char * argv[],
                      std::string & inFileName,
                      std::string & outFileName,
                      std::string & confFileName)
{
    int switchPos = 2;
    for ( ; switchPos < argc; switchPos++)
        if (std::string(argv[switchPos]) == CONFIG_FILE_SWITCH) break;
    switch (argc) {
    case  4: if (switchPos != 2) return false;
             inFileName   = argv[1];
             confFileName = argv[3];
             break;
    case  5: if (switchPos == 3) {
                 confFileName = argv[4];
             } else if (switchPos == 2) {
                 inFileName   = argv[1];
                 confFileName = argv[3];
                 outFileName  = argv[4];
                 break;
             } else return false;
    case  3: outFileName = argv[2];
    case  2: inFileName  = argv[1];
             break;
    default: return false; 
    }
    return true;
}

/**
 * Takes filename, returns origName prefixed with DERIVED_FILENAME_PREFIX\n
 * Checks whether file with derived name exists, if such file already exists
 * FileError is thrown.
 *
 * @param[in] origName filename to be prefixed
 */

static std::string deriveFileName (const std::string & origName)
{
    std::string newName = origName;
    size_t pos = newName.find_last_of("/");
    newName.insert(pos +1, DERIVED_FILENAME_PREFIX);
    struct stat buffer;   
    if (stat (newName.c_str(), & buffer) == 0)
        throw FileError(newName + DERIVED_FILENAME_EXISTS_MESSAGE);
    return newName;
}

int main(int argc, char** argv)
{
    std::string inFileName, outFileName, confFileName;
    if ( ! resolveArguments (argc, argv,
            inFileName, outFileName, confFileName) )
    {
        std::cerr << USAGE_MESSAGE << std::endl;
        return BAD_ARGUMENT;
    }
    Configuration cfg;
    try {
        cfg.readFile(confFileName);
    } catch (const FileError & e) {
        std::cerr << e.what << std::endl;
    }
    try {
        if (outFileName == "") outFileName = deriveFileName (inFileName);
        Page page (inFileName);
        page.writeToFile (outFileName, cfg);
    } catch (FileError & e) {
        std::cerr << FATAL_ERROR << e.what << std::endl;
        return FILE_ERROR;
    } catch (SyntaxError & e) {
        std::cerr << FATAL_ERROR << e.what << std::endl;
        return SYNTAX_ERROR;
    }
    return SUCCESS;
}

