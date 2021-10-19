#pragma once
#include "counter.h"

template<class Type, class TDeleter = std::default_delete<Type>>
class SharedPTR {
    typedef SharedPTR<Type, TDeleter> t_SharedPTR;
    Type* ptr;
    Counter* ref_count;
    TDeleter deleter;
public:
    SharedPTR() = default;
    SharedPTR(Type* pObj, TDeleter _deleter = std::default_delete<Type>()) : deleter(_deleter){
        ptr = pObj;
        ref_count = new Counter();
        if(ptr != nullptr)
            (*ref_count)++;
    }
    SharedPTR(t_SharedPTR&& unique_ptr){
        if(this != unique_ptr.ptr){
            ptr = unique_ptr.ptr;
            ref_count = unique_ptr.ref_count;
            deleter = unique_ptr.deleter;
        }
    }

    SharedPTR(const t_SharedPTR& other){
        ptr = other.ptr;
        ref_count = other.ref_count;
        deleter = other.deleter;
    }

    ~SharedPTR()
    {
        (*ref_count)--;
        if(ref_count->get() == 0)
        {
            deleter(ptr);
            delete ref_count;
        }
    };
public:
    t_SharedPTR& operator=(t_SharedPTR&& sharedPtr)
    {

        ptr = sharedPtr.ptr;
        ref_count = sharedPtr.ref_count;
        deleter = sharedPtr.deleter;

    }

    t_SharedPTR& operator=(const t_SharedPTR& sharedPtr)
    {
        ptr = sharedPtr.ptr;
        ref_count = sharedPtr.ref_count;
        deleter = sharedPtr.deleter;
        if(ptr != nullptr)
        {
            (*ref_count)++;
        }
    }

    t_SharedPTR operator=(Type* pObj){
        ptr(pObj);
        ref_count = new Counter;
    }

public:
    Type& operator*() const
    {
        return *ptr;
    };
    Type* operator->() const
    {
        return ptr;
    }; // Return the stored pointer.
    Type* get() const
    {
        return ptr;
    }; // Return the stored pointer.
    TDeleter& get_deleter()
    {
        return deleter;
    }; // Return a reference to the stored deleter.
    operator bool() const
    {
        return ptr != nullptr;
    }; // Return false if the stored pointer is null.
public:

};