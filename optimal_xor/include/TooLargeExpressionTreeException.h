//
// Created by barak on 20/06/2020.
//

#ifndef AILABGENETICALGORITHM_TOOLARGEEXPRESSIONTREEEXCEPTION_H
#define AILABGENETICALGORITHM_TOOLARGEEXPRESSIONTREEEXCEPTION_H

#include <exception>
#include <string>
#include <vector>

class TooLargeExpressionTreeException : public std::exception {
public:
    TooLargeExpressionTreeException(const int treeHeight, const int maxAllowed)
    : message{"ERROR! Too large tree! your size is: " + std::to_string(treeHeight) + ", while max allowed is: " + std::to_string(maxAllowed)}
    {}
    const char* what () const throw (){
        return message.c_str();
    }

protected:
    const std::string message;
};

#endif //AILABGENETICALGORITHM_TOOLARGEEXPRESSIONTREEEXCEPTION_H
