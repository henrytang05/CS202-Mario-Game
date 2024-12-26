#include <gtest/gtest.h>

#include "EntityManager.h"
#include "TestComponent.h"

class EntityMangerTest : public ::testing::Test {
protected:
  void SetUp() override { std::cout << "SetUp called\n"; }

  void TearDown() override {
    std::cout << "TearDown called\n";
    em.reset();
  }

  EntityManager em;
  Weak<AbstractEntity> entity = em.createEntity("TestEntity");
};

TEST(TestCreateEntity, testCreate) {
  EntityManager em;
  auto entity = em.createEntity("TestEntity");
  ASSERT_EQ(entity.lock()->getName(), "TestEntity");
}

TEST(TestCreateEntity, testCreateDuplicatedName) {
  EntityManager em;
  auto entity = em.createEntity("TestEntity");
  ASSERT_EQ(entity.lock()->getName(), "TestEntity");
  ASSERT_NO_THROW(auto entity2 = em.createEntity("TestEntity"););
}

TEST_F(EntityMangerTest, testGetByName) {
  std::vector<Weak<AbstractEntity>> res = em.getEntityByName("TestEntity");
  ASSERT_EQ(res.size(), 1);
  ASSERT_EQ(entity.lock()->getName(), res[0].lock()->getName());
}

TEST_F(EntityMangerTest, testGetByID) {
  auto entity2 = em.getEntityRef(entity.lock()->getID());
  ASSERT_EQ(entity.lock()->getName(), entity2.getName());

  auto entity3 = em.getEntityPtr(entity.lock()->getID());
  ASSERT_EQ(entity.lock()->getName(), entity3.lock()->getName());
}

TEST_F(EntityMangerTest, testGetEntityID) {
  std::vector<EntityID> id = em.getEntityID("TestEntity");
  uint32_t id2 = em.getEntityID(entity);
  ASSERT_EQ(id.size(), 1);
  ASSERT_EQ(entity.lock()->getID(), id[0]);
  ASSERT_EQ(entity.lock()->getID(), id2);
}

TEST_F(EntityMangerTest, testGetEntityByName) {
  auto entity2 = em.createEntity("TestEntity");
  auto entity3 = em.createEntity("TestEntity");
  std::vector<Weak<AbstractEntity>> res = em.getEntityByName("TestEntity");
  ASSERT_EQ(res.size(), 3);
}

TEST_F(EntityMangerTest, testHasComponent1) {
  Shared<AbstractEntity> temp = this->entity.lock();
  ASSERT_FALSE(em.hasComponent<TestComponent>(temp));
  ASSERT_FALSE(em.hasComponent<TestComponent>(temp.get()));
}

TEST_F(EntityMangerTest, testHasAllComponents1) {
  Shared<AbstractEntity> temp = this->entity.lock();
  ASSERT_FALSE(em.hasAllComponents<TestComponent>(temp));
  ASSERT_FALSE(em.hasAllComponents<TestComponent>(temp.get()));
}

TEST_F(EntityMangerTest, testAddComponent) {
  Shared<AbstractEntity> temp = this->entity.lock();
  auto T = em.addComponent<TestComponent>(temp, 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(temp));
  ASSERT_EQ(T.value, 5);
}
TEST_F(EntityMangerTest, testAddComponent2) {
  Shared<AbstractEntity> temp = this->entity.lock();
  auto T = em.addComponent<TestComponent>(temp.get(), 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(temp));
  ASSERT_EQ(T.value, 5);
}

TEST_F(EntityMangerTest, testAddDuplicateComponent) {
  auto T = em.addComponent<TestComponent>(entity.lock(), 5);
  ASSERT_THROW(em.addComponent<TestComponent>(entity.lock(), 5),
               std::runtime_error);
}

TEST_F(EntityMangerTest, testEntityHasComponent2) {
  auto T = em.addComponent<TestComponent>(entity.lock(), 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(entity.lock()));
}

