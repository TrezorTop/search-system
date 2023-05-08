#include "SearchSystem.h"

#include <cmath>
#include <iostream>
#include <iterator>
#include <sstream>
#include <unordered_set>

DocumentsMap SearchSystem::GetDocumentsMap() {
  return this->documentsMap;
}

void SearchSystem::SetDocumentsMap(DocumentsMap documentsMap) {
  this->documentsMap = std::move(documentsMap);
}

std::vector<std::pair<std::string, Document>> SearchSystem::GetDocumentsWithQuery(const std::string& query) {
  // create an istringstream to split the string into words
  std::istringstream iss(query);
  // collections of unique strings.
  // std::unordered_set has faster lookup times than std::vector for large
  std::unordered_set<std::string> subStrings(
      std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>()
  );

  DocumentsMap result;

  std::map<std::string, Word> stringIdfMap;

  for (const std::string& string : subStrings) {
    std::vector<std::string> documentsWithString;

    for (const auto& document : this->documentsMap) {
      if (document.second.value.find(string) != std::string::npos) {
        documentsWithString.push_back(document.first);
        result.insert(document);
      }
    }

    size_t foundDocuments = documentsWithString.size();

    double idf = std::log(this->documentsMap.size() / static_cast<double>(foundDocuments));

    if (foundDocuments > 0) {
      stringIdfMap.insert({string, {documentsWithString, idf}});
    };
  }

  for (const auto& string : stringIdfMap) {
    for (auto document : string.second.documents) {
      // create an istringstream to split the string into words
      std::istringstream iss(this->documentsMap.find(document)->second.value);
      // collections of unique strings.
      std::vector<std::string> subStrings(
          std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>()
      );

      double tf =
          std::count(subStrings.begin(), subStrings.end(), string.first) / static_cast<double>(subStrings.size());

      double sumOfIdfAndTf = tf * string.second.idf;

      result.find(document)->second.relevance += sumOfIdfAndTf;
    }
  }

  // Create a vector of pairs from the map
  std::vector<std::pair<std::string, Document>> output(result.begin(), result.end());

  std::sort(output.begin(), output.end(), [](const auto& a, const auto& b) {
    return a.second.relevance > b.second.relevance;
  });

  return output;
}
