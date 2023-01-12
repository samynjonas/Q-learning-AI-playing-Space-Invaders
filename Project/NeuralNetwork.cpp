#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(int inputAmount, int hiddenLayers, int hiddenAmount, int outputamount)
	: m_Screen{ GameStruct::Box{GAME_ENGINE->GetGameWidth(), 0, GAME_ENGINE->GetWidth() - GAME_ENGINE->GetGameWidth(), 500}}
{
	m_VecLayers.push_back(new Layer(RGB( 0,		255,	0	))); //Input

	for (size_t i = 0; i < hiddenLayers; i++)
	{
		m_VecLayers.push_back(new Layer(RGB( 255,	0,		0	))); //Hidden
	}

	m_VecLayers.push_back(new Layer(RGB( 0,		255,	255	))); //Ouput

	for (size_t i = 0; i < inputAmount; i++)
	{
		m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	}

	for (size_t i = 0; i < hiddenLayers; i++)
	{
		for (size_t j = 0; j < hiddenAmount; j++)
		{
			m_VecLayers[static_cast<UINT>(LayerType::Hidden) + i]->AddNeuron();
		}
	}

	for (size_t i = 0; i < outputamount; i++)
	{
		m_VecLayers.back()->AddNeuron();
	}

	//Form connections
	for (size_t index = 0; index < m_VecLayers.size() - 1; index++)
	{
		m_VecConnections.push_back(new Connection(m_VecLayers[index], m_VecLayers[index + 1]));
	}
}

NeuralNetwork::~NeuralNetwork()
{

}

void NeuralNetwork::Update()
{
	int layerDistance{ m_Screen.Width / (static_cast<int>(m_VecLayers.size()) + 1)};
	for (int index = 0; index < m_VecLayers.size(); index++)
	{
		m_VecLayers[index]->Update(layerDistance * (index + 1), m_Screen);
	}


	for (auto* connections : m_VecConnections)
	{
		connections->Update();
	}
}

void NeuralNetwork::Render() const
{
	GAME_ENGINE->SetColor(RGB(50, 50, 50));
	GAME_ENGINE->FillRect(m_Screen.X, m_Screen.Y, m_Screen.Width, m_Screen.Height);

	for (const auto* connections : m_VecConnections)
	{
		connections->Render();
	}

	for (const auto* layer : m_VecLayers)
	{
		layer->Render();
	}
}

NeuralNetwork NeuralNetwork::MergeAndMutate(NeuralNetwork other)
{
	NeuralNetwork mergedAndMutated(17, 2, 4, 3);

	for (int connectionIndex{}; connectionIndex < mergedAndMutated.m_VecConnections.size(); ++connectionIndex)
	{
		for (int weightIndex{}; weightIndex < mergedAndMutated.m_VecConnections[connectionIndex]->m_VecWeights.size(); ++weightIndex)
		{
			int random{ rand() % 10};

			if (random <= 4)
			{
				mergedAndMutated.m_VecConnections[connectionIndex]->m_VecWeights[weightIndex]->value = m_VecConnections[connectionIndex]->m_VecWeights[weightIndex]->value;
			}
			else if(random <= 8)
			{
				mergedAndMutated.m_VecConnections[connectionIndex]->m_VecWeights[weightIndex]->value = other.m_VecConnections[connectionIndex]->m_VecWeights[weightIndex]->value;
			}
			else
			{
				mergedAndMutated.m_VecConnections[connectionIndex]->m_VecWeights[weightIndex]->value = static_cast<float>(rand() % 200 - 100) / 100;
			}
		}
	}

	return mergedAndMutated;
}

void NeuralNetwork::BellManEquation(int currentScore)
{
	const float learningRate = 0.1f;
	const float reward{ static_cast<float>(currentScore) };
	const float discountRate = 0.9f;
	const float maxQ{ 1.f };
	
	for (auto& connection : m_VecConnections)
	{
		for (auto& weight : connection->m_VecWeights)
		{
			float newWeight;
			float currentWeight;

			newWeight = weight->value + learningRate * (reward + discountRate * maxQ - weight->value);
			weight->value = newWeight;
		}
	}



}