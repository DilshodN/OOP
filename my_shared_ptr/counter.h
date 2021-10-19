#pragma once

class Counter{
    unsigned int count{};
public:
    Counter() : count(0){};
    Counter(const Counter&) = delete;
    Counter& operator=(const Counter&) = delete;
public:
    unsigned int get() const {return count;};
    void reset(){count = 0;};

    void operator++(){count++;}
    void operator++(int){count++;}

    void operator--(){count--;}
    void operator--(int){count--;}
};

