#include "ServiceCenter.hpp"

#include <cctype>
#include <cstddef>
#include <string>

#include "Errors.hpp"

void ServiceCenter::inspect(const Transport& transport) const {
  std::string name = transport.name();
  for (std::size_t i = 0; i < name.size(); i++) {
    unsigned char symb = name[i];
    name[i] = std::tolower(symb);
  }
  if (name.find("broken") == std::string::npos) {
    return;
  }
  throw InspectionError("Inspection failed");
}