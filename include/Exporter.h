#pragma once

#include "json.h"
using json = nlohmann::json;

class EntityManager;

class IVisitor;

enum class ExportableType {
  EntityManager,
};

class IExportable {
public:
  virtual ~IExportable() = default;
  virtual void accept(IVisitor &e) = 0;
};

class IVisitor {
public:
  virtual ~IVisitor() = default;
  virtual void visit(EntityManager &e) = 0;
};

class IExporter : public IVisitor {
public:
  virtual ~IExporter() = default;
  virtual void save() = 0;
};

class IImporter : public IVisitor {
public:
  virtual ~IImporter() = default;
  virtual void load() = 0;
};

class JSONExporter : public IExporter {
public:
  JSONExporter();
  void visit(EntityManager &e) override;
  void save() override;

private:
  std::unordered_map<ExportableType, json> jsonMap;
  std::unordered_map<ExportableType, std::string> pathNameMap;
};

class JSONImporter : public IImporter {
public:
  JSONImporter();
  void visit(EntityManager &e) override;
  void load() override;

private:
  std::unordered_map<ExportableType, json> jsonMap;
  std::unordered_map<ExportableType, std::string> pathNameMap;
};
