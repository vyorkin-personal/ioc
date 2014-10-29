
template<class T, class... Ts>
void Container::registerSingleton() {
    auto holder = std::make_shared<Holder<T>>();
    holder->instance = std::make_shared<T>(get<Ts>()...);
    instanceMap.emplace(typeid(T).name(), holder); 
}

template<class T>
void Container::registerInstance(const std::shared_ptr<T>& instance) {
    auto holder = std::make_shared<Holder<T>>();
    holder->instance = instance;
    instanceMap.emplace(typeid(T).name(), holder); 
}

template<class T, class... Ts>
void Container::registerClass() {
    auto func = [this]() -> T * {
        return new T(get<Ts>()...);
    };
    creatorMap.emplace(typeid(T).name(), func); 
}

template<class T>
std::shared_ptr<T> Container::get() {
    const auto typeName = typeid(T).name();
    const auto it = instanceMap.find(typeName);

    if (it == instanceMap.cend()) {
        auto creatorFunc = creatorMap[typeName]; 
        auto result = creatorFunc();

        return std::shared_ptr<T>(static_cast<T*>(result));
    } else {
        std::shared_ptr<IHolder> iholder = instanceMap[typeName];
        Holder<T>* holder = dynamic_cast<Holder<T>*>(iholder.get());

        return holder->instance;
    }
}