TEST_F(EntityMangerTest, testEntityHasAllComponents2) {
  auto T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto T2 = em.addComponent<TestComponent2>(entity.lock(), 5);
  bool hasAll =
      em.hasAllComponents<TestComponent, TestComponent2>(entity.lock());
  ASSERT_TRUE(hasAll);
}

TEST_F(EntityMangerTest, testGetComponent1) {
  auto T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto T2 = em.getComponent<TestComponent>(entity.lock());
  ASSERT_EQ(T2.value, 5);
}

TEST_F(EntityMangerTest, testGetComponent2) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.getComponent<TestComponent>(entity.lock());
  T2.value = 10;
  ASSERT_EQ(T.value, T2.value);
}

TEST_F(EntityMangerTest, testGetComponent3) {
  ASSERT_THROW(em.getComponent<TestComponent>(entity.lock()),
               std::runtime_error);
}

TEST_F(EntityMangerTest, testRemoveComponent) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(entity.lock()));
  em.removeComponent<TestComponent>(entity.lock());
  ASSERT_FALSE(em.hasComponent<TestComponent>(entity.lock()));
}

TEST_F(EntityMangerTest, testRemoveComponent2) {
  ASSERT_THROW(em.removeComponent<TestComponent>(entity.lock()),
               std::runtime_error);
}

TEST_F(EntityMangerTest, testRemoveComponent3) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  em.removeComponent<TestComponent>(entity.lock());
  ASSERT_THROW(em.removeComponent<TestComponent>(entity.lock()),
               std::runtime_error);
  ASSERT_THROW(em.getComponent<TestComponent>(entity.lock()),
               std::runtime_error);
}

TEST_F(EntityMangerTest, testGetHasAllAfterRemove) {
  auto entity2 = em.createEntity("Entity2");
  auto entity3 = em.createEntity("Entity3");

  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  entity2.lock()->addComponent<TestComponent>(10);
  entity3.lock()->addComponent<TestComponent>(10);

  entity2.lock()->removeComponent<TestComponent>();

  auto hasall = em.getHasAll<TestComponent>();

  ASSERT_EQ(hasall.size(), 2);
  ASSERT_NO_THROW(hasall[0].lock()->getComponent<TestComponent>());
  ASSERT_NO_THROW(hasall[1].lock()->getComponent<TestComponent>());
}

TEST_F(EntityMangerTest, testModifyComponent1) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.modifyComponent<TestComponent>(entity.lock(), 10);
  ASSERT_EQ(T2.value, 10);

  auto &T3 = em.getComponent<TestComponent>(entity.lock());
  ASSERT_EQ(T3.value, 10);
}

TEST_F(EntityMangerTest, testModifyComponent) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.modifyComponent<TestComponent>(entity.lock(), 10);
  auto &T3 = em.getComponent<TestComponent>(entity.lock());
  T3.value = 15;
  ASSERT_EQ(T2.value, T3.value);
}

TEST_F(EntityMangerTest, testModifyComponent4) {
  ASSERT_THROW(em.modifyComponent<TestComponent>(entity.lock(), 10),
               std::runtime_error);
}

TEST_F(EntityMangerTest, testGetHasAll) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.addComponent<TestComponent2>(entity.lock(), 5);
  auto entities = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities.size(), 1);
}

TEST_F(EntityMangerTest, testGetHasAll2) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.addComponent<TestComponent2>(entity.lock(), 5);
  auto entities = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities.size(), 1);
  em.removeComponent<TestComponent>(entity.lock());
  auto entities2 = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities2.size(), 0);
}

TEST_F(EntityMangerTest, testGetHasAll3) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.addComponent<TestComponent2>(entity.lock(), 5);

  auto entity2 = em.createEntity("TestEntity2");

  auto &T3 = em.addComponent<TestComponent>(entity2.lock(), 5);
  auto &T4 = em.addComponent<TestComponent2>(entity2.lock(), 5);
  auto entities = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities.size(), 2);
  em.removeComponent<TestComponent>(entity.lock());
  auto entities2 = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities2.size(), 1);
}

