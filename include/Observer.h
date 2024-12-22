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
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void notify() {
        for (auto observer : observers) {
            observer->onNotify();
        }
    }

private:
    std::vector<Observer*> observers;
};