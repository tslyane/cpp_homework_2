#include "Transport.hpp"

#include <utility>

#include "Errors.hpp"

Transport::Transport(std::string id, std::string newName, int noviceScore)
    : InventoryItem(id, newName), noviceScore_(noviceScore) {
  if (noviceScore < 1 || noviceScore > 10) {
    throw CommandError("Score must be between 1 and 10");
  }
}

bool Transport::isSuitableForNovice() const { return noviceScore_ >= 6; }

int Transport::getNoviceScore() const { return noviceScore_; }

void Transport::setModelSpec(std::shared_ptr<ModelSpec> spec) {
  modelSpec_ = std::move(spec);
}

Bike::Bike(std::string id, std::string name, int noviceScore)
    : Transport(id, name, noviceScore) {}

std::string Bike::inventoryId() const { return getId(); }

std::string Bike::name() const { return getName(); }

std::string Bike::describe() const {
  return getId() + " " + getName() + " " + std::to_string(getNoviceScore());
}

ElectricBike::ElectricBike(std::string id, std::string name, int noviceScore,
                           double energy)
    : Bike(id, name, noviceScore), energy_(energy) {
  if (!(energy >= 0)) {
    throw CommandError("Energy must be non-negative");
  }
}

double ElectricBike::dailyEnergy() const { return energy_; }

ElectricScooter::ElectricScooter(std::string id, std::string name,
                                 int noviceScore, double energy)
    : Transport(id, name, noviceScore), energy_(energy) {
  if (!(energy >= 0)) {
    throw CommandError("Energy must be non-negative");
  }
}

double ElectricScooter::dailyEnergy() const { return energy_; }

std::string ElectricScooter::inventoryId() const { return getId(); }

std::string ElectricScooter::name() const { return getName(); }

std::string ElectricScooter::describe() const {
  return getId() + " " + getName() + " " + std::to_string(getNoviceScore()) +
         " " + std::to_string(energy_);
}