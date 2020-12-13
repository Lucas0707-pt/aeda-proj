#ifndef _FILEEXCEPTION_H
#define _FILEEXCEPTION_H

#include <string>

/**
 * Class holding the exception of a file not existing
 */
class FileNotFound
{
    std::string fileName;/**File Name that doesn't exist or isn't in the correct directory*/
public:
    /**
     * Constructor of the FileNotFound exception
     * @param name File name that wasn't opened
     */
    FileNotFound(std::string fileName);

    /**
     * Returns the file name that doesn't exist or isn't in the correct directory
     * @return File Name
     */
    std::string getFileName();
};

/**
 * Class holding the exception of a file being modified outside the program
 */

class FileWasModified
{
    std::string fileName; /**File Name that was modified outside the program*/
public:
    /**
     * Constructor of the FileWasModified exception
     * @param fileName File name that was edited
     */
    FileWasModified(std::string fileName);

    /**
     * Returns the file name that was modified outside the program
     * @return Element error
     */
    std::string getFileModifiedName();
};
#endif //_FILEEXCEPTION_H
