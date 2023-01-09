#pragma once
#include "GameStruct.h"
#include "GameEngine.h"

#include <random>
#include <vector>

struct Neuron
{
	GameStruct::point position{ 0, 0 };

	GameStruct::point center()
	{
		return GameStruct::point{ position.X + radius / 2, position.Y + radius / 2 };
	}

	COLORREF color{ RGB(255, 0, 0) };
	int radius{ 35 };
	
	float value{ 0 };
};

struct Layer
{
	Layer(COLORREF color)
		: color{ color }
	{

	}
	COLORREF color{ RGB(255, 0, 0) };

	std::vector<Neuron*> vecNeurons;

	void AddNeuron()
	{
		vecNeurons.push_back(new Neuron());
	}
	void Update(int layerX, GameStruct::Box screen)
	{
		int yDistance{ screen.Height / (static_cast<int>(vecNeurons.size()) + 1) };
		for (int index = 0; index < vecNeurons.size(); index++)
		{
			int halfRadius{ (vecNeurons[index]->radius / 2) };

			int x{ layerX + screen.X - halfRadius };
			int y{ (yDistance * (index + 1)) + screen.Y - halfRadius };

			vecNeurons[index]->position.X = x;
			vecNeurons[index]->position.Y = y;
		}
	}

	void Render() const
	{
		for (int index = 0; index < vecNeurons.size(); index++)
		{
			GAME_ENGINE->SetColor(color);
			GAME_ENGINE->FillOval(vecNeurons[index]->position.X, vecNeurons[index]->position.Y, vecNeurons[index]->radius, vecNeurons[index]->radius);

			GAME_ENGINE->SetColor(RGB(0, 0, 0));


			int valueINT{ static_cast<int>(vecNeurons[index]->value * 100.f) };

			wstring buffer = std::to_wstring(valueINT);

			GAME_ENGINE->DrawString(buffer, vecNeurons[index]->position.X + 5, vecNeurons[index]->position.Y + 10 );
		}
	}
};

struct Weight
{
	Weight(Neuron* neuronOne, Neuron* neuronTwo)
		: neuronOne{ neuronOne }
		, neuronTwo{ neuronTwo }
	{

	}

	Neuron* neuronOne;
	Neuron* neuronTwo;

	void Render() const
	{
		if (value > 0)
		{
			GAME_ENGINE->SetColor(RGB(0, (255 * value), 0));
		}
		else
		{
			GAME_ENGINE->SetColor(RGB((255 * value), 0, 0));
		}


		GAME_ENGINE->DrawLine(neuronOne->center().X, neuronOne->center().Y, neuronTwo->center().X, neuronTwo->center().Y);
	}	

	float value{ static_cast<float>(rand() % 200 - 100) / 100 };
	int x{};
};

struct Connection
{
	Layer* layerOne;
	Layer* layerTwo;

	std::vector<Weight*> m_VecWeights;

	Connection(Layer* layerOne, Layer* layerTwo)
		: layerOne{ layerOne }
		, layerTwo{ layerTwo }
	{
		for (Neuron* neuronL1 : layerOne->vecNeurons)
		{
			for (Neuron* neuronL2 : layerTwo->vecNeurons)
			{
				m_VecWeights.push_back(new Weight(neuronL1, neuronL2));
			}
		}
	}


	void Update()
	{
		for (Neuron* neuronL2 : layerTwo->vecNeurons)
		{
			float newValue{};			
			for (const Neuron* neuronL1 : layerOne->vecNeurons)
			{
				for (const auto* weight : m_VecWeights)
				{
					if (weight->neuronOne == neuronL1 && weight->neuronTwo == neuronL2)
					{
						newValue += neuronL1->value * weight->value;
					}
				}
			}

			newValue = 1 / (1 + expl(newValue)); //Sigmoid function
			//newValue = tanh(newValue); //Activation function -- Hyperbolic tangent -- https://en.wikipedia.org/wiki/Activation_function
			neuronL2->value = newValue;

		}		
	}


	void Render() const
	{
		for (const auto* connection : m_VecWeights)
		{
			connection->Render();
		}
	}
};

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();

	void Update();
	void Render() const;

	NeuralNetwork MergeAndMutate(NeuralNetwork other);

	std::vector<Connection*> GetConnections() const
	{
		return m_VecConnections;
	}
	void SetConnections(std::vector<Connection*> vecConnections)
	{
		//taking over neuralNetwork
		for (int connectionIndex{0}; connectionIndex < m_VecConnections.size(); connectionIndex++)
		{
			if (connectionIndex >= vecConnections.size())
			{
				break;
			}
			for (int weightIndex{ 0 }; weightIndex < m_VecConnections[connectionIndex]->m_VecWeights.size(); weightIndex++)
			{
				if (weightIndex >= vecConnections[connectionIndex]->m_VecWeights.size())
				{
					break;
				}

				m_VecConnections[connectionIndex]->m_VecWeights[weightIndex]->value = vecConnections[connectionIndex]->m_VecWeights[weightIndex]->value;
			}			
		}

	}

	Layer* GetInputLayer()
	{
		return m_VecLayers[static_cast<UINT>(LayerType::Input)];
	}

	Layer* GetOutputLayer() const
	{
		return m_VecLayers[static_cast<UINT>(LayerType::Output)];
	}


	enum class LayerType
	{
		Input = 0,
		Hidden = 1,
		Output = 2
	};
private:


	GameStruct::Box m_Screen;
	std::vector<Layer*> m_VecLayers;
	std::vector<Connection*> m_VecConnections;

};

