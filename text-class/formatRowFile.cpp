#include"formatRowFile.hpp"
#include<sstream>

using std::vector;
using std::string;

formatRowFile::formatRowFile(const string str) {
    std::stringstream ss(str);
    string word;
    while (ss >> word) {
        columns.push_back(word);
    }
}

bool formatRowFile::operator == (const formatRowFile& other) const {
    return this->columns == other.columns;
}

bool formatRowFile::operator != (const formatRowFile& other) const {
    return this->columns != other.columns;
}