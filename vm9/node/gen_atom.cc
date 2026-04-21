#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include "node.hh"

/**
 * To use: 
 * g++ -o gen_atoms main.cpp
 * ./gen_atoms ok error retry > atoms.h
 */

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <name1> <name2> ...\n";
        return 1;
    }

    std::hash<std::string> hasher;

    std::cout << "// Auto-generated header file\n";
    std::cout << "#ifndef ATOMS_H\n#define ATOMS_H\n\n";

    for (int i = 1; i < argc; ++i) {
        std::string name = argv[i];
        Node::Integer hash_value = hasher(name);

        // Print the define in the requested format
        std::cout << "#define atom_" << name << " " << hash_value << "\n";
    }

    std::cout << "\n#endif // ATOMS_H\n";

    return 0;
}


