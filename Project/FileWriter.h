#pragma once
#include <string>
#include <vector>

#include "NeuralNetwork.h"

class FileWriter final
{
public:
	FileWriter(std::string filepath);
	~FileWriter();

	FileWriter(const FileWriter& other) = delete;
	FileWriter& operator=(const FileWriter& other) = delete;
	FileWriter(FileWriter&& other) = delete;
	FileWriter& operator=(FileWriter&& other) = delete;

	void Write(int episodeNum, std::vector<Connection*> m_VecConnections, int highscore);

private:
	const std::string FILEPATH;


	std::string its(int intValue) const; // int to string conversion
	std::string fts(float floatValue) const; // float to string conversion



};

