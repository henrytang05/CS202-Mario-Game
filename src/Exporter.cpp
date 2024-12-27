#include "Exporter.h"
#include "EntityManager.h"

JSONExporter::JSONExporter() {
  pathNameMap[ExportableType::EntityManager] = "data/EntityManager.json";
}

void JSONExporter::visit(EntityManager &e) {
  json j;
  j = e;
  jsonMap[ExportableType::EntityManager] = j;
}

void JSONExporter::save() {
  for (auto &[k, v] : jsonMap) {
    std::ofstream o(pathNameMap[k]);
    ASSERT(o.is_open(), "Failed to open file");
    o << v.dump(4);
    o.close();
  }
}

JSONImporter::JSONImporter() {
  pathNameMap[ExportableType::EntityManager] = "data/EntityManager.json";
}

void JSONImporter::visit(EntityManager &e) {
  throw std::runtime_error("Not implemented");
}

void JSONImporter::load() { throw std::runtime_error("Not implemented"); }
