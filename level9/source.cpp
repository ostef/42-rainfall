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
    short number1; // offset 26
    char _padding[74];
    int number2; // offset 104
    // total size 108

public:
    N(int value) {
        this->number1 = value;
    }

    void setAnnotation(const char *str) {
        memcpy(this->annotation, str, strlen(str));
    }

    virtual int operator+(N &other) override {
        return (this->number1) + (other.number1);
    }

    virtual int operator-(N &other) override {
        return (this->number1) - (other.number1);
    }
};

int main(int argc, const char **argv, const char **envp) {
    const size_t offset_a = offsetof(N, annotation);
    const size_t offset_b = offsetof(N, number1);
    const size_t offset_c = offsetof(N, number2);
    const size_t size = sizeof(N);

    if (argc < 2) {
        _exit(1);
    }

    N *a = new N(5);
    BaseClass<N> *b = new N(6);

    a->setAnnotation(argv[1]);

    return *b + *a; // Indirection via vtable because b is BaseClass<N> which is abstract
}
