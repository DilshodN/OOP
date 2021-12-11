#pragma once
#include <functional>


template<typename Type, class TDeleter = std::default_delete<Type>>
class SharedPTR final{
    using t_SharedPTR = SharedPTR<Type, TDeleter>;
    using value_type = std::conditional_t<std::is_array_v<Type>, typename std::remove_extent_t<Type>, Type>;
    using deleter_type = TDeleter;

    value_type* data = nullptr;
    long* count = nullptr;

    void increment_count(){
        if(data != nullptr){
            (*count)++;
        }
    };

    void assign(const t_SharedPTR& other){
        release();
        data = other.data;
        count = other.count;
    }

public:
    SharedPTR() = default;
    SharedPTR(std::nullptr_t){};

    explicit SharedPTR(value_type* ptr) {
        data = ptr;
        count = new long(0);
        increment_count();
    }


    SharedPTR(const t_SharedPTR& other) : data(other.data), count(other.count){
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
        if(this == &other) {
            return *this;
        }
        assign(other);
        other.data = nullptr;
        other.count = nullptr;
        return *this;
    };
    t_SharedPTR& operator=(value_type* ptr){
        *this = t_SharedPTR(ptr);
        return *this;
    };
    t_SharedPTR& operator=(const t_SharedPTR& other) noexcept{
        if(this == &other) {
            return *this;
        }
        assign(other);
        increment_count();
        return *this;
    };
public:
    value_type* get() const {
        return data;
    };
    operator bool() const{
        return data != nullptr;
    };

    value_type& operator*() const {
        return *data;
    };
    value_type* operator->() const {
        return data;
    };

    TDeleter& get_deleter(){
        return deleter_type();
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
                deleter_type()(data);
                delete count;
            }
            else {
                (*count)--;
            }
        };
    };

    void reset(value_type* ptr = nullptr){
        *this = ptr;
    };
    void swap(t_SharedPTR& sharedPTR){
        std::swap(data, sharedPTR.data);
        std::swap(count, sharedPTR.count);
    };
};

template<typename T, typename ... Args>
SharedPTR<T> make_shared_ptr(Args&&... args){
    return SharedPTR<T>(new T(std::forward<Args>(args)...));
}