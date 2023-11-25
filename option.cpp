#pragma once
#include <iostream>

template<typename T = bool>
struct option {
    option(T value) : _value(value) {
        _isSet = true;
    }

    option() : _value() {
        _isSet = false;
    }

    T expect(const std::string &msg) {
        if (!_isSet) {
            std::cout << msg << std::endl;
            throw;
        }
        return _value;
    }

    static option none() {
        return {};
    }

private:
    T _value;
    bool _isSet = false;
};

