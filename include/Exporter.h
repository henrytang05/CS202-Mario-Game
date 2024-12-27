#pragma once

#include "json.h"
using json = nlohmann::json;

class EntityManager;

class IExporter;

enum class ExportableType {
  EntityManager,
};

class IExportable {
public:
  virtual ~IExportable() = default;
  virtual void accept(IExporter &e) = 0;
};

class IExporter {
public:
  virtual ~IExporter() = default;
  virtual void visit(EntityManager &e) = 0;

  virtual void save() = 0;
};

class JSONExporter : public IExporter {
public:
  void visit(EntityManager &e) override;
  void save() override;

private:
  std::unordered_map<ExportableType, json> jsonMap;
  std::unordered_map<ExportableType, std::string> pathNameMap;
};
