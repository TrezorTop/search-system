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

  while (true) {
    std::cout << "Enter the search string" << '\n';

    std::string query;
    std::getline(std::cin, query);

    if (query.empty()) {
      std::cerr << "Error: invalid query" << '\n';
      continue;
    }

    std::vector<std::pair<std::string, Document>> result = searchSystem.GetDocumentsWithQuery(query);

    if (!result.size()) {
      std::cout << "No documents containing the given string found" << '\n';
      continue;
    }

    std::cout << "Result: " << '\n';
    for (auto& document : result) {
      std::cout << document.first << " [relevance: " << document.second.relevance << "]" << '\n';
    }
    std::cout << '\n';
  }

  return 0;
}