#pragma once
#include <string>

#include "NeuralNetwork.h"

class FileReader final
{
public:
	FileReader(std::string filePath);
	~FileReader();

	FileReader(const FileReader& other) = delete;
	FileReader& operator=(const FileReader& other) = delete;
	FileReader(FileReader&& other) = delete;
	FileReader& operator=(FileReader&& other) = delete;


	NeuralNetwork GetNeuralNetworkOfEpisode(int number);

	
private:
	std::string m_FilePath;

	std::string GetAttributeValue(const std::string& attrName, const std::string& element) const;
	int attributeLastIndex(const std::string& attrName, const std::string& element) const;

	void createConnections(const std::string& connectionElement, int connectionIndex, Connection* connection);


	NeuralNetwork& createInformation(const std::string& element, NeuralNetwork& neuralNetwork);
};

