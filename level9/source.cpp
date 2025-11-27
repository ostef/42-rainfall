// > g++ -m32 source.cpp

#include <cstddef>
#include <cstring>

template<typename T>
class BaseClass {
public:
    virtual int operator+(T &b) = 0;
    virtual int operator-(T &b) = 0;
};

class N : public BaseClass<N> {
public:
    // void *vtable; // offset 0
    char annotation[22]; // offset 4
    char _padding[76];
    int number; // offset 104
    // total size 108

public:
    N(int value) {
        this->number = value;
    }

    void setAnnotation(const char *str) {
        memcpy(this->annotation, str, strlen(str));
    }

    virtual int operator+(N &other) override {
        return (this->number) + (other.number);
    }

    virtual int operator-(N &other) override {
        return (this->number) - (other.number);
    }
};

int main(int argc, const char **argv, const char **envp) {
    const size_t offset_a = offsetof(N, annotation) - 4;
    const size_t offset_b = offsetof(N, number) - 4;
    const size_t size = sizeof(N) - 4;

    if (argc < 2) {
        _exit(1);
    }

    N *a = new N(5);
    BaseClass<N> *b = new N(6);

    a->setAnnotation(argv[1]);

    return *b + *a; // Indirection via vtable because b is BaseClass<N> which is abstract
}
