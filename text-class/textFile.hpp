#pragma once
#include"formatRowFile.hpp"
#include<string>
#include<fstream>

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