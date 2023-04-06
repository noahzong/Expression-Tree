/* Copyright G. Hemingway @ 2022, All Rights Reserved */
#ifndef VARIABLE_MAP
#define VARIABLE_MAP

#include <string>
#include <unordered_map>

/***
 * @class VariableMap
 * @brief This class stores variables and their values for use by the Interpreters.
 *        This class plays the role of the "context" in the Interpreter pattern.
 */
class VariableMap {
public:
    // Constructor.
    VariableMap() = default;
    // Destructor.
    ~VariableMap() = default;
    // Return the value of a variable.
    [[nodiscard]] int get(const std::string& variable) const;
    // Set the value of a variable.
    void set(const std::string& variable, int value);
    // False if not variables are declared
    [[maybe_unused]] [[nodiscard]] bool isEmpty() const;
    // Print all variables and their values.
    void print(std::ostream& os) const;
    // Clear all variables and their values.
    [[maybe_unused]] void reset();

private:
    // Unordered map containing variable names and values.
    std::unordered_map<std::string, int> map;
};

#endif // VARIABLE_MAP
