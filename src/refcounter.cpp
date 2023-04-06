/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef REFCOUNTER_CPP
#define REFCOUNTER_CPP

#include "refcounter.h"

// default Ctor
template <typename T>
Refcounter<T>::Refcounter()
    : ptr(nullptr)
{
}

// Ctor with refcounting functionality
template <typename T>
Refcounter<T>::Refcounter(T* ptr, bool increase_count)
    : ptr(new Shim(ptr))
{
    if (increase_count)
        increment();
}

// copy Ctor
template <typename T>
Refcounter<T>::Refcounter(const Refcounter& rhs)
    : ptr(rhs.ptr)
{
    increment();
}

// Dtor will delete pointer if refcount becomes 0
template <typename T> Refcounter<T>::~Refcounter()
{
    decrement();
}

// assignment operator for times when you don't want the reference
// increased for incoming ptr.
template <typename T> Refcounter<T>& Refcounter<T>::operator=(T* ptr)
{
    decrement();
    ptr = new Shim(ptr);
    return *this;
}

// assignment operator
template <typename T> Refcounter<T>& Refcounter<T>::operator=(const Refcounter& rhs)
{
    decrement();
    ptr = rhs.ptr;
    increment();
    return *this;
}

// get the underlying pointer
template <typename T> T* Refcounter<T>::get_ptr()
{
    return ptr->t;
}

// get the underlying pointer
template <typename T> const T* Refcounter<T>::get_ptr() const
{
    return ptr->t;
}

// dereference operator
template <typename T> T& Refcounter<T>::operator*()
{
    return *ptr->t;
}

// dereference operator
template <typename T> const T& Refcounter<T>::operator*() const
{
    return *ptr->t;
}

// mimic pointer dereferencing
template <typename T> T* Refcounter<T>::operator->()
{
    return ptr->t;
}

// mimic pointer dereferencing
template <typename T> const T* Refcounter<T>::operator->() const
{
    return ptr->t;
}

// implementation of the increment operation
template <typename T> void Refcounter<T>::increment()
{
    if (ptr)
        ++ptr->refcount;
}

// implementation of the decrement operation
template <typename T> void Refcounter<T>::decrement()
{
    if (ptr) {
        --ptr->refcount;
        if (ptr->refcount <= 0) {
            delete ptr;
            ptr = nullptr;
        }
    }
}

template <typename T>
Refcounter<T>::Shim::Shim(T* t)
    : t(t)
    , refcount(1)
{
}

template <typename T> Refcounter<T>::Shim::~Shim()
{
    delete t;
}

#endif // REFCOUNTER_CPP
