#include "HealthComponent.h"

HealthComponent::HealthComponent(float maxHealth)
	: m_MaxHealth{ maxHealth }
	, m_CurrentHealth{ maxHealth }
{

}

HealthComponent::~HealthComponent()
{

}

bool HealthComponent::Damage(float amount)
{
	if (m_CurrentHealth > 0 && m_CurrentHealth <= m_MaxHealth)
	{
		m_CurrentHealth -= amount;

		if (m_CurrentHealth < 0)
		{
			m_CurrentHealth = 0;
			return true;
		}

		if (m_CurrentHealth > m_MaxHealth)
		{
			m_CurrentHealth = m_MaxHealth;
			return true;
		}
	}

	return true;
}

float HealthComponent::GetHealth() const
{
	return m_CurrentHealth;
}