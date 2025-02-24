#include <iostream>
#include <memory>

///////////////////////////////////////////////////////////

class Entity
{
public:

    virtual ~Entity() = default;

//  ------------------------------

    virtual void test() const = 0;
};

///////////////////////////////////////////////////////////

class Client : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Client::test\n";
    } 
};

///////////////////////////////////////////////////////////

class Server : public Entity 
{ 
public: 
    
    void test() const override 
    { 
        std::cout << "Server::test\n";
    } 
};

///////////////////////////////////////////////////////////

template < typename E > auto make_entity() -> std::unique_ptr<Entity>
{ 
    return std::unique_ptr<Entity>{new E};
}

///////////////////////////////////////////////////////////

class Router : public Entity
{
public:

    class Factory
    {
    public:

        static auto make_v1() -> std::unique_ptr<Entity> { return std::unique_ptr<Entity>(new Router(1)); }
        
        static auto make_v2() -> std::unique_ptr<Entity> { return std::unique_ptr<Entity>(new Router(2)); }
    };

//  -------------------------------------------------------

    void test() const override 
    { 
        std::cout << "Router::test\n";
    }

private:

    Router(int x) : m_data(x) {}

//  -------------------------------------------------------

    int m_data = 0;
};

///////////////////////////////////////////////////////////

class Factory
{
public:

    virtual ~Factory() = default;

    virtual std::unique_ptr<Entity> make() const = 0;
};

///////////////////////////////////////////////////////////

class Factory_Client : public Factory 
{ 
public: 
    
    std::unique_ptr<Entity> make() const override 
    { 
        return std::unique_ptr<Entity>{new Client};
    } 
};

///////////////////////////////////////////////////////////

class Factory_Server : public Factory 
{ 
public: 
    
    std::unique_ptr<Entity> make() const override 
    { 
        return std::unique_ptr<Entity>{new Server};
    } 
};

///////////////////////////////////////////////////////////

int main()
{
    {
        auto entity = make_entity < Client > ();

        entity->test();
    }
    
//  ---------------------------------------------

    {
        auto entity = Router::Factory::make_v1();

        entity->test();
    }

//  ---------------------------------------------

    {
        std::unique_ptr<Factory> factory = std::unique_ptr<Factory>(new Factory_Server);

        auto entity = factory->make();

        entity->test();
    }
}
