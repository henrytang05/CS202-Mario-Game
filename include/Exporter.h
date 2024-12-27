#ifndef EXPORTER_H
#define EXPORTER_H
#include "Interface.h"
#include <json.h>
#include <unordered_map>

// for convenience
using json = nlohmann::json;

class Exporter;
class Component;
class PositionComponent;
class AbstractEntity;

enum class ExportableType {
  ENTITY,
  COMPONENT,
  POSITION_COMPONENT,
  ENTITY_MANAGER
};

class Exportable {
public:
  virtual ~Exportable() = default;
  virtual void accept(Exporter &exporter) = 0;
};

template <typename T> class JSONExportable : public Exportable {
public:
  virtual void to_json(json &j) const = 0;
  virtual void from_json(const json &, T &) = 0;
};

class Exporter {
public:
  virtual ~Exporter() = default;
  virtual void visit(AbstractEntity &entity) = 0;
  virtual void visit(EntityManager &EM) = 0;
  virtual void visit(Component &component) = 0;
  virtual void visit(PositionComponent &component) = 0;

  virtual void serialize() = 0;
};

class JSONExporter : public Exporter {
public:
  JSONExporter();
  ~JSONExporter() = default;
  void visit(AbstractEntity &entity) override;
  void visit(PositionComponent &component) override;
  void visit(EntityManager &EM) override;
  void visit(Component &component) override;

  json &getJSON(ExportableType type);

  void serialize() override;

private:
  json j;

  std::unordered_map<ExportableType, json> typeJsonMap;
  std::unordered_map<ExportableType, std::string> typePathMap;
};

#endif // EXPORTER_H
