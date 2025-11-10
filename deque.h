#pragma once

#include <cstddef>

template <typename T>
struct Deque
{
    virtual void addFirst(T &x) = 0;
    virtual void addLast(T &x) = 0;
    virtual T removeFirst() = 0;
    virtual T removeLast() = 0;
    virtual const T peekFirst() const = 0;
    virtual const T peekLast() const = 0;
    virtual bool isEmpty() const = 0;
    virtual void clear() = 0;
    virtual size_t size() const = 0;
};