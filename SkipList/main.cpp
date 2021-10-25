#include <iostream>
#include <utility>
#include <vector>

template<typename Key,
        typename Value>
class temp{

//    typedef std::pair<const Key, Value> value_type;
    Key key;
    Value value;
    temp(const Key& key, Value  value) : value(std::move(value)), key(key){};
public:
     Key& get_key() const{
         return key;
    }
    Value& get_value() const{
        return value;
     }
};

int main() {
    temp<int, std::string> a(5, "123");
    return 0;
}
