#ifndef GENERATOR_HPP
#define GENERATOR_HPP

#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

template<typename port_type>
struct generatorState {
    port_type output;
    double sigma;

    explicit generatorState<port_type>(port_type val, double _sigma): output(val), sigma(_sigma) {
    }
};

template<typename port_type>
std::ostream& operator<<(std::ostream &out, const generatorState<port_type>& state) {
    out  << "{output: " << state.output << ", sigma: " << state.sigma <<"}";
    return out;
}

template<typename port_type>
class generator : public Atomic<generatorState<port_type>> {
    public:
    Port<port_type> out;

    generator(const std::string id, port_type val, double sigma) :   Atomic<generatorState<port_type>>(id, generatorState<port_type>(val, sigma)) {
        out = generator<port_type>::template addOutPort<port_type>("out");
    }

    void internalTransition(generatorState<port_type>& state) const override {
    }

    // external transition
    void externalTransition(generatorState<port_type>& state, double e) const override {
        //Nothing should happen here
    }
    
    
    // output function
    void output(const generatorState<port_type>& state) const override {
        out->addMessage(state.output);
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const generatorState<port_type>& state) const override {
        return state.sigma;
    }
};

#endif