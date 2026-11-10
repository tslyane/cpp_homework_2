#pragma once
#include <stdexcept>
#include <string>

class FleetError : public std::runtime_error {
 public:
  FleetError(const std::string& message) : std::runtime_error(message) {}
};

class InspectionError : public FleetError {
 public:
  InspectionError(const std::string& message) : FleetError(message) {}
};

class CommandError : public FleetError {
 public:
  CommandError(const std::string& message) : FleetError(message) {}
};