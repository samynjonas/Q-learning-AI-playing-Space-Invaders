#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork()
	: m_Screen{ GameStruct::Box{GAME_ENGINE->GetGameWidth(), 0, GAME_ENGINE->GetWidth() - GAME_ENGINE->GetGameWidth(), 500}}
{
	m_VecLayers.push_back(new Layer(RGB( 0,		255,	0	))); //Input
	m_VecLayers.push_back(new Layer(RGB( 255,	0,		0	))); //Hidden
	m_VecLayers.push_back(new Layer(RGB( 0,		255,	255	))); //Ouput

	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Input)]->AddNeuron();


	m_VecLayers[static_cast<UINT>(LayerType::Hidden)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Hidden)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Hidden)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Hidden)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Hidden)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Hidden)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Hidden)]->AddNeuron();
	m_VecLayers[static_cast<UINT>(LayerType::Hidden)]->AddNeuron();


	
	m_VecLayers[static_cast<UINT>(LayerType::Output)]->AddNeuron(); //Go left
	m_VecLayers[static_cast<UINT>(LayerType::Output)]->AddNeuron();	//Go Right
	m_VecLayers[static_cast<UINT>(LayerType::Output)]->AddNeuron();	//Shoot


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
	NeuralNetwork mergedAndMutated;

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