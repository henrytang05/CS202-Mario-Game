#include "Exporter.h"
#include "Components/Component.h"
#include "Components/Components_include.h"
#include "EntityManager.h"

JSONExporter::JSONExporter() {
  typeJsonMap[ExportableType::ENTITY] = json();
  typeJsonMap[ExportableType::COMPONENT] = json();
  typeJsonMap[ExportableType::POSITION_COMPONENT] = json();
  typeJsonMap[ExportableType::ENTITY_MANAGER] = json();

  typePathMap[ExportableType::ENTITY] = "data/Entity.json";
  typePathMap[ExportableType::COMPONENT] = "data/Component.json";
  typePathMap[ExportableType::POSITION_COMPONENT] =
      "data/PositionComponent.json";
  typePathMap[ExportableType::ENTITY_MANAGER] = "data/EntityManager.json";
}

json &JSONExporter::getJSON(ExportableType type) { return typeJsonMap[type]; }

void JSONExporter::visit(AbstractEntity &entity) {
  json &j = getJSON(ExportableType::ENTITY);
  j["entities"][std::to_string(entity.getID())]["name"] = entity.getName();
  j["entities"][std::to_string(entity.getID())]["active"] = entity.isActive();
}

void JSONExporter::serialize() {
  for (auto &[type, j] : typeJsonMap) {
    std::string path = typePathMap[type];
    std::ofstream file;
    file.open(path);
    ASSERT(file.is_open(), "Failed to open file");
    file << j.dump(4);
    file.close();
  }
}

void JSONExporter::visit(EntityManager &component) {}

void JSONExporter::visit(Component &component) { component.accept(*this); }

void JSONExporter::visit(PositionComponent &component) {
  json &j = getJSON(ExportableType::POSITION_COMPONENT);
  j["components"]["PositionComponent"]["x"] = component.x;
  j["components"]["PositionComponent"]["y"] = component.y;
}
