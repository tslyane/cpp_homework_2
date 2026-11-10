#pragma once
#include <memory>
#include <string>

#include "Inventory.hpp"

class ModelSpec {
 public:
  std::string modelName;
};

class Transport : public InventoryItem {
 private:
  int noviceScore_;
  std::shared_ptr<ModelSpec> modelSpec_;

 public:
  bool isSuitableForNovice() const;
  int getNoviceScore() const;
  void setModelSpec(std::shared_ptr<ModelSpec> spec);

  Transport(std::string id, std::string newName, int noviceScore);
};

class Bike : public Transport {
 public:
  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;

  Bike(std::string id, std::string name, int noviceScore);
};

class ElectricBike : public Bike, public EnergyConsumer {
 private:
  double energy_;

 public:
  ElectricBike(std::string id, std::string name, int noviceScore,
               double energy);

  double dailyEnergy() const override;
};

class ElectricScooter : public Transport, public EnergyConsumer {
 private:
  double energy_;

 public:
  double dailyEnergy() const override;
  std::string inventoryId() const override;
  std::string name() const override;
  std::string describe() const override;

  ElectricScooter(std::string id, std::string name, int noviceScore,
                  double energy);
};