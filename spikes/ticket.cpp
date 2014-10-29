#include <iostream>
#include <memory>

#include "Container.hpp"

class Foo {
    public:
        Foo(const int v): value(v) {
            std::cout << "Foo ctor" << std::endl;
        }

        inline int getValue() const {
            return value;
        }
    private:
        int value;
};

class Bar {
    public:
        Bar(std::shared_ptr<Foo> f):
        foo(f) {
            std::cout << "Bar ctor" << std::endl;
        }

    private:
        std::shared_ptr<Foo> foo;
};

int main() {
    auto container = Container();
    auto foo = std::make_shared<Foo>(5);

    container.registerInstance<Foo>(foo);
    container.registerClass<Bar, Foo>();

    auto fooInstance = container.get<Foo>();
    auto barInstance = container.get<Bar>();

    return 0;
}
