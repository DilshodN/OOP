#pragma once
#include <functional>

template<typename Type, class TDeleter = std::default_delete<Type>>
class SharedPTR final{
    using t_SharedPTR = SharedPTR<Type, TDeleter>;
    using ptr_type = Type*;
    using value_type = Type;
    using deleter_type = TDeleter;
    deleter_type deleter = std::default_delete<t_SharedPTR>();

    ptr_type data = nullptr;
    long* count = nullptr;

    void increment_count(){
        if(data != nullptr){
            (*count)++;
        }
    };

public:
    // https://en.cppreference.com/w/cpp/memory/shared_ptr/shared_ptr
    SharedPTR() = default;
    SharedPTR(std::nullptr_t) : data(nullptr), count(nullptr){};
    explicit SharedPTR(typename SharedPTR<Type>::ptr_type ptr) {
        data = ptr;
        count = new long(0);
        deleter = std::default_delete<Type>();
        increment_count();
    }

    SharedPTR(const t_SharedPTR& other) : data(other.data), count(other.count){
        increment_count();
    };
    SharedPTR(t_SharedPTR&& other) noexcept : data(other.data), count(other.count), deleter(other.deleter){
        other.data = nullptr;
        other.count = nullptr;
    };
    ~SharedPTR(){
        release();
    };
public:
    t_SharedPTR& operator=(t_SharedPTR&& other) noexcept{
        release();
        data = other.data;
        count = other.count;
        deleter = other.deleter;
        other.data = nullptr;
        other.count = nullptr;
        return *this;
    };
    t_SharedPTR& operator=(Type* ptr){
        release();
        data = ptr;
        if(data != nullptr){
            count = new long(0);
            increment_count();
        }
        return *this;
    };
    t_SharedPTR& operator=(const t_SharedPTR& other){
        release();
        data = other.data;
        count = other.count;
        deleter = other.deleter;
        increment_count();
        return *this;
    };
public:
    Type* get() const {
        return data;
    };
    operator bool() const{
        return get() != nullptr;
    };
    // Dereferences the stored pointer. The behavior is undefined if the stored pointer is null. (cpp_reference)
    Type& operator*() const {
        return *get();
    };
    Type* operator->() const {
        return get();
    };

    TDeleter& get_deleter(){
        return deleter;
    };

    long use_count() const {
        return count ? *count : 0;
    }

    bool unique() const {
        return use_count() == 1;
    }

public:
    void release(){
        if(count != nullptr){
            if(*count == 1){
                deleter(data);
                delete count;
            }
            else {
                (*count)--;
            }
        };
    };

    void reset(ptr_type ptr = nullptr){
        release();
        data = ptr;
        count = new long(0);
        increment_count();
    };
    void swap(t_SharedPTR& sharedPTR){
        std::swap(data, sharedPTR.data);
        std::swap(count, sharedPTR.count);
    };
};