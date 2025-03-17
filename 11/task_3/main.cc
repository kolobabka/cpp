#include <algorithm>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include <unordered_map>

struct base_entity
{
    virtual ~base_entity() = default;
    virtual void print() const = 0;
};

struct first_entity final : base_entity
{
    void print () const override
    {
        std::cout << "first_entity is created" << std::endl;
    }
};

struct second_entity final : base_entity
{
    void print () const override
    {
        std::cout << "second_entity is created" << std::endl;
    }
};

class entity_factory {
public:
    using creator_func = std::function<std::unique_ptr<base_entity> ()>;

    void register_entity (const std::string& type, creator_func creator)
    {
        creators_ [type] = std::move (creator);
    }

    std::unique_ptr<base_entity> create (const std::string& type) const
    {
        auto it = creators_.find(type);
        if (it != creators_.end())
            return it->second();

        return nullptr;
    }

private:
    std::unordered_map<std::string, creator_func> creators_;
};

auto main () -> int
{
    entity_factory factory;

    factory.register_entity ("first_entity", []() { return std::make_unique<first_entity>(); });
    factory.register_entity ("second_entity", []() { return std::make_unique<second_entity>(); });

    auto first_entity = factory.create ("first_entity");
    if (first_entity)
        first_entity->print ();

    auto second_entity = factory.create ("second_entity");
    if (second_entity)
        second_entity->print ();


    auto third_entity = factory.create ("third_entity");
    if (!third_entity)
        std::cerr << "third_entity is not found" << std::endl;

    return 0;
}

