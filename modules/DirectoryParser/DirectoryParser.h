#ifndef SEARCHSYSTEM_DIRECTORYPARSER_H
#define SEARCHSYSTEM_DIRECTORYPARSER_H

#include <map>
#include <string>

typedef std::map<std::string, std::string> FilesMap;

class DirectoryParser {
  private:
    FilesMap filesMap;

  public:
    void InitializeFilesInDirectory();
    FilesMap GetFilesMap();
};

#endif  // SEARCHSYSTEM_DIRECTORYPARSER_H
