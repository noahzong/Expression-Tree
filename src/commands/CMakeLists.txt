# Include all of the recognized commands
target_sources(Core PRIVATE
    ./command.cpp
    ./command_factory.cpp
    ./command_impl.cpp
    ./eval.cpp
    ./expr.cpp
    ./format.cpp
    ./macro.cpp
    ./null.cpp
    ./print.cpp
    ./quit.cpp
    ./set.cpp
        ./get.cpp
        ./list.cpp
        ./history.cpp
)