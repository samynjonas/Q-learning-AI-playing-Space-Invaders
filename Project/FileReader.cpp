#include "FileReader.h"

FileReader::FileReader(std::string mapPath)
	: m_FilePath{ mapPath }
{

}

FileReader::~FileReader()
{

}

NeuralNetwork FileReader::GetNeuralNetworkOfEpisode(int number)
{
	NeuralNetwork neuralNetwork(17, 2, 4, 3);

	std::ifstream input(m_FilePath + "\\Episode_" + to_string(number) + ".txt");
	std::string sentence{};

	bool foundSentence{ false };

	while (input.peek() != EOF)
	{
		std::string readText{}; //String that saves the data
		std::getline(input, readText);

		sentence += readText;
		for (size_t index = 0; index < sentence.size(); index++)
		{
			if (sentence[index] == '>')
			{
				foundSentence = true;
			}
		}

		if (foundSentence == true)
		{
			for (size_t index = 0; index < sentence.size(); index++)
			{
				if (sentence[index] == '<')
				{
					createInformation(sentence, neuralNetwork);

					sentence = "";
					foundSentence = false;
				}
			}
		}
	}

	return neuralNetwork;

}

NeuralNetwork& FileReader::createInformation(const std::string& element, NeuralNetwork& neuralNetwork)
{
	std::vector<Connection*> vecConnections = neuralNetwork.GetConnections();

	for (int index{}; index < neuralNetwork.GetConnections().size(); ++index)
	{
		if (element.find("Connection=" + to_string(index)) != std::string::npos)
		{
			createConnections(element, index, vecConnections[index]);
		}
	}

	return neuralNetwork;
}

void FileReader::createConnections(const std::string& connectionElement, int connectionIndex, Connection* connection)
{
	for (int index{}; index < connection->m_VecWeights.size(); ++index)
	{
		std::string attribute{ "w" + to_string(index) };
		connection->m_VecWeights[index]->value = stof(GetAttributeValue(attribute, connectionElement));
	}
}

std::string FileReader::GetAttributeValue(const std::string& attrName, const std::string& element) const
{
	std::string attribute{};
	bool startWord{ false };

	for (size_t index = attributeLastIndex(attrName, element); index < element.size(); index++)
	{
		if (index > 0)
		{
			string start{ element[index - 1] };
			string end{ element[index + 1] };

			if (element[index - 1] == '\"' && startWord == false)
			{
				startWord = true;
				attribute = "";
			}
			if (startWord == true)
			{
				attribute += element[index];
			}
			if (element[index + 1] == '\"' && startWord == true)
			{
				return attribute;
			}
		}
	}
	return attribute;
}
int FileReader::attributeLastIndex(const std::string& attrName, const std::string& element) const
{
	for (size_t index = 0; index < element.size(); index++)
	{
		if (index > 0)
		{
			if (element[index] == attrName[0])
			{
				//First letter
				if (element[index + 1] == attrName[1])
				{
					//Second letter
					return int(index);
				}
			}
		}
	}
	return 0;
}