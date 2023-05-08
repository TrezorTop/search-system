#ifndef SEARCHSYSTEM_SEARCHSYSTEM_H
#define SEARCHSYSTEM_SEARCHSYSTEM_H

#include <map>
#include <string>
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

  public:
    DocumentsMap GetDocumentsMap();
    void SetDocumentsMap(DocumentsMap documentsMap);
    std::vector<std::pair<std::string, Document>> GetDocumentsWithQuery(const std::string& a);
};

#endif  // SEARCHSYSTEM_SEARCHSYSTEM_H
