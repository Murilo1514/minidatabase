#include <iostream>
#include "../datafile.hpp"

int main() {
    DataFile df("database.db");

    Record r1{1, "Joao", 100.5};
    long off1 = df.append(r1);

    Record r2 = df.read(off1);
    std::cout << "Lido: " << r2.id << " " << r2.name << " " << r2.value << "\n";

    r2.value = 999.9;
    df.update(off1, r2);

    Record r3 = df.read(off1);
    std::cout << "Atualizado: " << r3.value << "\n";

    return 0;
}
