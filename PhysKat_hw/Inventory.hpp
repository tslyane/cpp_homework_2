#pragma once
#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>

#include "Registry.hpp"

class Transport;
class ServiceCenter;
class ModelSpec;

class InventoryItem {
 private:
  std::string itemId_;
  std::string itemName_;

 public:
  virtual std::string inventoryId() const = 0;
  virtual std::string name() const = 0;
  virtual std::string describe() const = 0;

  std::string getId() const;
  std::string getName() const;

  virtual ~InventoryItem() = default;

  InventoryItem(std::string id, std::string name);
};

class EnergyConsumer {
 public:
  virtual double dailyEnergy() const = 0;
  virtual ~EnergyConsumer() = default;
};

class Fleet {
 private:
  Registry<std::shared_ptr<InventoryItem>, 1000> items_;
  std::weak_ptr<InventoryItem> focusedItem_;
  std::unordered_map<std::string, std::shared_ptr<ModelSpec>> modelSpecs_;

  void hasId(const std::string& id) const;

 public:
  void addTransport(std::unique_ptr<Transport> item);
  void addThing(std::unique_ptr<InventoryItem> item);
  bool remove(const std::string& id);
  void list() const;
  void energy() const;
  void novice() const;
  bool focus(const std::string& id);
  void showFocus() const;
  void count() const;
};

bool operator<(const InventoryItem& lhs, const InventoryItem& rhs);

std::ostream& operator<<(std::ostream& os, const InventoryItem& item);