// NOTE: implementation of the Entity file
// Don't worry about the warnings from the editor

template <typename T> inline bool Entity::hasComponent() const {
  ComponentTypeID typeID = getComponentTypeID<T>();

  if (typeID >= maxComponents) {
    Log("log.txt", LogLevel::CRITICAL, "Exceeded maximum number of components");
    return false;
  }
  return this->componentBitset.test(typeID);
}

template <typename T, typename... TArgs>
inline T &Entity::addComponent(TArgs &&...mArgs) {
  ComponentTypeID typeID = getComponentTypeID<T>();
  if (typeID >= maxComponents) {
    throw std::runtime_error("Exceeded maximum number of components");
  }
  T *c(new T(std::forward<TArgs>(mArgs)...));
  c->setEntity(this);

  // Unique<Component> uPtr{c};
  // components.emplace_back(std::move(uPtr));
  components.push_back(Unique<Component>(c));

  componentArray[getComponentTypeID<T>()] = c;
  componentBitset[getComponentTypeID<T>()] = true;
  c->init();

#ifdef _DEBUG
  Log("log.txt", LogLevel::INFO, c->name + " created");
#endif
  return *c;
}

template <typename T> inline T &Entity::getComponent() const {
  auto ptr(componentArray[getComponentTypeID<T>()]);
  return *static_cast<T *>(ptr);
}
