/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef REACTOR_H
#define REACTOR_H

#include <vector>

/**
 * @class HandlerBase
 * @brief Provides an abstract interface for handling various types of
 *        events, e.g., input events.
 *
 *         Subclasses read/write input/output on an I/O handle, etc.
 */
class Handler {
public:
    // Destructor can be made private to ensure dynamic allocation.
    virtual ~Handler() = default;

    // Called back by the Reactor when input events occur.
    virtual void handle() = 0;
};

/**
 * @class Reactor
 * @brief An object-oriented event demultiplexor and dispatcher of
 *        event handler callback methods in response to input events.
 *
 *        This class plays the role of the "reactor" in the
 *        Reactor pattern.  It is access as a singleton and uses the
 *        Iterator pattern to dispatch the various event handlers.
 */
class Reactor {
public:
    // Singleton access point.
    static Reactor* instance();

    // Dtor.
    ~Reactor();

    // Run the reactor's event loop.
    void runEventLoop();

    // End the reactor's event loop.
    void endEventLoop();

    // Register event_handler for input events.
    void registerHandler(Handler* handler);

    // Remove event_handler for input events.
    void removeHandler(Handler* handler);

private:
    // Constructor is private to ensure use as a singleton.
    Reactor();

    // Pointer to the singleton instance of the Reactor.
    static Reactor* inst;

    // Vector of pointers to Event_Handler objects used to dispatch callbacks.
    std::vector<Handler*> dispatchTable;

    // Keeps track of whether we're running the event loop or not.
    bool runningEventLoop;
};

#endif // REACTOR_H
