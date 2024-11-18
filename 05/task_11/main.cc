#include <iostream>
#include <string>
#include <string_view>

struct Notifier {
    virtual void send(std::string_view Message) const = 0;
};

struct EmailNotifier final : public Notifier {
    void send(std::string_view Message) const override {
        std::cout << "Email: " << Message << std::endl;
    }
};

class NotifierDecorator : public Notifier {
protected:
    const Notifier &NotifierWrap;
public:
    virtual ~NotifierDecorator() = default;
    NotifierDecorator(const Notifier &N) : NotifierWrap(N) {}
    void send(std::string_view Message) const override {
        NotifierWrap.send(Message);
    }
};

struct SMSNotifier final : public NotifierDecorator {
    SMSNotifier(const Notifier &N) : NotifierDecorator(N) {}
    void send(std::string_view Message) const override {
        NotifierDecorator::send(Message);
        std::cout << "SMS: " << Message << std::endl;
    }
};

struct FacebookNotifier final : public NotifierDecorator {
    FacebookNotifier(const Notifier &N) : NotifierDecorator(N) {}
    void send(std::string_view Message) const override {
        NotifierDecorator::send(Message);
        std::cout << "Facebook: " << Message << std::endl;
    }
};

int main() {
    EmailNotifier ENotifier;

    SMSNotifier SNotifier(ENotifier);

    FacebookNotifier FNotifier(SNotifier);

    std::cout << "Sending notifications:" << std::endl;
    FNotifier.send("Hello, Decorator Pattern!");

    return 0;
}
