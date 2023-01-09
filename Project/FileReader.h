#pragma once
#include <string>


class FileReader final
{
public:
	FileReader(std::string filePath);
	~FileReader();

	FileReader(const FileReader& other) = delete;
	FileReader& operator=(const FileReader& other) = delete;
	FileReader(FileReader&& other) = delete;
	FileReader& operator=(FileReader&& other) = delete;


private:




};

