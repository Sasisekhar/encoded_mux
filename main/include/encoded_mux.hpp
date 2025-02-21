#ifndef ENCODED_MUX_HPP
#define ENCODED_MUX_HPP

#include <random>
#include <iostream>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

/**
 * @brief state set of the encoded_mux
 */
template<typename port_type>
struct encoded_muxState {
    std::vector<port_type> values;
    bool output_available;

    explicit encoded_muxState<port_type>(): values(), output_available(false){
    }
};
template<typename port_type>
std::ostream& operator<<(std::ostream &out, const encoded_muxState<port_type>& state) {
    //<! Tertiary conditional is used below because implementation of << for 'bool' differs based on platform.
    out  << "{output_available:" << ((state.output_available)? "true" : "false") << "}";
    return out;
}

template<typename port_type>
class encoded_mux : public Atomic<encoded_muxState<port_type>> {
    public:

    //Declare your ports here
    std::vector<Port<port_type>> in_ports;
    Port<port_type> out_port;

    encoded_mux(const std::string id, int number_of_ports) : Atomic<encoded_muxState<port_type>>(id, encoded_muxState<port_type>()) {

        for(int i = 0; i < number_of_ports; i++) {
            std::string port_id = "input_" + std::to_string(i);
            auto port = encoded_mux<port_type>::template addInPort<port_type>(port_id);
            in_ports.push_back(port);
        }

        out_port = encoded_mux<port_type>::template addOutPort<port_type>("output");
    }

    // inernal transition
    void internalTransition(encoded_muxState<port_type>& state) const override {
        state.output_available = false;
    }

    // external transition
    void externalTransition(encoded_muxState<port_type>& state, double e) const override {
        state.values.clear();
        for(auto port: in_ports) {
            if(!port->getBag().empty()) {
                state.values.push_back(port->getBag().back());
            }
        }

        state.output_available = true;
    }
    
    
    // output function
    void output(const encoded_muxState<port_type>& state) const override {
        for(auto value: state.values) {
            out_port->addMessage(value);
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const encoded_muxState<port_type>& state) const override {  
        if(state.output_available) {
            return 0;
        } else {
            return std::numeric_limits<double>::infinity();
        }
    }
};

#endif