#ifndef EXPORTER_H
#define EXPORTER_H
#include <json.h>

// for convenience
using json = nlohmann::json;

class Exporter;

class Exportable {
public:
  virtual ~Exportable() = default;
  virtual void accept(class Exporter &exporter) = 0;
};

class Exporter {
public:
  virtual ~Exporter() = default;
  virtual void visit(class Exportable &exportable) = 0;
};

#endif // EXPORTER_H
