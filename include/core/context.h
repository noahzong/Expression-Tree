/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef CONTEXT_H
#define CONTEXT_H

#include "core/state.h"
#include "interpreter/variable_map.h"
#include "tree/expression_tree.h"
#include <memory>
#include <queue>
#include <string>

/**
 * @class Context
 * @brief Interface for the State pattern that is used to ensure that
 *        commands are invoked according to the correct protocol.
 *
 *        Plays the role of the "context" class in the State pattern
 *        and delegates to the appropriate "state" subclass that
 *        performs the commands.
 */
class Context {
public:
    // Constructor.
    explicit Context(std::ostream&);

    VariableMap& getVariables();

    // Set the desired format to the designated new_format.
    void format(const std::string& newFormat);

    // Make an expression tree based on the designated expression using the previously designated
    // format.
    void makeTree(const std::string& expression);

    // Print the most recently created expression tree using the designated format.
    void print(const std::string& format);

    // Evaluate the "yield" of the most recently created expression tree using the designated
    // format.
    int evaluate(const std::string& format);

    // Set the value of the variable is a string of the format "variable_name=variable_value"
    void set(const std::string& kvPair);

    // Returns the value of the requested variable
    void get(const std::string& var);

    // Prints out a list of variables in use
    void list();

    // Return a pointer to the current State.
    [[nodiscard]] State* state() const;

    // Set the current State to the designated new_state pointer.
    void state(State* new_state);

    // Return a reference to the current ExpressionTree.
    ExpressionTree& tree();

    // Set the current ExpressionTree to the newTree.
    void tree(const ExpressionTree& newTree);

    // Returns whether or not a successful format call has been called
    [[maybe_unused]] [[nodiscard]] bool formatted() const;

    // Where all output should be printed
    [[nodiscard]] std::ostream& output() const;

    // Returns the history queue
    std::queue<std::string> getHistory();

    // Prints out the history queue
    void history();

    // Adds command to history queue
    void addCommand(std::string);

private:
    // Persistent interpreter context for variables. Our interpreter
    // will change values inside of this, so I just stuck the variable
    // in the public section.
    VariableMap variables;
    // Keep track of the current state that we're in.  We use an @a
    // std::unique_ptr to simplify memory management and avoid memory leaks.
    std::unique_ptr<State> treeState;
    // Current expression tree.
    ExpressionTree expTree;
    // Had the format been set
    bool isFormatted;
    // Where is output being directed
    std::ostream& os;
    // Queue keeps track of history
    std::queue<std::string> historyQ;
};

#endif // CONTEXT_H
