#pragma once
#include "pch.h"
class Observer {
public:
    virtual ~Observer() = default;
    virtual void onNotify() = 0;
};
class Subject {
public:
    virtual ~Subject() = default;
    void addObserver(Weak<Observer> observer) {
        observers.push_back(observer);
    }
    void notify() {
        for (auto observer : observers) {
            observer.lock()->onNotify();
        }
    }

private:
    std::vector<Weak<Observer>> observers;
};