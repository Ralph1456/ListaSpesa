#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include <memory>

template<typename T>
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const T& data) = 0;
};

template<typename T>
class Subject {
private:
    std::vector<std::weak_ptr<Observer<T>>> observers;

public:
    virtual ~Subject() = default;

    void addObserver(std::shared_ptr<Observer<T>> observer) {
        observers.push_back(observer);
    }

    void removeObserver(std::shared_ptr<Observer<T>> observer) {
        observers.erase(
                std::remove_if(observers.begin(), observers.end(),
                               [&observer](const std::weak_ptr<Observer<T>>& weak_obs) {
                                   return weak_obs.expired() || weak_obs.lock() == observer;
                               }),
                observers.end());
    }

protected:
    void notifyObservers(const T& data) {
        auto it = observers.begin();
        while (it != observers.end()) {
            if (auto obs = it->lock()) {
                obs->update(data);
                ++it;
            } else {
                it = observers.erase(it);
            }
        }
    }
};

#endif