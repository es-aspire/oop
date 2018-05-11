#pragma once

#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include "Drawable.h"
#include "IShape.h"
#include "CCanvas.h"

class CShapeController
{
public:
	CShapeController(std::istream& input, std::ostream& output, CCanvas& canvas);
	bool HandleCommand();
	void PrintShapeWithMinPerimeter();
	void PrintShapeWithMaxArea();
	void Draw();

private:
	void AddLineSegment(std::istream& args);
	void AddRectangle(std::istream& args);
	void AddTriangle(std::istream& args);
	void AddCircle(std::istream& args);

	void PollEvent(sf::Event& event);
	void DrawPicture();
	void DrawShapes();

private:
	using ActionMap = std::map<std::string, std::function<void(std::istream& args)>>;
	using Picture = std::vector<std::shared_ptr<IShape>>;

	Picture m_picture;

	std::istream& m_input;
	std::ostream& m_output;
	CCanvas& m_canvas;
	sf::RenderWindow m_window;
	ActionMap m_actionMap;
};
