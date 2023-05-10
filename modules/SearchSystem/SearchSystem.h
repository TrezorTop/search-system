#ifndef SEARCHSYSTEM_SEARCHSYSTEM_H
#define SEARCHSYSTEM_SEARCHSYSTEM_H

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

struct Document {
    std::string value;
    double relevance;
};

struct Word {
    std::vector<std::string> documents;
    double idf;
};

typedef std::map<std::string, Document> DocumentsMap;

class SearchSystem {
  private:
    DocumentsMap documentsMap;
    template <typename T>
    T GetSubStrings(std::string string);
    std::unordered_map<std::string, Word> CalculateIdfForEachWord();

  public:
    DocumentsMap GetDocumentsMap();
    void SetDocumentsMap(DocumentsMap documentsMap);
    std::vector<std::pair<std::string, Document>> GetDocumentsWithQuery(const std::string& a);
};

#endif  // SEARCHSYSTEM_SEARCHSYSTEM_H
