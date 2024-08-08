#ifndef LSYSTEM_H
#define LSYSTEM_H

#include <string>
#include <map>

class LSystem {
public:
    LSystem(const std::string &axiom);
    void addRule(char symbol, const std::string &replacement);
    std::string generate(int iterations);

private:
    std::string axiom;
    std::map<char, std::string> rules;
};

#endif // LSYSTEM_H
