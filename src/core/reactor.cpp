/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "core/reactor.h"
#include "core/event_handler.h"
#include <algorithm>
#include <functional>

Reactor* Reactor::inst = nullptr;

Reactor::Reactor()
    : runningEventLoop(true)
{
}

/**
 * @class Remove_Handler_Adapter
 * @brief This functor implements the Adapter pattern so an @a
 *        Reactor's remove_input_handler() method can be called
 *        with the appropriate Event_Handler in the context of the
 *        std:for_each() algorithm.
 */
struct RemoveHandlerAdapter {
    // Remote event_handler from the singleton Reactor.
    bool operator()(EventHandler* handler)
    {
        Reactor::instance()->removeHandler(handler);
        return true;
    }
};

Reactor::~Reactor()
{
    std::for_each(dispatchTable.begin(), dispatchTable.end(),
        [this](Handler* handler) { removeHandler(handler); });
}

Reactor* Reactor::instance()
{
    if (Reactor::inst == nullptr)
        Reactor::inst = new Reactor;
    return Reactor::inst;
}

void Reactor::registerHandler(Handler* handler)
{
    dispatchTable.push_back(handler);
}

void Reactor::removeHandler(Handler* handler)
{
    auto iter = std::remove(dispatchTable.begin(), dispatchTable.end(), handler);
    dispatchTable.erase(iter);
    delete handler;
}

void Reactor::runEventLoop()
{
    while (runningEventLoop)
        std::for_each(dispatchTable.begin(), dispatchTable.end(), std::mem_fn(&Handler::handle));
}

void Reactor::endEventLoop()
{
    runningEventLoop = false;
}
