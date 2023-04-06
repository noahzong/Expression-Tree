/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#include "core/event_handler.h"
#include "core/options.h"
#include "core/reactor.h"

int main(int argc, char* argv[])
{
    // Create Options singleton to parse command line options.
    std::unique_ptr<Options> options(Options::instance());

    // Parse the command-line options.
    if (!options->parseArgs(argc, argv))
        std::terminate();

    // Create Reactor singleton to run application event loop.
    std::unique_ptr<Reactor> reactor(Reactor::instance());

    // Dynamically allocate the appropriate event handler based on the command-line options.
    EventHandler* handler = EventHandler::makeHandler(options->verbose(), std::cout);

    // Register the event handler with the reactor.  The reactor is responsible for
    // triggering the deletion of the event handler
    reactor->registerHandler(handler);

    // Run the reactor's event loop, which drives all the processing
    // via callbacks to registered event handlers.
    reactor->runEventLoop();

    // The std::unique_ptr destructors automatically destroy the singletons.
    return 0;
}
