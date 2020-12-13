#include "FileException.h"

//FileNotFound exception
FileNotFound::FileNotFound(std::string name) {this->fileName = fileName;}
std::string FileNotFound::getFileName() {return fileName;}

//FileWasModified
FileWasModified::FileWasModified(std::string fileName) {this->fileName = fileName;}
std::string FileWasModified::getFileModifiedName() {return fileName;}