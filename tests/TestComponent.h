#pragma once

#include "EntityManager.h"

#include "../src/EntityManager.cpp"
#include "Interface.h"
#include <gtest/gtest.h>
#include <stdexcept>
struct TestComponent : public IComponent {
  TestComponent(int val) : value(val) {}
  TestComponent() = default;

  int value;
};

struct TestComponent2 : public IComponent {
  TestComponent2(int value) : value(value) {}
  TestComponent2() = default;

  int value;
};
