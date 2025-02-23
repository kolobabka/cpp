#include <cassert>
#include <cstddef>
#include <vector>
#include <memory>

//////////////////////////////////////////////////////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default;

//  -------------------------------------

    virtual std::size_t size() const = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////

class Client : public Entity { public: std::size_t size() const override { return 1; } };

class Server : public Entity { public: std::size_t size() const override { return 2; } };

//////////////////////////////////////////////////////////////////////////////////////////

template <typename T, typename... ArgsT>
std::unique_ptr<Entity> make_entity(ArgsT&&... Args);

class Composite : public Entity
{
public:
    Composite(std::size_t size_1 = 0, std::size_t size_2 = 0) {
        for (auto i = 0; i < size_1; ++i) { add_entity<Client>(); }
        for (auto i = 0; i < size_2; ++i) { add_entity<Server>(); }
    }
//  ------------------------------------

    template<typename T, typename... ArgsT>
    void add_entity(ArgsT&&... Args) 
    { 
        m_entities.push_back(std::move(make_entity<T>(std::forward<ArgsT>(Args)...)));
    }

//  ------------------------------------

    std::size_t size() const override
    {
        auto size = 0u;

        for (auto &&entity : m_entities)
        {
            if (entity) 
            {
                size += entity->size();
            }
        }

        return size;
    }

private:
    
    std::vector <std::unique_ptr<Entity>> m_entities;
};

//////////////////////////////////////////////////////////////////////////////////////////

// TOOD: T is dervied from entity :) 
template <typename T, typename... ArgsT>
std::unique_ptr<Entity> make_entity(ArgsT&&... Args) 
{
    if constexpr(std::is_same_v<T, Client>)
        return std::unique_ptr<Entity>(new Client(std::forward<ArgsT>(Args)...));
    if constexpr(std::is_same_v<T, Server>)
        return std::unique_ptr<Entity>(new Server(std::forward<ArgsT>(Args)...));
    if constexpr(std::is_same_v<T, Composite>)
        return std::unique_ptr<Entity>(new Composite(std::forward<ArgsT>(Args)...));
}

//////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    auto composite = std::make_unique<Composite>();

    for (auto i = 0u; i < 5; ++i)
    {
        composite->add_entity<Composite>(1, 1);
    }

    assert(composite->size() == 15);
}