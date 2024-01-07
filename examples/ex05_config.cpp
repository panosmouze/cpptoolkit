#include "CtIO.hpp"

#include <iostream>

int main() {
    CtConfigParser parser("config.ini");
    std::cout << parser.parseAsUInt("alpha") << std::endl;
    std::cout << parser.parseAsInt("beta") << std::endl;
    std::cout << parser.parseAsFloat("gamma") << std::endl;
    std::cout << parser.parseAsString("name") << std::endl;
    std::cout << parser.parseAsString("email") << std::endl;
    return 0;
}
