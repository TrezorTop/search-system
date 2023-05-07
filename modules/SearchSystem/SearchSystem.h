#ifndef SEARCHSYSTEM_SEARCHSYSTEM_H
#define SEARCHSYSTEM_SEARCHSYSTEM_H

#include <map>
#include <string>

struct Document {
    std::string value;
    double relevance;
};

typedef std::map<std::string, Document> DocumentsMap;

class SearchSystem {
  private:
    DocumentsMap documentsMap;

  public:
    DocumentsMap GetDocumentsMap();
    void SetDocumentsMap(DocumentsMap documentsMap);
};

#endif  // SEARCHSYSTEM_SEARCHSYSTEM_H
