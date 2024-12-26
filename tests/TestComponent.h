#pragma once

#include "Components/Component.h"
#include "EntityManager.h"
#include "Interface.h"
#include <gtest/gtest.h>
#include <stdexcept>

struct TestComponent : public Component {
  TestComponent(int val) : value(val) {}
  TestComponent() = default;

  int value;
};

struct TestComponent2 : public Component {
  TestComponent2(int value) : value(value) {}
  TestComponent2() = default;

  int value;
};
