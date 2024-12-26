#include <gtest/gtest.h>

#include "TestComponent.h"

class EntityManagerTest : public testing::Test {
protected:
  void SetUp() override { std::cout << "\nSetUp called\n"; }

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

TEST_F(EntityManagerTest, testGetByName) {
  std::vector<Weak<AbstractEntity>> res = em.getEntityByName("TestEntity");
  ASSERT_EQ(res.size(), 1);
  ASSERT_EQ(entity.lock()->getName(), res[0].lock()->getName());
}

TEST_F(EntityManagerTest, testGetByID) {
  auto entity2 = em.getEntityRef(entity.lock()->getID());
  ASSERT_EQ(entity.lock()->getName(), entity2.getName());

  auto entity3 = em.getEntityPtr(entity.lock()->getID());
  ASSERT_EQ(entity.lock()->getName(), entity3.lock()->getName());
}

TEST_F(EntityManagerTest, testGetEntityID) {
  std::vector<EntityID> id = em.getEntityID("TestEntity");
  uint32_t id2 = em.getEntityID(entity);
  ASSERT_EQ(id.size(), 1);
  ASSERT_EQ(entity.lock()->getID(), id[0]);
  ASSERT_EQ(entity.lock()->getID(), id2);
}

TEST_F(EntityManagerTest, testGetEntityByName) {
  auto entity2 = em.createEntity("TestEntity");
  auto entity3 = em.createEntity("TestEntity");
  std::vector<Weak<AbstractEntity>> res = em.getEntityByName("TestEntity");
  ASSERT_EQ(res.size(), 3);
}

TEST_F(EntityManagerTest, testHasComponent1) {
  Shared<AbstractEntity> temp = this->entity.lock();
  ASSERT_FALSE(em.hasComponent<TestComponent>(temp));
  ASSERT_FALSE(em.hasComponent<TestComponent>(temp.get()));
}

TEST_F(EntityManagerTest, testHasAllComponents1) {
  Shared<AbstractEntity> temp = this->entity.lock();
  ASSERT_FALSE(em.hasAllComponents<TestComponent>(temp));
  ASSERT_FALSE(em.hasAllComponents<TestComponent>(temp.get()));
}

TEST_F(EntityManagerTest, testAddComponent) {
  Shared<AbstractEntity> temp = this->entity.lock();
  auto T = em.addComponent<TestComponent>(temp, 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(temp));
  ASSERT_EQ(T.value, 5);
}
TEST_F(EntityManagerTest, testAddComponent2) {
  Shared<AbstractEntity> temp = this->entity.lock();
  auto T = em.addComponent<TestComponent>(temp.get(), 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(temp));
  ASSERT_EQ(T.value, 5);
}

TEST_F(EntityManagerTest, testAddDuplicateComponent) {
  auto T = em.addComponent<TestComponent>(entity.lock(), 5);
  ASSERT_THROW(em.addComponent<TestComponent>(entity.lock(), 5),
               std::runtime_error);
}

TEST_F(EntityManagerTest, testEntityHasComponent2) {
  auto T = em.addComponent<TestComponent>(entity.lock(), 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(entity.lock()));
}

TEST_F(EntityManagerTest, testEntityHasAllComponents2) {
  auto T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto T2 = em.addComponent<TestComponent2>(entity.lock(), 5);
  bool hasAll =
      em.hasAllComponents<TestComponent, TestComponent2>(entity.lock());
  ASSERT_TRUE(hasAll);
}

TEST_F(EntityManagerTest, testGetComponent1) {
  auto T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto T2 = em.getComponent<TestComponent>(entity.lock());
  ASSERT_EQ(T2.value, 5);
}

TEST_F(EntityManagerTest, testGetComponent2) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.getComponent<TestComponent>(entity.lock());
  T2.value = 10;
  ASSERT_EQ(T.value, T2.value);
}

TEST_F(EntityManagerTest, testGetComponent3) {
  ASSERT_THROW(em.getComponent<TestComponent>(entity.lock()),
               std::runtime_error);
}

TEST_F(EntityManagerTest, testRemoveComponent) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  ASSERT_TRUE(em.hasComponent<TestComponent>(entity.lock()));
  em.removeComponent<TestComponent>(entity.lock());
  ASSERT_FALSE(em.hasComponent<TestComponent>(entity.lock()));
}

TEST_F(EntityManagerTest, testRemoveComponent2) {
  ASSERT_THROW(em.removeComponent<TestComponent>(entity.lock()),
               std::runtime_error);
}

TEST_F(EntityManagerTest, testRemoveComponent3) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  em.removeComponent<TestComponent>(entity.lock());
  ASSERT_THROW(em.removeComponent<TestComponent>(entity.lock()),
               std::runtime_error);
  ASSERT_THROW(em.getComponent<TestComponent>(entity.lock()),
               std::runtime_error);
}

TEST_F(EntityManagerTest, testGetHasAllAfterRemove) {
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

TEST_F(EntityManagerTest, testModifyComponent1) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.modifyComponent<TestComponent>(entity.lock(), 10);
  ASSERT_EQ(T2.value, 10);

  auto &T3 = em.getComponent<TestComponent>(entity.lock());
  ASSERT_EQ(T3.value, 10);
}

TEST_F(EntityManagerTest, testModifyComponent) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.modifyComponent<TestComponent>(entity.lock(), 10);
  auto &T3 = em.getComponent<TestComponent>(entity.lock());
  T3.value = 15;
  ASSERT_EQ(T2.value, T3.value);
}

TEST_F(EntityManagerTest, testModifyComponent4) {
  ASSERT_THROW(em.modifyComponent<TestComponent>(entity.lock(), 10),
               std::runtime_error);
}

TEST_F(EntityManagerTest, testGetHasAll) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.addComponent<TestComponent2>(entity.lock(), 5);
  auto entities = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities.size(), 1);
}

TEST_F(EntityManagerTest, testGetHasAll2) {
  auto &T = em.addComponent<TestComponent>(entity.lock(), 5);
  auto &T2 = em.addComponent<TestComponent2>(entity.lock(), 5);
  auto entities = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities.size(), 1);
  em.removeComponent<TestComponent>(entity.lock());
  auto entities2 = em.getHasAll<TestComponent, TestComponent2>();
  ASSERT_EQ(entities2.size(), 0);
}

TEST_F(EntityManagerTest, testGetHasAll3) {
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
