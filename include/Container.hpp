#include <memory>
#include <string>
#include <map>
#include <functional>

class Container {
    public:
        template<class T, class... Ts>
        void registerSingleton();

        template<class T>
        void registerInstance(const std::shared_ptr<T>& instance);

        template<class T, class... Ts>
        void registerClass();

        template<class T>
        std::shared_ptr<T> get();

    private:
        class IHolder {
            public:
                virtual ~IHolder() {}
                virtual void noop() {}
        };

        template <class T>
        class Holder: public IHolder {
            public:
                virtual ~Holder() {}
                std::shared_ptr<T> instance;
        };

        std::map<std::string, std::function<void*()>> creatorMap;
        std::map<std::string, std::shared_ptr<IHolder>> instanceMap;
};

#include "Container.tpp"
