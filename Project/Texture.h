#pragma once
#include <string>
#include "GameStruct.h"

class Texture final
{
public:
	explicit Texture(const std::string& imagePath);
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	Texture(Texture&& other) noexcept;
	Texture& operator=(Texture&& other) noexcept;
	~Texture();

	void Draw(const GameStruct::point& dstBottomLeft = { 0, 0 }, const GameStruct::Box& srcRect = { 0, 0, 0, 0 }) const;
	void Draw(const GameStruct::Box& dstRect, const GameStruct::Box& srcRect = { 0, 0, 0, 0 }) const;

	float GetWidth() const;
	float GetHeight() const;
	bool IsCreationOk() const;
	std::string getPath() const;

private:
	//DATA MEMBERS
	float m_Width;
	float m_Height;
	bool m_CreationOk;
	std::string m_Path;

	// FUNCTIONS
	void CreateFromImage(const std::string& path);
	void DrawFilledRect(const GameStruct::Box& dstRect) const;
};