#include "DirectoryParser.h"

#include <dirent.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>

void DirectoryParser::InitializeFilesInDirectory() {
  DIR *dir;
  struct dirent *ent;

  std::string dirPath = std::filesystem::current_path().parent_path().string() + "/DocumentsExamples/";

  dir = opendir(dirPath.c_str());

  if (dir == nullptr) {
    throw std::runtime_error("Could not open directory: " + dirPath);
  }

  while ((ent = readdir(dir)) != nullptr) {
    if (!std::string(ent->d_name).ends_with(".txt")) continue;

    std::stringstream stringStream;

    std::ifstream fileIn;
    std::string filePath = dirPath + ent->d_name;

    fileIn.open(filePath, std::ofstream::in);

    if (!fileIn.is_open()) {
      std::cout << "Could not open file:" << '\n' << filePath << '\n';
      continue;
    }

    std::string fileString;

    stringStream << fileIn.rdbuf();
    this->filesMap.insert(std::make_pair(ent->d_name, stringStream.str()));

    fileIn.close();
  }
  closedir(dir);
}

FilesMap DirectoryParser::GetFilesMap() {
  return this->filesMap;
}
