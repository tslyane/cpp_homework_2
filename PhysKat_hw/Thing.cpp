#include "Thing.hpp"

#include "Errors.hpp"

Helmet::Helmet(std::string id, std::string name) : InventoryItem(id, name) {}

std::string Helmet::inventoryId() const { return getId(); }

std::string Helmet::name() const { return getName(); }

std::string Helmet::describe() const { return getId() + " " + getName(); }

Dock::Dock(std::string id, std::string name, double energy)
    : InventoryItem(id, name), energy_(energy) {
  if (!(energy >= 0)) {
    throw CommandError("Energy must be non-negative");
  }
}

std::string Dock::inventoryId() const { return getId(); }

std::string Dock::name() const { return getName(); }

std::string Dock::describe() const {
  return getId() + " " + getName() + " " + std::to_string(dailyEnergy());
}

double Dock::dailyEnergy() const { return energy_; }