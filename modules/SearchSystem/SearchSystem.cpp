#include "SearchSystem.h"

#include <cmath>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <unordered_set>

DocumentsMap SearchSystem::GetDocumentsMap() {
  return this->documentsMap;
}

void SearchSystem::SetDocumentsMap(DocumentsMap documentsMap) {
  this->documentsMap = std::move(documentsMap);
}

template <typename T>
T SearchSystem::GetSubStrings(std::string string) {
  // create an istringstream to split the string into words
  std::istringstream iss(string);
  // collections of unique strings.
  // std::unordered_set has faster lookup times than std::vector for large
  T subStrings(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
  return subStrings;
}

std::vector<std::pair<std::string, Document>> SearchSystem::GetDocumentsWithQuery(const std::string& query) {
  auto subStrings = this->GetSubStrings<std::unordered_set<std::string>>(query);

  DocumentsMap foundDocumentsMap;

  // since we are not sorting wordIdfMap and we only need to look up elements by key, we can use a std::unordered_map
  // instead of a std::map for potentially better performance
  std::unordered_map<std::string, Word> wordIdfMap;

  // use const auto& instead of const std::string& to avoid unnecessary copies
  for (const auto& word : subStrings) {
    std::vector<std::string> currentWordDocuments;
    // we know the maximum size of the vector beforehand, we can allocate the required memory upfront to avoid
    // unnecessary reallocations
    currentWordDocuments.reserve(this->documentsMap.size());

    for (const auto& document : this->documentsMap) {
      if (document.second.value.find(word) != std::string::npos) {
        // emplace_back is more efficient because it constructs the object in-place instead of making a copy
        currentWordDocuments.emplace_back(document.first);
        // this constructs the Document object in-place in the map, avoiding the extra copy
        foundDocumentsMap.emplace(document.first, Document(document.second.value));
      }
    }

    size_t currentWordDocumentsSize = currentWordDocuments.size();

    double idf = std::log(this->documentsMap.size() / static_cast<double>(currentWordDocumentsSize));

    if (currentWordDocumentsSize > 0) {
      // use emplace instead of insert to construct the Document object in-place in the map. This avoids an extra copy
      // and can be more efficient
      wordIdfMap.emplace(word, Word{currentWordDocuments, idf});
    };
  }

  for (const auto& word : wordIdfMap) {
    for (const auto& document : word.second.documents) {
      auto subStrings = this->GetSubStrings<std::vector<std::string>>(query);

      double tf = std::count(subStrings.begin(), subStrings.end(), word.first) / static_cast<double>(subStrings.size());

      double sumOfIdfAndTf = tf * word.second.idf;

      foundDocumentsMap.find(document)->second.relevance += sumOfIdfAndTf;
    }
  }

  // Create a vector of pairs from the map
  std::vector<std::pair<std::string, Document>> output;
  output.reserve(foundDocumentsMap.size());
  // this will move the elements from foundDocumentsMap into output, which can be more efficient than copying them
  std::move(foundDocumentsMap.begin(), foundDocumentsMap.end(), std::back_inserter(output));

  std::sort(output.begin(), output.end(), [](const auto& a, const auto& b) {
    return a.second.relevance > b.second.relevance;
  });

  return output;
}
