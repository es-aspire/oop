#include "stdafx.h"
#include "ShapeController.h"
#include "Circle.h"
#include "ColorRGBA.h"
#include "LineSegment.h"
#include "Point.h"
#include "Rectangle.h"
#include "Triangle.h"

namespace
{
bool StringToUInt(const std::string& str, unsigned int& value)
{
	try
	{
		value = static_cast<unsigned int>(stoi(str));

		return true;
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << std::endl;
	}

	return false;
}

bool StringToInt(const std::string& str, int& value)
{
	try
	{
		value = static_cast<unsigned int>(stoi(str));
		return true;
	}
	catch (const std::exception& err)
	{
		std::cerr << err.what() << std::endl;
	}
	return false;
}
} // namespace

static const sf::Vector2u RESOLUTION = { 800, 600 };
static const std::string PROGRAM_TITLE = "Geometric Shape";

CShapeController::CShapeController(std::istream& input, std::ostream& output, CCanvas& canvas)
	: m_input(input)
	, m_output(output)
	, m_canvas(canvas)
	, m_window(sf::VideoMode(RESOLUTION.x, RESOLUTION.y), PROGRAM_TITLE)
	, m_actionMap({ 
		{ "LineSegment", std::bind(&CShapeController::AddLineSegment, this, std::placeholders::_1) },
		{ "Rectangle", std::bind(&CShapeController::AddRectangle, this, std::placeholders::_1) },
		{ "Triangle", std::bind(&CShapeController::AddTriangle, this, std::placeholders::_1) },
		{ "Circle", std::bind(&CShapeController::AddCircle, this, std::placeholders::_1) },
		})
{
};

bool CShapeController::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	std::string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		it->second(strm);
		return true;
	}

	return false;
}

void CShapeController::PrintShapeWithMinPerimeter()
{
	if (m_picture.empty())
	{
		m_output << "no figures\n";
	}
	else
	{
		auto it = *std::min_element(m_picture.begin(), m_picture.end(), [](const std::shared_ptr<IShape>& shapeFirst, const std::shared_ptr<IShape>& shapeSecond) {
			return shapeFirst->GetPerimeter() < shapeSecond->GetPerimeter();
		});

		m_output << it->ToString();
	}
}

void CShapeController::PrintShapeWithMaxArea()
{
	if (m_picture.empty())
	{
		m_output << "no figures\n";
	}
	else
	{
		auto it = *std::max_element(m_picture.begin(), m_picture.end(), [](const std::shared_ptr<IShape>& shapeFirst, const std::shared_ptr<IShape>& shapeSecond) {
			return shapeFirst->GetArea() < shapeSecond->GetArea();
		});

		m_output << it->ToString();
	}
}

void CShapeController::Draw()
{
	if (m_picture.empty())
	{
		m_output << "no figures for draw\n";
	}

	while (m_window.isOpen())
	{
		sf::Event event;

		PollEvent(event);
		DrawPicture();
	}

}

void CShapeController::AddLineSegment(std::istream& args)
{
	CPoint from;
	CPoint to;
	ColorRGBA outlineColor;

	if (!(args >> from))
	{
		m_output << "failed read from point\n";
	}
	else if (!(args >> to))
	{
		m_output << "failed read to point\n";
	}
	else if (!(args >> outlineColor))
	{
		m_output << "failed read outlineColor\n";
	}

	std::shared_ptr<CLineSegment> sharedPtr(new CLineSegment(from, to, outlineColor));
	m_picture.push_back(std::move(sharedPtr));
}

void CShapeController::AddRectangle(std::istream& args)
{
	CPoint leftTopVertex;
	double width = 0.0;
	double height = 0.0;
	ColorRGBA outlineColor;
	ColorRGBA fillColor;

	if (!(args >> leftTopVertex))
	{
		m_output << "failed read left top vertex\n";
	}
	else if (!(args >> width))
	{
		m_output << "failed read width\n";
	}
	else if (!(args >> height))
	{
		m_output << "failed read height\n";
	}
	else if (!(args >> outlineColor))
	{
		m_output << "failed read outlineColor\n";
	}
	else if (!(args >> fillColor))
	{
		m_output << "failed read fillColor\n";
	}

	std::shared_ptr<CRectangle> sharedPtr(new CRectangle(leftTopVertex, width, height, outlineColor, fillColor));
	m_picture.push_back(std::move(sharedPtr));
}

void CShapeController::AddTriangle(std::istream& args)
{
	CPoint firstVertex;
	CPoint secondVertex;
	CPoint thirdVertex;
	ColorRGBA outlineColor;
	ColorRGBA fillColor;

	if (!(args >> firstVertex))
	{
		m_output << "failed read first vertex\n";
	}
	else if (!(args >> secondVertex))
	{
		m_output << "failed read second vertex\n";
	}
	else if (!(args >> thirdVertex))
	{
		m_output << "failed read third vertex\n";
	}
	else if (!(args >> outlineColor))
	{
		m_output << "failed read outlineColor\n";
	}
	else if (!(args >> fillColor))
	{
		m_output << "failed read fillColor\n";
	}

	std::shared_ptr<CTriangle> sharedPtr(new CTriangle(firstVertex, secondVertex, thirdVertex, outlineColor, fillColor));
	m_picture.push_back(std::move(sharedPtr));
}

void CShapeController::AddCircle(std::istream& args)
{
	CPoint centerPoint;
	double radius = 0;
	ColorRGBA outlineColor;
	ColorRGBA fillColor;

	if (!(args >> centerPoint))
	{
		m_output << "failed read center\n";
	}
	else if (!(args >> radius))
	{
		m_output << "failed read radius\n";
	}
	else if (!(args >> outlineColor))
	{
		m_output << "failed read outlineColor\n";
	}
	else if (!(args >> fillColor))
	{
		m_output << "failed read fillColor\n";
	}

	std::shared_ptr<CCircle> sharedPtr(new CCircle(centerPoint, radius, outlineColor, fillColor));
	m_picture.push_back(std::move(sharedPtr));
}

void CShapeController::PollEvent(sf::Event& event)
{
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
		{
			m_window.close();
		}
	}
}

void CShapeController::DrawPicture()
{
	m_window.clear();
	DrawShapes();
	m_window.display();
}

void CShapeController::DrawShapes()
{
	for (auto shape : m_picture)
	{
		shape->Draw(m_window, m_canvas);
	}
}
