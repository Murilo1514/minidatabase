#pragma once
#include <fstream>
#include <vector>
#include <cstring>

const int PAGE_SIZE = 4096;

enum PageType {
    INTERNAL = 1,
    LEAF = 2
};

// Estrutura fixa de header de página
struct PageHeader {
    PageType type;
    int keyCount;
    int nextPage;   // para folhas (encadeamento)
};

// Página representada em RAM
struct Page {
    PageHeader header;
    char data[PAGE_SIZE - sizeof(PageHeader)];
};

class PageManager {
private:
    std::string filename;

public:
    PageManager(const std::string& fname) : filename(fname) {}

    // cria o arquivo com 1 página vazia (root)
    void createNewFile() {
        std::ofstream out(filename, std::ios::binary | std::ios::trunc);

        Page root;
        root.header.type = LEAF;    // começa como folha
        root.header.keyCount = 0;
        root.header.nextPage = -1;
        memset(root.data, 0, sizeof(root.data));

        out.write((char*)&root, sizeof(Page));
    }

    // lê página N
    Page readPage(int pageNum) {
        std::ifstream in(filename, std::ios::binary);
        Page pg;

        in.seekg(pageNum * PAGE_SIZE);
        in.read((char*)&pg, sizeof(Page));

        return pg;
    }

    // grava página N
    void writePage(int pageNum, const Page& pg) {
        std::ofstream out(filename, std::ios::binary | std::ios::in);

        out.seekp(pageNum * PAGE_SIZE);
        out.write((char*)&pg, sizeof(Page));
    }

    // cria uma nova página no final do arquivo
    int allocatePage(PageType type) {
        std::fstream fs(filename, std::ios::binary | std::ios::in | std::ios::out);

        fs.seekp(0, std::ios::end);
        int newPageNum = fs.tellp() / PAGE_SIZE;

        Page pg;
        pg.header.type = type;
        pg.header.keyCount = 0;
        pg.header.nextPage = -1;
        memset(pg.data, 0, sizeof(pg.data));

        fs.write((char*)&pg, sizeof(Page));

        return newPageNum;
    }

};
