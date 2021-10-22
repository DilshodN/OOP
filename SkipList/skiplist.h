#pragma once
#include <algorithm>
#include <functional>
#include <array>


template <typename Key,
        typename Value,
        typename Compare = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key,Value> > >
class skip_list {
public:
    using key_type = Key;
    using mapped_type = Value;
    using value_type = std::pair<const Key, Value>;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using const_pointer = const value_type*;

private:
    static const size_type max_level = 3;
    Compare comp_ = Compare();
    Alloc alloc_ = Alloc();

    struct skip_node{
        value_type data;
        std::array<std::shared_ptr<skip_node>, max_level + 1> next;
        skip_node() = default;
        explicit skip_node(value_ptr&& data) : data(std::move(data)) {}
    };

    using node_ptr = std::shared_ptr<skip_node>;
    node_ptr create_node(key_type&& key, mapped_type&& value){

    }

};