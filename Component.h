#pragma once

// clasa abstracta din care vor fi derivate componentele

class Component
{
public:
	virtual ~Component() = default;
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
};
