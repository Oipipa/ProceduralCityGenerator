#include "lsystem.h"

LSystem::LSystem(const std::string &axiom) : axiom(axiom) {}

void LSystem::addRule(char symbol, const std::string &replacement) {
    rules[symbol] = replacement;
}

std::string LSystem::generate(int iterations) {
    std::string current = axiom;
    for (int i = 0; i < iterations; ++i) {
        std::string next;
        for (char c : current) {
            next += (rules.find(c) != rules.end()) ? rules[c] : std::string(1, c);
        }
        current = next;
    }
    return current;
}
