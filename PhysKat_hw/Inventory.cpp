#include "Inventory.hpp"

#include <iomanip>
#include <iostream>
#include <utility>

#include "Errors.hpp"
#include "ServiceCenter.hpp"
#include "Thing.hpp"
#include "Transport.hpp"

InventoryItem::InventoryItem(std::string id, std::string newName)
    : itemId_(id), itemName_(newName) {}

std::string InventoryItem::getId() const { return itemId_; }

std::string InventoryItem::getName() const { return itemName_; }

void Fleet::hasId(const std::string& id) const {
  if (id.empty()) {
    throw CommandError("Empty ID");
  } else if (items_.find(id) != -1) {
    throw CommandError("Non-unique ID");
  }
}

void Fleet::addTransport(std::unique_ptr<Transport> item) {
  if (item == nullptr) {
    throw CommandError("Empty transport pointer");
  }
  hasId(item->inventoryId());
  ServiceCenter serviceCenter;
  serviceCenter.inspect(*item);
  std::string modelName = item->name();
  auto it = modelSpecs_.find(modelName);
  bool isNewModel = (it == modelSpecs_.end());
  std::shared_ptr<ModelSpec> spec;
  if (isNewModel) {
    spec = std::make_shared<ModelSpec>();
    spec->modelName = modelName;
  } else {
    spec = it->second;
  }
  item->setModelSpec(spec);
  std::shared_ptr<InventoryItem> accepted(std::move(item));
  if (!items_.add(std::move(accepted))) {
    throw CommandError("Registry is full");
  }
  if (isNewModel) {
    modelSpecs_.emplace(modelName, std::move(spec));
  }
}

void Fleet::addThing(std::unique_ptr<InventoryItem> item) {
  if (item == nullptr) {
    throw CommandError("Empty thing pointer");
  }
  hasId(item->inventoryId());
  std::shared_ptr<InventoryItem> accepted(std::move(item));
  if (!items_.add(std::move(accepted))) {
    throw CommandError("Registry is full");
  }
}

bool Fleet::remove(const std::string& id) {
  int index = items_.find(id);
  if (index == -1) {
    return false;
  }
  items_.remove(index);
  return true;
}

void Fleet::list() const {
  for (std::size_t i = 0; i < items_.size(); i++) {
    std::cout << *items_[i] << '\n';
  }
}

template <typename Container>
double calculateEnergy(const Container& items) {
  double sum = 0;
  for (std::size_t i = 0; i < items.size(); i++) {
    auto ptr = std::dynamic_pointer_cast<EnergyConsumer>(items[i]);
    if (ptr != nullptr) {
      sum += ptr->dailyEnergy();
    }
  }
  return sum;
}

void Fleet::energy() const {
  double sum = calculateEnergy(items_);
  std::cout << std::fixed << std::setprecision(1) << sum << '\n';
}

void Fleet::novice() const {
  for (std::size_t i = 0; i < items_.size(); i++) {
    auto ptr = std::dynamic_pointer_cast<Transport>(items_[i]);
    if (ptr != nullptr && ptr->isSuitableForNovice()) {
      std::cout << ptr->describe() << '\n';
    }
  }
}

bool Fleet::focus(const std::string& id) {
  int index = items_.find(id);
  if (index == -1) {
    return false;
  }
  focusedItem_ = items_[index];
  return true;
}

void Fleet::showFocus() const {
  auto ptr = focusedItem_.lock();
  if (ptr == nullptr) {
    throw CommandError("Focused item doesn't exist");
  }
  std::cout << ptr->describe() << '\n';
}

void Fleet::count() const {
  int bikes = 0;
  int electricBikes = 0;
  int scooters = 0;
  int helmets = 0;
  int docks = 0;

  for (std::size_t i = 0; i < items_.size(); i++) {
    auto item = items_[i];

    if (std::dynamic_pointer_cast<ElectricBike>(item)) {
      electricBikes++;
    } else if (std::dynamic_pointer_cast<Bike>(item)) {
      bikes++;
    } else if (std::dynamic_pointer_cast<ElectricScooter>(item)) {
      scooters++;
    } else if (std::dynamic_pointer_cast<Helmet>(item)) {
      helmets++;
    } else if (std::dynamic_pointer_cast<Dock>(item)) {
      docks++;
    }
  }

  std::cout << "Bikes: " << bikes << '\n';
  std::cout << "Electric bikes: " << electricBikes << '\n';
  std::cout << "Electric scooters: " << scooters << '\n';
  std::cout << "Helmets: " << helmets << '\n';
  std::cout << "Docks: " << docks << '\n';
  std::cout << "Total: " << items_.size() << '\n';
}

bool operator<(const InventoryItem& lhs, const InventoryItem& rhs) {
  return lhs.inventoryId() < rhs.inventoryId();
}

std::ostream& operator<<(std::ostream& os, const InventoryItem& item) {
  os << "ID: " << item.inventoryId() << ' ' << "Name: " << item.name();
  return os;
}