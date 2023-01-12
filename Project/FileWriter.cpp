#include "FileWriter.h"
#include <iostream>
#include <fstream>
#include <sstream>

FileWriter::FileWriter(std::string filepath)
	: FILEPATH{ filepath }
{

}

FileWriter::~FileWriter()
{

}

void FileWriter::Write(int episodeNum, std::vector<Connection*> m_VecConnections, int highscore)
{
	std::ofstream output{ FILEPATH + "\\Episode_" + its(episodeNum) + ".txt" };
	//std::ofstream output{ FILEPATH + ".txt" };

	//Episode
	output << "<NeuralNetwork" << std::endl;

	output << "\tepisode=\"" << its(episodeNum) << "\"" << std::endl;
	output << "\tscore=\"" << its(highscore) << "\"" << std::endl;
	
	output << "/>" << std::endl << std::endl;

	//Weigth
	for (int index{}; index < m_VecConnections.size(); index++)
	{
		output << "<";
		output << "Connection=\"" << its(index) << "\"" << std::endl;
		for (int weightIndex{}; weightIndex < m_VecConnections[index]->m_VecWeights.size(); weightIndex++)
		{
			output << "\tw=\"" << its(weightIndex) << "=\"" << fts(m_VecConnections[index]->m_VecWeights[weightIndex]->value) << "\"" << std::endl;
		}
		output << "/>" << std::endl << std::endl;

	}
	output.close();
}

std::string FileWriter::its(int intValue) const
{
	return std::to_string(intValue);
}

std::string FileWriter::fts(float floatValue) const
{
	return std::to_string(floatValue);
}
