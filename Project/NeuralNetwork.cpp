#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork()
	: m_Screen{ GameStruct::Box{0, 250, 250, 250} }
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

	GAME_ENGINE->SetColor(RGB(100, 100, 100));
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