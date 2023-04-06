# Include all of the "front-end" stuff
target_sources(Core PRIVATE
    ./event_handler.cpp
    ./context.cpp
    ./state.cpp
    ./options.cpp
    ./getopt.cpp
    ./reactor.cpp
)
