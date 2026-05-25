#pragma once
#include"formatRowFile.hpp"
#include<string>
#include<fstream>
#include<stdexcept>

template <class T>
class TextFile {
	std::string filePath;
	bool isWriteMode;
public:
    std::vector<T> data;
	TextFile() : isWriteMode(false) {}
	TextFile(std::string path, bool isWriteMode);
	void setFilePath(std::string path) { filePath = path; }
	void saveToFile();
	double sumColumn(size_t index);
	void sortByColumn(size_t index, bool asc = true);
};

template <class T>
TextFile<T>::TextFile(std::string path, bool isWriteMode) : filePath(path), isWriteMode(isWriteMode) {
	if (isWriteMode == false) {
		std::ifstream ifs(path);
		if (ifs.is_open()) {
		    std::string line;
			while (std::getline(ifs, line)) {
				if (!line.empty()) {
					T temp(line);
					data.push_back(temp);
				}
			}
		}
	}
}

template <class T>
void TextFile<T>::saveToFile() {
	std::ofstream ofs(filePath);
	for (auto& v : data) {
		for (auto& s : v.columns) {
			ofs << s << '\t';
		}
		ofs << std::endl;
	}
}

template <class T>
double TextFile<T>::sumColumn(size_t index) {
	double total_sum = 0.0;
	for (auto& v : data) {
		if (index < v.columns.size()) {
			try {
				double temp = std::stod(v.columns[index]);
				total_sum += temp;
			}
			catch (...) {}
		}
		else continue;
	}
	return total_sum;
}

template <class T>
void TextFile<T>::sortByColumn(size_t index, bool asc) {
    if (data.empty()) return;
    for (size_t i = 0; i < data.size() - 1; ++i) {
        for (size_t j = i + 1; j < data.size(); ++j) {
            if (index < data[i].columns.size() && index < data[j].columns.size()) {
                if (asc && data[i].columns[index] > data[j].columns[index]) {
                    std::swap(data[i], data[j]);
                }
                else if (!asc && data[i].columns[index] < data[j].columns[index]) {
                    std::swap(data[i], data[j]);
                }
            }
        }
    }
}