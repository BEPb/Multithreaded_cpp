#include <string>

class StringPointer {

private:
    std::string* _ptr;
    bool _owner;

public:
    std::string *operator->() {
        return _ptr;
    }

    operator std::string*() {
        return _ptr;
    }

    StringPointer(std::string *Pointer):
        _ptr(Pointer != nullptr ? Pointer : new std::string()),
        _owner(Pointer == nullptr) {}

    ~StringPointer() {
        if(_owner) delete _ptr;
    }
};