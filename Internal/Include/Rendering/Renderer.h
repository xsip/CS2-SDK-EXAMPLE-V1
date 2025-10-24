#pragma once
#include <vector>
#include <Rendering/RenderObject.h>
struct ImVec2;
class Renderer {
private:
	std::vector<RenderObject*> renderObjects;
public:
	Renderer(std::vector<RenderObject*> _renderObjects) {
		renderObjects = _renderObjects;
	}
	void AddRenderObject(RenderObject* obj) {
		renderObjects.push_back(obj);
	}
private:
	static void RenderWatermark(ImVec2 displaySize);
public:
	void Render(ImVec2 displaySize);
};