class AbstractEntityTest : public ::testing::Test {
protected:
  void SetUp() override { std::cout << "SetUp called\n"; }

  void TearDown() override { std::cout << "TearDown called\n"; }

  EntityManager em;
  Shared<AbstractEntity> entity = em.createEntity("TestEntity").lock();
};

TEST_F(AbstractEntityTest, testHas) {
  ASSERT_FALSE(entity->hasComponent<TestComponent>());
}

TEST_F(AbstractEntityTest, testAddComponent_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  ASSERT_TRUE(entity->hasComponent<TestComponent>());
  ASSERT_EQ(T.value, 5);
}

TEST_F(AbstractEntityTest, testAddDuplicateComponent_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  ASSERT_THROW(entity->addComponent<TestComponent>(5), std::runtime_error);
}

TEST_F(AbstractEntityTest, testEntityHasComponent2_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  ASSERT_TRUE(entity->hasComponent<TestComponent>());
}

TEST_F(AbstractEntityTest, testEntityHasAllComponents2_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->addComponent<TestComponent2>(5);
  bool hasAll = entity->hasAllComponents<TestComponent, TestComponent2>();
  ASSERT_TRUE(hasAll);
}

TEST_F(AbstractEntityTest, testGetComponent1_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->getComponent<TestComponent>();
  ASSERT_EQ(T2.value, 5);
}

TEST_F(AbstractEntityTest, testGetComponent2_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->getComponent<TestComponent>();
  T2.value = 10;
  ASSERT_EQ(T.value, T2.value);
}

TEST_F(AbstractEntityTest, testGetComponent3_AbstractEntity) {
  ASSERT_THROW(entity->getComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testRemoveComponent_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  ASSERT_TRUE(entity->hasComponent<TestComponent>());
  entity->removeComponent<TestComponent>();
  ASSERT_FALSE(entity->hasComponent<TestComponent>());
}

TEST_F(AbstractEntityTest, testRemoveComponent2_AbstractEntity) {
  ASSERT_THROW(entity->removeComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testRemoveComponent3_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  entity->removeComponent<TestComponent>();
  ASSERT_THROW(entity->removeComponent<TestComponent>(), std::runtime_error);
  ASSERT_THROW(entity->getComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testRemoveComponent4_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  entity->removeComponent<TestComponent>();
  ASSERT_THROW(entity->removeComponent<TestComponent>(), std::runtime_error);
  ASSERT_THROW(entity->getComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testRemoveComponent5_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  entity->removeComponent<TestComponent>();
  ASSERT_THROW(entity->removeComponent<TestComponent>(), std::runtime_error);
  ASSERT_THROW(entity->getComponent<TestComponent>(), std::runtime_error);
}

TEST_F(AbstractEntityTest, testModifyComponent_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->modifyComponent<TestComponent>(10);
  ASSERT_EQ(T2.value, 10);
}

TEST_F(AbstractEntityTest, testModifyComponent2_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->modifyComponent<TestComponent>(10);
  ASSERT_EQ(T2.value, 10);
  auto &T3 = entity->getComponent<TestComponent>();
  ASSERT_EQ(T3.value, 10);
}

TEST_F(AbstractEntityTest, testModifyComponent3_AbstractEntity) {
  auto &T = entity->addComponent<TestComponent>(5);
  auto &T2 = entity->modifyComponent<TestComponent>(10);
  auto &T3 = entity->getComponent<TestComponent>();
  T3.value = 15;
  ASSERT_EQ(T2.value, T3.value);
}

TEST_F(AbstractEntityTest, testModifyComponent4_AbstractEntity) {
  ASSERT_THROW(entity->modifyComponent<TestComponent>(10), std::runtime_error);
}
