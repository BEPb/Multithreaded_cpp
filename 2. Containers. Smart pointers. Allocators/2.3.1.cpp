#include <cstring>

class SmallAllocator {

private:
    const unsigned int HeapSize = 1048576;
    char Memory[1048576];
    unsigned int _offset;

public:
    SmallAllocator(): _offset(0) {}

    void *Alloc(unsigned int Size) {
        if(_offset + Size > HeapSize){
            return nullptr;
        }

        void* result = &Memory[_offset];
        _offset += Size;

        return result;
    };

    void *ReAlloc(void *Pointer, unsigned int Size) {
        if(_offset + Size > HeapSize){
            return nullptr;
        }

        memcpy(&Memory[_offset + Size], Pointer, Size);
        _offset += Size;

        return &Memory[_offset];
    };

    void Free(void *Pointer) {};
};