/**
 * @file Exceptions.cpp
 * @author James Mok (jmok780@gmail.com)
 * @brief Implementations of errors
 * @version 1.0.0
 * @date 2023-08-24
 */

#include "Exceptions.hpp"

ostream& GeneralException::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail;
    return out;
}

ostream& InsufficientKeysException::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail << endl;
    out << "Keys Inputted: " << input << endl;
    out << "Keys Required: " << min;
    return out;
}

ostream& SecretDoesNotMatchException::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail;
    return out;
}

ostream& GenerateTwoShareSetsException::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail;
    return out;
}

ostream& EmptyShareSetException::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail;
    return out;
}

ostream& UnexpectedResultException::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail << endl;
    out << "Received Value: " << result << endl;
    out << "Expected Value: " << expected;
    return out;
}

ostream& IncalculableSecret::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail;
    return out;
}