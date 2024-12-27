#include "Exporter.h"
#include "EntityManager.h"

void JSONExporter::visit(EntityManager &e) {
  json j;
  j = e;
  jsonMap[ExportableType::EntityManager] = j;
  pathNameMap[ExportableType::EntityManager] = "data/EntityManager.json";
}

void JSONExporter::save() {
  for (auto &[k, v] : jsonMap) {
    std::ofstream o(pathNameMap[k]);
    ASSERT(o.is_open(), "Failed to open file");
    o << v.dump(4);
    o.close();
  }
}
