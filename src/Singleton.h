#pragma once

template <typename T>
class Singleton {
public:
    static T& Instance() {
        static T instance;
        return instance;
    }
    // Copy constructor
    Singleton(const Singleton&) = delete;
    // Move constructor
    Singleton(Singleton&&) = delete;
    // Copy assignment
    Singleton& operator =(const Singleton&) = delete;
    // Move assignment
    Singleton& operator =(Singleton&&) = delete;
protected:
    Singleton() {};
    virtual ~Singleton() {};
};
