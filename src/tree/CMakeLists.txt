# Include all of the recognized tree node types
target_sources(Core PRIVATE
    ./expression_tree.cpp
    ./expression_tree_iterator.cpp
    ./expression_tree_iterator_impl.cpp
    ./component_node.cpp
    ./leaf_node.cpp
    ./add_node.cpp
    ./binary_node.cpp
    ./divide_node.cpp
    ./multiply_node.cpp
    ./negate_node.cpp
    ./subtract_node.cpp
    ./unary_node.cpp
        ./exponent_node.cpp
        ./modulus_node.cpp
        ./factorial_node.cpp
./floor_node.cpp
        ./ceiling_node.cpp
)