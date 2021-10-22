//#pragma once
//#include <iostream>
//#include <vector>
//
//template <typename Key,
//        typename Value,
//        typename Compare = std::less<Key>,
//        typename Alloc = std::allocator<std::pair<const Key,Value> > >
//class skip_node{
//    typedef Key key_type;
//    typedef Value value_type;
//    typedef Compare comp_type;
//    typedef Alloc alloc_type;
//    key_type _key;
//    value_type _value;
//
//    std::vector<skip_node*> forward;
//public:
//    skip_node(key_type& key, value_type& value, uint& level = 5,
//              comp_type comp = std::less<key_type>) : _key(key), _value(value){
//        for(uint i = 0; i < level; i++){
//            forward.emplace_back(nullptr);
//        }
//    }
//};
//
//
