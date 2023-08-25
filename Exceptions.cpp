#include "Exceptions.hpp"

ostream& GeneralException::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail << endl;
    return out;
}

ostream& InsufficientKeysException::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail << endl;
    out << "Keys Inputted: " << input << endl;
    out << "Keys Required: " << min << endl;
    return out;
}

ostream& SecretDoesNotMatchException::
print(ostream& out) const {
    out << title << " Code: " << code << " - " << detail << endl;
    return out;
}