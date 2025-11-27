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
    char annotation[100]; // offset 4
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
    static_assert(offsetof(N, annotation) - 4 == 4);
    static_assert(offsetof(N, number) - 4 == 104);
    static_assert(sizeof(N) - 4 == 108);

    if (argc < 2) {
        _exit(1);
    }

    N *a = new N(5);
    BaseClass<N> *b = new N(6);

    a->setAnnotation(argv[1]);

    return *b + *a; // Indirection via vtable because b is BaseClass<N> which is abstract
}
