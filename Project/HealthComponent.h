#pragma once
class HealthComponent final
{
public:
	HealthComponent(float maxHealth = 1.f);
	~HealthComponent();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	HealthComponent(const HealthComponent& other) {}
	HealthComponent(HealthComponent&& other) noexcept {}
	HealthComponent& operator=(const HealthComponent& other) {}
	HealthComponent& operator=(HealthComponent&& other)	noexcept {}

	bool Damage(float amount);
	float GetHealth() const;

private:
	float m_MaxHealth;
	float m_CurrentHealth;


};

