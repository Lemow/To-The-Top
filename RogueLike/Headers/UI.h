#pragma once
#include "Sprite.h"
#include "Transform.h"

enum class AnchorPoint
{
	LU, CU, RU,
	LC, CC, RC,
	LD, CD, RD
};

struct UI
{
	UI* parent;
	Transform transform;
	AnchorPoint anchor;
	uint32_t spriteID;
	UI(uint32_t spriteID, const Transform& transform)
		:parent(nullptr),
		transform(transform),
		anchor(AnchorPoint::CC),
		spriteID(spriteID)
	{}

	UI(uint32_t spriteID, const Transform& transform, UI* parent, AnchorPoint anchor)
		:parent(parent),
		transform(transform),
		anchor(anchor),
		spriteID(spriteID)
	{}

	UI(uint32_t spriteID, const Transform& transform, AnchorPoint anchor)
		:parent(nullptr),
		transform(transform),
		anchor(anchor),
		spriteID(spriteID)
	{}

	virtual uint32_t GetSpriteID() const 
	{
		return spriteID;
	}

	virtual void OnClick(void* data) const
	{
	}

	bool isHovering(uint32_t mouseX, uint32_t mouseY) const
	{
		return abs(transform.pos.x - mouseX) <= transform.size.x && 
			   abs(transform.pos.y - mouseY) <= transform.size.y;
	}

};


struct Button : public UI
{
	Button() = default;
	Button(uint32_t textureID,
		const Transform& transform,
		uint32_t highlightSpriteID,
		uint32_t pressedSpriteID,
		void* (*buttonFunc)(void*))

		:UI(textureID,transform),
		highlightSpriteID(highlightSpriteID),
		buttonFunc(buttonFunc),
		pressedSpriteID(pressedSpriteID),
		isHighlighted(false),
		isPressed(false)
	{
	}

	Button(uint32_t textureID,
		const Transform& transform,
		UI* parent,
		AnchorPoint anchor,
		uint32_t highlightSpriteID,
		uint32_t pressedSpriteID,
		void* (*buttonFunc)(void*))

		:UI(textureID, transform, parent, anchor),
		highlightSpriteID(highlightSpriteID),
		buttonFunc(buttonFunc),
		pressedSpriteID(pressedSpriteID),
		isHighlighted(false),
		isPressed(false)
	{
	}

	Button(uint32_t textureID,
		const Transform& transform,
		AnchorPoint anchor,
		uint32_t highlightSpriteID,
		uint32_t pressedSpriteID,
		void* (*buttonFunc)(void*))

		:UI(textureID, transform, anchor),
		highlightSpriteID(highlightSpriteID),
		buttonFunc(buttonFunc),
		pressedSpriteID(pressedSpriteID),
		isHighlighted(false),
		isPressed(false)
	{
	}

	uint32_t GetSpriteID() const override
	{
		return (!isPressed) * (isHighlighted * highlightSpriteID + (!isHighlighted) * spriteID) + isPressed * pressedSpriteID;
	}

	void OnClick(void* data) const override
	{
		if(isHighlighted)
			buttonFunc(data);
	}


	uint32_t highlightSpriteID;
	void* (*buttonFunc)(void*);
	uint32_t pressedSpriteID;
	bool isHighlighted;
	bool isPressed;
};



