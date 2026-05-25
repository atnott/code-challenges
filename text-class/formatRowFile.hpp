#pragma once

#include<vector>
#include<string>

class formatRowFile {
public:
    std::vector<std::string> columns;
    formatRowFile(const std::string str);

    bool operator == (const formatRowFile& other) const;
    bool operator != (const formatRowFile& other) const;
};