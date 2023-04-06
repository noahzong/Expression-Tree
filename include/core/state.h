/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <map>
#include <string>

// Forward declaration.
class Context;
class ExpressionTree;

/**
 * @class State
 * @brief Implementation of the State pattern that is used to define
 *        the various states that affect how users operations are
 *        processed.
 *
 *        Plays the role of the "state" base class in the State
 *        pattern that is used as the basis for the subclasses that
 *        actually define the various user operation states.
 */
class State {
public:
    // Exception class for Invalid States exceptions
    class InvalidState : public std::domain_error {
    public:
        explicit InvalidState(const std::string& message)
            : std::domain_error(message)
        {
        }
    };

    explicit State(Context& ctx)
        : context(ctx) {};

    virtual ~State() = default;

    // Set the desired format to the designated format, updating
    // the state of the @context accordingly.
    virtual void format(const std::string& format) = 0;

    // Make an expression tree based on the designated expression
    // using the previously designated format, updating the state of
    // the @context accordingly.
    virtual void makeTree(const std::string& expression) = 0;

    // Print the most recently created expression tree using the
    // designated format, updating the state of the @context
    // accordingly.
    virtual void print(const std::string& format, std::ostream& os) = 0;

    // Evaluate the "yield" of the most recently created expression
    // tree using the designated format, updating the state of the
    // @context accordingly.
    virtual int evaluate(const std::string& format) = 0;

    // Print the appropriate commands that are available to the user
    virtual void printValidCommands() const = 0;

protected:
    // Print the tree in the designated traversal_order.
    static void printTree(const ExpressionTree& tree, const std::string& order, std::ostream& os);

    // Evaluate and print the yield of the tree to the @os in the
    // designated traversal_order.
    static auto evaluateTree(const ExpressionTree& tree, const std::string& order);

    Context& context;
};

/**
 * @class UninitializedState
 * @brief This is the initial state, which only allows format commands.
 */
class UninitializedState : public State {
public:
    explicit UninitializedState(Context& ctx);

    // Sets the context's state to correspond to the designated
    // new_format, e.g., PreOrderUninitializedState,
    // PostOrderUninitializedState, InOrderUninitializedState,
    // or LevelOrderUninitializedState.
    void format(const std::string& new_format) override;

    // Make an expression tree based on the designated expression
    // using the previously designated format, updating the state of
    // the @context accordingly.
    void makeTree(const std::string&) override;

    // Print the most recently created expression tree using the
    // designated format, updating the state of the @context
    // accordingly.
    void print(const std::string& format, std::ostream& os) override;

    // Evaluate the "yield" of the most recently created expression
    // tree using the designated format, updating the state of the
    // @context accordingly.
    int evaluate(const std::string& format) override;

    // Print the list of valid command if the user is in this state
    void printValidCommands() const override;

private:
    /**
     * @class UninitializedStateFactory
     * @brief Implementation of a factory pattern that dynamically
     *        allocates the appropriate State object.
     *
     *        This is a variant of the Abstract Factory pattern that has a
     *        set of related factory methods but which doesn't use
     *        inheritance.
     */
    class UninitializedStateFactory {
    public:
        // Constructor.
        UninitializedStateFactory();

        // Dynamically allocate a new ExpressionTreeState
        // object based on the designated traversal_order and end_iter.
        static State* makeUninitializedState(Context& context, const std::string& format);

    private:
        // Dynamically allocate a new LevelOrderUninitializedState
        // object based on the designated end_iter.
        static State* makeInOrderUninitializedState(Context&);

        // Dynamically allocate a new PreOrderUninitializedState
        // object based on the designated end_iter.
        static State* makePreOrderUninitializedState(Context&);

        // Dynamically allocate a new PostOrderUninitializedState
        // object based on the designated end_iter.
        static State* makePostOrderUninitializedState(Context&);

        // Dynamically allocate a new LevelOrderUninitializedState
        // object based on the designated end_iter.
        static State* makeLevelOrderUninitializedState(Context&);

        typedef State* (*UNINITIALIZED_STATE_PTF)(Context&);
        typedef std::map<std::string, UNINITIALIZED_STATE_PTF> UNINITIALIZED_STATE_MAP;
        static UNINITIALIZED_STATE_MAP uninitializedStateMap;
    };

