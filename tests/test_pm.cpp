#include <iostream>
#include "../pagemanager.hpp"

int main() {
    PageManager pm("index.idx");
    pm.createNewFile();

    Page root = pm.readPage(0);
    std::cout << "Tipo da página raiz: " << root.header.type << "\n";
    std::cout << "Keys: " << root.header.keyCount << "\n";

    int newPage = pm.allocatePage(LEAF);
    std::cout << "Nova página criada: " << newPage << "\n";

    return 0;
}
