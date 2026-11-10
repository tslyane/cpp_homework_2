#pragma once
#include <string>

#include "Inventory.hpp"

class Helmet : public InventoryItem {
 public:
  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;

  Helmet(std::string id, std::string name);
};

class Dock : public InventoryItem, public EnergyConsumer {
 private:
  double energy_;

 public:
  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;
  double dailyEnergy() const override;

  Dock(std::string id, std::string name, double energy);
};