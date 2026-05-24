#pragma once

#include <functional>
#include <vector>

using SignalID = int;
inline constexpr SignalID SIGNAL_NULL_ID = -1;

// Class for managing signal events.
template<typename... Args>
class Signal {
private:
    using Callback = std::function<void(Args...)>;

    struct Slot {
        SignalID id;
        Callback cb;
    };

    std::vector<Slot> _listeners;
    SignalID _next_id = 0;

public:
    // Connect a callback to the signal.
    // Returns a positive integer ID that can
    // be used to later disconnect from the signal.
    SignalID connect(Callback cb) {
        SignalID id = _next_id++;
        _listeners.push_back({id, std::move(cb)});
        return id;
    }

    // Disconnect a callback from the signal.
    void disconnect(SignalID id) {
        if (id < 0)
            return;

        int index = -1;
        for (int i = 0; i < _listeners.size(); i++) {
            if (_listeners[i].id == id) {
                index = i;
                break;
            }
        }

        if (index >= 0)
            _listeners.erase(_listeners.begin() + index);
    }

    // Emit a signal and call all of the connected callbacks.
    void emit(Args... args) {
        for (auto& slot : _listeners)
            slot.cb(args...);
    }

};
