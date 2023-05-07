#include "SearchSystem.h"

DocumentsMap SearchSystem::GetDocumentsMap() {
  return this->documentsMap;
}

void SearchSystem::SetDocumentsMap(DocumentsMap documentsMap) {
  this->documentsMap = std::move(documentsMap);
}