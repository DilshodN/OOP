#pragma once
#include <functional>


template<typename Type, class TDeleter = std::default_delete<Type>>
class SharedPTR{
    using t_SharedPTR = SharedPTR<Type, TDeleter>;
    using deleter_type = TDeleter;
    using type_ptr = Type*;
    type_ptr data = nullptr;
    long* count = nullptr;
    deleter_type deleter = TDeleter();

    void decrement_count(){
        if(count != nullptr){
            if(*count == 0 or *count == 1){
                deleter(data);
                delete count;
            }
            else {
                (*count)--;
            }
        }
    };
    void increment_count(){
        if(data != nullptr && count != nullptr){
            (*count)++;
        }
    };
public:
    // https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    SharedPTR() noexcept = default;
    SharedPTR(std::nullptr_t) noexcept : data(nullptr), count(nullptr){};
    explicit SharedPTR(type_ptr ptr) noexcept{
        data = ptr;
        count = new long(0);
        increment_count();
    };
    SharedPTR(const t_SharedPTR& other) noexcept: data(other.data), count(other.count){
        increment_count();
    };
    SharedPTR(t_SharedPTR&& other) noexcept : data(other.data), count(other.count){
        other.data = nullptr;
        other.count = nullptr;
    };
    ~SharedPTR(){
        release();
    };
public:
    t_SharedPTR& operator=(t_SharedPTR&& other) noexcept{
        decrement_count();
        data = other.data;
        count = other.count;
        other.data = nullptr;
        other.count = nullptr;
        return *this;
    };
    t_SharedPTR& operator=(Type* ptr) noexcept{
        decrement_count();
        data = ptr;
        if(data != nullptr){
            count = new long(0);
            increment_count();
        }
        return *this;
    };
    t_SharedPTR& operator=(const t_SharedPTR& other) noexcept{
        decrement_count();
        data = other.data;
        count = other.count;
        increment_count();
        return *this;
    };
public:
    Type* get() const noexcept{
        return data;
    };
    operator bool() const{
        return get() != nullptr;
    };
    // Dereferences the stored pointer. The behavior is undefined if the stored pointer is null. (cpp_reference)
    Type& operator*() const noexcept{
        return *get();
    };
    Type* operator->() const noexcept{
        return get();
    };

    TDeleter& get_deleter(){
        return deleter;
    };

    long use_count() const noexcept{
        return count ? *count : 0;
    }

    bool unique() const noexcept{
        return use_count() == 1;
    }

public:
    void release(){
        decrement_count();
    };
    void reset(Type* ptr = nullptr){
        decrement_count();
        data = ptr;
        count = new long(0);
        increment_count();
    }; // Replace the stored pointer.
    void swap(t_SharedPTR& sharedPTR){
        std::swap(data, sharedPTR.data);
        std::swap(count, sharedPTR.count);
    };
};