#include "../src/EntityManager.cpp"
#include "AbstractEntity.h"
#include "Components/Component.h"
#include "EntityManager.h"

#include <gtest/gtest.h>
#include <stdexcept>

struct TestComponent {
  TestComponent(int value) : value(value) {}
  TestComponent() = default;

  int value;
};

struct TestComponent2 {
  TestComponent2(int value) : value(value) {}
  TestComponent2() = default;

  int value;
};

class MyTest : public ::testing::Test {
protected:
  void SetUp() override { std::cout << "SetUp called\n"; }

  void TearDown() override { std::cout << "TearDown called\n"; }

  EntityManager em;
};

TEST_F(MyTest, testCreate) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  ASSERT_EQ(entity.getName(), "TestEntity");
}

TEST_F(MyTest, testGet) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  AbstractEntity &entity2 = em.getEntity("TestEntity");
  ASSERT_EQ(entity.getName(), entity2.getName());
}

TEST_F(MyTest, testGetEntityID) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  uint32_t id = em.getEntityID("TestEntity");
  uint32_t id2 = em.getEntityID(entity);
  ASSERT_EQ(entity.getID(), id);
  ASSERT_EQ(entity.getID(), id2);
}

TEST_F(MyTest, testHasComponent1) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  ASSERT_FALSE(em.hasComponent<TestComponent>(&entity));
}

TEST_F(MyTest, testHasAllComponents1) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  ASSERT_FALSE(em.hasAllComponents<TestComponent>(&entity));
}

TEST_F(MyTest, testAddComponent) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto T = em.addComponent<TestComponent>(&entity, 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(&entity));
  ASSERT_EQ(T.value, 5);
}

TEST_F(MyTest, testAddDuplicateComponent) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto T = em.addComponent<TestComponent>(&entity, 5);
  ASSERT_THROW(em.addComponent<TestComponent>(&entity, 5), std::runtime_error);
}

TEST_F(MyTest, testEntityHasComponent2) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto T = em.addComponent<TestComponent>(&entity, 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(&entity));
}

TEST_F(MyTest, testEntityHasAllComponents2) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto T = em.addComponent<TestComponent>(&entity, 5);
  auto T2 = em.addComponent<TestComponent2>(&entity, 5);
  bool hasAll = em.hasAllComponents<TestComponent, TestComponent2>(&entity);
  ASSERT_TRUE(hasAll);
}

TEST_F(MyTest, testGetComponent1) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto T = em.addComponent<TestComponent>(&entity, 5);
  auto T2 = em.getComponent<TestComponent>(&entity);
  ASSERT_EQ(T2.value, 5);
}

TEST_F(MyTest, testGetComponent2) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto &T = em.addComponent<TestComponent>(&entity, 5);
  auto &T2 = em.getComponent<TestComponent>(&entity);
  T2.value = 10;
  ASSERT_EQ(T.value, T2.value);
}

TEST_F(MyTest, testRemoveComponent) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto &T = em.addComponent<TestComponent>(&entity, 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(&entity));
  em.removeComponent<TestComponent>(&entity);
  ASSERT_FALSE(em.hasComponent<TestComponent>(&entity));
}

TEST_F(MyTest, testRemoveComponent2) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  ASSERT_THROW(em.removeComponent<TestComponent>(&entity), std::runtime_error);
}

TEST_F(MyTest, testRemoveComponent3) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto &T = em.addComponent<TestComponent>(&entity, 5);
  em.removeComponent<TestComponent>(&entity);
  ASSERT_THROW(em.removeComponent<TestComponent>(&entity), std::runtime_error);
  ASSERT_THROW(em.getComponent<TestComponent>(&entity), std::runtime_error);
}

TEST_F(MyTest, testModifyComponent1) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto &T = em.addComponent<TestComponent>(&entity, 5);
  auto &T2 = em.modifyComponent<TestComponent>(&entity, 10);
  ASSERT_EQ(T2.value, 10);

  auto &T3 = em.getComponent<TestComponent>(&entity);
  ASSERT_EQ(T3.value, 10);
}

TEST_F(MyTest, testModifyComponent) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto &T = em.addComponent<TestComponent>(&entity, 5);
  auto &T2 = em.modifyComponent<TestComponent>(&entity, 10);
  auto &T3 = em.getComponent<TestComponent>(&entity);
  T3.value = 15;
  ASSERT_EQ(T2.value, T3.value);
}

TEST_F(MyTest, testModifyComponent4) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  ASSERT_THROW(em.modifyComponent<TestComponent>(&entity, 10),
               std::runtime_error);
}

TEST_F(MyTest, testGetHasAll) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto &T = em.addComponent<TestComponent>(&entity, 5);
  auto &T2 = em.addComponent<TestComponent2>(&entity, 5);
  auto &entities = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities.size(), 1);
}

TEST_F(MyTest, testGetHasAll2) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto &T = em.addComponent<TestComponent>(&entity, 5);
  auto &T2 = em.addComponent<TestComponent2>(&entity, 5);
  auto &entities = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities.size(), 1);
  em.removeComponent<TestComponent>(&entity);
  auto &entities2 = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities2.size(), 0);
}

TEST_F(MyTest, testGetHasAll3) {
  AbstractEntity &entity = em.createEntity("TestEntity");
  auto &T = em.addComponent<TestComponent>(&entity, 5);
  auto &T2 = em.addComponent<TestComponent2>(&entity, 5);
  AbstractEntity &entity2 = em.createEntity("TestEntity2");
  auto &T3 = em.addComponent<TestComponent>(&entity2, 5);
  auto &T4 = em.addComponent<TestComponent2>(&entity2, 5);
  auto &entities = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities.size(), 2);
  em.removeComponent<TestComponent>(&entity2);
  auto &entities2 = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities2.size(), 1);
}
