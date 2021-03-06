

#ifndef _CONSUMER_H_
#define _CONSUMER_H_

#include "sparta/simulation/Resource.hpp"
#include "sparta/simulation/ParameterSet.hpp"
#include "sparta/ports/DataPort.hpp"
#include "sparta/ports/SignalPort.hpp"
#include "sparta/ports/PortSet.hpp"
#include "sparta/events/UniqueEvent.hpp"
#include "sparta/utils/ValidValue.hpp"

class Consumer : public sparta::Resource
{
public:

    //! \brief Name of this resource. Required by sparta::ResourceFactory
    static const char * name;

    class ConsumerParameterSet : public sparta::ParameterSet
    {
    public:
        ConsumerParameterSet(sparta::TreeNode* n) :
            sparta::ParameterSet(n)
        {
        }
        PARAMETER(uint32_t, num_producers, 1, "Number of producers")
    };

    Consumer (sparta::TreeNode * name,
              const ConsumerParameterSet * p);

private:
    // The Consumer's PortSet
    sparta::PortSet port_set_;

    // Consumer's InPort to get data
    sparta::DataInPort<uint32_t> consumer_in_port_{&port_set_, "consumer_in_port", 1};

    // Consumer's push-back (or go) port
    std::vector<std::unique_ptr<sparta::SignalOutPort>> producer_go_port_;
    uint32_t current_producer_ = 0;
    const uint32_t num_producers_;

    // Consumer's receiving callback
    void receiveData_(const uint32_t & dat);
    sparta::utils::ValidValue<uint32_t> arrived_data_;

    // An Event scehduled when data arrives
    sparta::EventSet      event_set_;
    // 0 cycle delay on scheduling
    sparta::UniqueEvent<> ev_data_arrived_{&event_set_, "ev_data_arrived",
            CREATE_SPARTA_HANDLER(Consumer, dataArrived_), 0};

    // Operate on incoming data
    void dataArrived_();

    // Startup handler
    void signalNextProducer_();

    // Stats
    sparta::StatisticSet stat_set_;
    sparta::Counter      num_consumed_{&stat_set_, "num_consumed",
            "Number of items consumed", sparta::Counter::COUNT_NORMAL};

    //! Loggers
    sparta::log::MessageSource consumer_log_;

};

#endif
