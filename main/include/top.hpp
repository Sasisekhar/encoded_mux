#ifndef SAMPLE_TOP_HPP
#define SAMPLE_TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "encoded_mux.hpp"
#include "generator.hpp"
#include <random>
#include <functional>

using namespace cadmium;

//vary these two values to test various datatypes and number of ports.
#define NUM_PORTS 10
using port_type = int; //When you change the datatype, remember to change rand_val() accordingly.

struct top_coupled : public Coupled {

    /**
     * Constructor function for the top model.
     * @param id ID of the top model.
     */
    top_coupled(const std::string& id) : Coupled(id) {

        //create random generators for sigma and value
        std::default_random_engine rand_generator;
        std::uniform_int_distribution<int> distribution_val(1,10);
        std::uniform_int_distribution<int> distribution_sigma(1,100);
        auto rand_val = std::bind ( distribution_val, rand_generator );
        auto rand_sigma = std::bind ( distribution_sigma, rand_generator );

        //Atomic models that will produce outputs for the mux
        std::vector<std::shared_ptr<generator<port_type>>> testers;

        for(int i = 0; i < NUM_PORTS; i++) {
            std::string model_name = "genr_" + std::to_string(i);
            auto model = addComponent<generator<port_type>>(model_name, rand_val(), rand_sigma()/10.0);
            testers.push_back(model);
        }

        auto mux = addComponent<encoded_mux<port_type>>("multiplexer", NUM_PORTS);

        for(int i = 0; i < NUM_PORTS; i++) {
            addCoupling(testers.at(i)->out, mux->in_ports.at(i));
        }
    }
};

#endif