#include "Exceptions.hpp"

ostream& GeneralException::
print(ostream& out) const {
    out << title << code << " - " << detail << endl;
    return out;
}

ostream& InsufficientKeysException::
print(ostream& out) const {
    out << title << code << " - " << detail << endl;
    out << "Keys Inputted: " << input << endl;
    out << "Keys Required: " << min << endl;
    return out;
}