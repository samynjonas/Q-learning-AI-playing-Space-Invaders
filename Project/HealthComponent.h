#pragma once
class HealthComponent final
{
public:
	HealthComponent(float maxHealth = 1.f);
	~HealthComponent();

	// -------------------------
	// Copy/move constructors and assignment operators
	// -------------------------    
	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) noexcept = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other)	noexcept = delete;

	bool Damage(float amount);
	float GetHealth() const;

private:
	float m_MaxHealth;
	float m_CurrentHealth;


};

