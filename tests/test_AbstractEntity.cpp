#include "EntityManager.h"
#include "TestComponent.h"
#include <gtest/gtest.h>

class AbstractEntityTest : public testing::Test {
protected:
  void SetUp() override { std::cout << "\nSetUp called\n"; }

  void TearDown() override { std::cout << "TearDown called\n"; }

  EntityManager em;
  Shared<AbstractEntity> entity = em.createEntity("TestEntity").lock();
};

TEST_F(AbstractEntityTest, testHas) {
  ASSERT_FALSE(entity->hasComponent<TestComponent>());
}

TEST_F(AbstractEntityTest, testAddComponent) {
  auto &T = entity->addComponent<TestComponent>(5);
  ASSERT_TRUE(entity->hasComponent<TestComponent>());
  ASSERT_EQ(T.value, 5);
}

TEST_F(AbstractEntityTest, testAddDuplicateComponent) {
  auto &T = entity->addComponent<TestComponent>(5);
  ASSERT_THROW(entity->addComponent<TestComponent>(5), std::runtime_error);
}

TEST_F(AbstractEntityTest, testEntityHasComponent2) {
  auto &T = entity->addComponent<TestComponent>(5);
  ASSERT_TRUE(entity->hasComponent<TestComponent>());
}

TEST_F(AbstractEntityTest, testEntityHasAllComponents2) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->addComponent<TestComponent2>(5);
  bool hasAll = entity->hasAllComponents<TestComponent, TestComponent2>();
  ASSERT_TRUE(hasAll);
}

TEST_F(AbstractEntityTest, testGetComponent1) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->getComponent<TestComponent>();
  ASSERT_EQ(T2.value, 5);
}

TEST_F(AbstractEntityTest, testGetComponent2) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->getComponent<TestComponent>();
  T2.value = 10;
  ASSERT_EQ(T.value, T2.value);
}

TEST_F(AbstractEntityTest, testGetComponent3) {
  ASSERT_THROW(entity->getComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testRemoveComponent) {
  auto &T = entity->addComponent<TestComponent>(5);
  ASSERT_TRUE(entity->hasComponent<TestComponent>());
  entity->removeComponent<TestComponent>();
  ASSERT_FALSE(entity->hasComponent<TestComponent>());
}

TEST_F(AbstractEntityTest, testRemoveComponent2) {
  ASSERT_THROW(entity->removeComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testRemoveComponent3) {
  auto &T = entity->addComponent<TestComponent>(5);
  entity->removeComponent<TestComponent>();
  ASSERT_THROW(entity->removeComponent<TestComponent>(), std::runtime_error);
  ASSERT_THROW(entity->getComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testRemoveComponent4) {
  auto &T = entity->addComponent<TestComponent>(5);
  entity->removeComponent<TestComponent>();
  ASSERT_THROW(entity->removeComponent<TestComponent>(), std::runtime_error);
  ASSERT_THROW(entity->getComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testRemoveComponent5) {
  auto &T = entity->addComponent<TestComponent>(5);
  entity->removeComponent<TestComponent>();
  ASSERT_THROW(entity->removeComponent<TestComponent>(), std::runtime_error);
  ASSERT_THROW(entity->getComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testModifyComponent) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->modifyComponent<TestComponent>(10);
  ASSERT_EQ(T2.value, 10);
}

TEST_F(AbstractEntityTest, testModifyComponent2) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->modifyComponent<TestComponent>(10);
  ASSERT_EQ(T2.value, 10);
  auto &T3 = entity->getComponent<TestComponent>();
  ASSERT_EQ(T3.value, 10);
}

TEST_F(AbstractEntityTest, testModifyComponent3) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->modifyComponent<TestComponent>(10);
  auto &T3 = entity->getComponent<TestComponent>();
  T3.value = 15;
  ASSERT_EQ(T2.value, T3.value);
}

TEST_F(AbstractEntityTest, testModifyComponent4) {
  ASSERT_THROW(entity->modifyComponent<TestComponent>(10), std::runtime_error);
}

TEST_F(AbstractEntityTest, testDestroyEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  ASSERT_TRUE(entity->hasComponent<TestComponent>());
  em.destroyEntity(entity);
  EXPECT_ANY_THROW(entity->hasComponent<TestComponent>());
}

TEST_F(AbstractEntityTest, testDestroyEntityAndUsed) {
  auto _e2 = em.createEntity("TestEntity2");
  Shared<AbstractEntity> e2 = _e2.lock();

  auto &T = e2->addComponent<TestComponent>(5);
  ASSERT_TRUE(e2->hasComponent<TestComponent>());

  ASSERT_TRUE(e2->isActive());
  e2->destroy();
  EXPECT_FALSE(e2->isActive());
  // EXPECT_ANY_THROW(e2->getName());
  EXPECT_ANY_THROW(e2->hasComponent<TestComponent>());
  EXPECT_ANY_THROW(e2->getComponent<TestComponent>());
  EXPECT_ANY_THROW(e2->addComponent<TestComponent>(5));
  EXPECT_ANY_THROW(e2->removeComponent<TestComponent>());
  EXPECT_ANY_THROW(e2->modifyComponent<TestComponent>(10));
}
