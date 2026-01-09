#pragma once
#include <string>
#include <fstream>

struct Record{
    int id;
    char name[50];
    double value;
};

class DataFile {
private:
    std::string filename;

public:
    DataFile(const std::string& fname): filename(fname) {}

    long append(const Record& rec){
        std::ofstream out(filename, std::ios::binary | std::ios::app);
        if(!out) throw std::ios_base::failure("Failed to open file for appending");
        long offset = out.tellp();
        out.write(reinterpret_cast<const char*>(&rec), sizeof(Record));
   
        return offset;
    }

    Record read(long offset){
        std::ifstream in(filename, std::ios::binary);
        if(!in) throw std::ios_base::failure("Failed to open file for reading");
        in.seekg(offset);
        Record rec;
        in.read(reinterpret_cast<char*>(&rec), sizeof(Record));
        return rec;
    }

    void update(long offset, const Record& rec) {
        std::ofstream out(filename, std::ios::binary | std::ios::in);
        out.seekp(offset);
        out.write(reinterpret_cast<const char*>(&rec), sizeof(Record));
    }


};