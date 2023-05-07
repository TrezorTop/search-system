#include <iostream>

#include "modules/DirectoryParser/DirectoryParser.h"
#include "modules/SearchSystem/SearchSystem.h"

DocumentsMap transformMap(const FilesMap& inputMap) {
  DocumentsMap outputMap;
  std::transform(inputMap.begin(), inputMap.end(), std::inserter(outputMap, outputMap.begin()), [](const auto& elem) {
    return std::make_pair(elem.first, Document{elem.second, 0.0});
  });
  return outputMap;
}

int main() {
  DirectoryParser directoryParser;
  directoryParser.InitializeFilesInDirectory();

  DocumentsMap documentsMap = transformMap(directoryParser.GetFilesMap());

  SearchSystem searchSystem;
  searchSystem.SetDocumentsMap(documentsMap);

  for (auto const& [key, value] : searchSystem.GetDocumentsMap()) {
    std::cout << value.value << '\n';
  }

  return 0;
}