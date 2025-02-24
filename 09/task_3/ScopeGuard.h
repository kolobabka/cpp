#pragma once

#include <functional>
#include <concepts>

template<typename T>
concept CallableInScopeGuard = requires(const T& callable) {
    { callable() } noexcept -> std::same_as<void>;
};

template <CallableInScopeGuard ActionT>
class ScopeGuard {
    ActionT Act;
    bool GuardActive = true;
public:
    ScopeGuard(ActionT Act) : Act(Act) {}

    ~ScopeGuard() {
        if (GuardActive)
            Act();
    }

    void disable() noexcept { GuardActive = false; }
};
