
#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "Errors.hpp"
#include "Inventory.hpp"
#include "Thing.hpp"
#include "Transport.hpp"

int readScore() {
  int score;
  if (!(std::cin >> score)) {
    throw CommandError("Invalid score");
  }
  return score;
}

double readEnergy() {
  double energy;
  if (!(std::cin >> energy)) {
    throw CommandError("Invalid energy");
  }
  return energy;
}

std::string readString() {
  std::string value;
  if (!(std::cin >> value)) {
    throw CommandError("Failed to read argument");
  }
  return value;
}

int main() {
  Fleet fleet;

  while (true) {
    std::string command;
    if (!(std::cin >> command)) {
      break;
    }

    try {
      if (command == "quit") {
        break;
      } else if (command == "list") {
        fleet.list();
      } else if (command == "energy") {
        fleet.energy();
      } else if (command == "novice") {
        fleet.novice();
      } else if (command == "show_focus") {
        fleet.showFocus();
      } else if (command == "count") {
        fleet.count();
      } else if (command == "focus") {
        std::string id = readString();
        if (!fleet.focus(id)) {
          throw CommandError("Wrong ID");
        }
      } else if (command == "remove") {
        std::string id = readString();
        if (!fleet.remove(id)) {
          throw CommandError("Wrong ID");
        }
      } else if (command == "add") {
        std::string type = readString();

        if (type == "helmet") {
          std::string id = readString();
          std::string name = readString();
          fleet.addThing(std::make_unique<Helmet>(id, name));

        } else if (type == "dock") {
          std::string id = readString();
          std::string name = readString();
          double energy = readEnergy();
          fleet.addThing(std::make_unique<Dock>(id, name, energy));

        } else if (type == "bike") {
          std::string id = readString();
          std::string name = readString();
          int score = readScore();
          fleet.addTransport(std::make_unique<Bike>(id, name, score));

        } else if (type == "scooter") {
          std::string id = readString();
          std::string name = readString();
          double energy = readEnergy();
          int score = readScore();
          fleet.addTransport(
              std::make_unique<ElectricScooter>(id, name, score, energy));

        } else if (type == "ebike") {
          std::string id = readString();
          std::string name = readString();
          double energy = readEnergy();
          int score = readScore();
          fleet.addTransport(
              std::make_unique<ElectricBike>(id, name, score, energy));

        } else {
          throw CommandError("Unknown item type");
        }
      } else {
        throw CommandError("Unknown command");
      }
    } catch (const FleetError& e) {
      std::cout << "Error: " << e.what() << '\n';

      if (!std::cin) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
  }

  return 0;
}