    static UninitializedStateFactory uninitializedStateFactory;
};

/**
 * @class PreOrderUninitializedState
 * @brief Now that the user has provided a format command
 *        indicating "pre-order" input this state will interpret the
 *        subsequent expression accordingly.
 */
class PreOrderUninitializedState : public UninitializedState {
public:
    explicit PreOrderUninitializedState(Context& ctx);

    // Process the expression using a pre-order interpreter and
    // update the state of the context to the PreOrderInitializedState.
    void makeTree(const std::string& expression) override;
};

/**
 * @class PreOrderInitializedState
 * @brief Now that the user has provided a expr command this state
 *        will print or evaluate the subsequent expression
 *        accordingly.
 */
class PreOrderInitializedState : public PreOrderUninitializedState {
public:
    explicit PreOrderInitializedState(Context& ctx);

    // Print the current expression tree in the context using the designed format.
    void print(const std::string& format, std::ostream& os) override;

    // Evaluate the yield of the current expression tree in the context using the designed format.
    int evaluate(const std::string& format) override;
};

/**
 * @class PostOrderUninitializedState
 * @brief Now that the user has provided a format command
 *        indicating "post-order" input this state will interpret the
 *        subsequent expression accordingly.
 */
class PostOrderUninitializedState : public UninitializedState {
public:
    explicit PostOrderUninitializedState(Context& ctx);

    // Process the expression using a post-order interpreter and
    // update the state of the context to the PostOrderInitializedState.
    void makeTree(const std::string& expression) override;
};

/**
 * @class PostOrderInitializedState
 * @brief Now that the user has provided a expr command this state
 *        will print or evaluate the subsequent expression
 *        accordingly.
 */
class PostOrderInitializedState : public PostOrderUninitializedState {
public:
    explicit PostOrderInitializedState(Context& ctx);

    // Print the current expression tree in the context using the
    // designed format.
    void print(const std::string& format, std::ostream& os) override;

    // Evaluate the yield of the current expression tree in the @a
    // context using the designed format.
    int evaluate(const std::string& format) override;
};

/**
 * @class InOrderUninitializedState
 * @brief Now that the user has provided a format command
 *        indicating "in-order" input this state will interpret the
 *        subsequent expression accordingly.
 */
class InOrderUninitializedState : public UninitializedState {
public:
    explicit InOrderUninitializedState(Context& ctx);

    // Process the expression using an in-order interpreter and
    // update the state of the context to the InOrderInitializedState.
    void makeTree(const std::string& expression) override;

    // Print the list of valid command if the user is in this state
    void printValidCommands() const override;
};

/**
 * @class InOrderInitializedState
 * @brief Now that the user has provided a expr command this state
 *        will print or evaluate the subsequent expression
 *        accordingly.
 */
class InOrderInitializedState : public InOrderUninitializedState {
public:
    explicit InOrderInitializedState(Context& ctx);

    // Print the current expression tree in the context using the
    // designed format.
    void print(const std::string& format, std::ostream& os) override;

    // Evaluate the yield of the current expression tree in the @a
    // context using the designed format.
    int evaluate(const std::string& format) override;

    // Print the list of valid command if the user is in this state
    void printValidCommands() const override;
};

/**
 * @class LevelOrderUninitializedState
 * @brief Now that the user has provided a format command
 *        indicating "level-order" input this state will interpret the
 *        subsequent expression accordingly.
 */
class LevelOrderUninitializedState : public UninitializedState {
public:
    explicit LevelOrderUninitializedState(Context& ctx);

    // Process the expression using a level-order interpreter and
    // update the state of the context to the LevelOrderInitializedState.
    void makeTree(const std::string& expression) override;
};

/**
 * @class LevelOrderInitializedState
 * @brief Now that the user has provided a expr command this state
 *        will print or evaluate the subsequent expression
 *        accordingly.
 */
class LevelOrderInitializedState : public LevelOrderUninitializedState {
public:
    explicit LevelOrderInitializedState(Context& ctx);

    // Print the current expression tree in the context using the
    // designed format.
    void print(const std::string& format, std::ostream& os) override;

    // Evaluate the yield of the current expression tree in the @a
    // context using the designed format.
    int evaluate(const std::string& format) override;
};

#endif // STATE_H
