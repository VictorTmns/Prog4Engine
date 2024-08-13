#include "Commands.h"

#include <utility>

#include "InputManager.h"


// ----- BASECOMMAND -----
inline vic::BaseCommand::~BaseCommand()
{
	InputManager::GetInstance().RemoveCommand(this);
}



// ----- BUTTONCOMMAND -----
vic::ButtonCommand::ButtonCommand(std::function<void()> function)
	:m_Command{std::move(function)}
{}

void vic::ButtonCommand::Execute()
{
	if(IsEnabled())
		m_Command();
}




// ----- VECTORCOMMAND -----
vic::VectorCommand::VectorCommand(std::function<void( float deltaX, float deltaY)> function)
	:m_Command{std::move(function)}
{}

void vic::VectorCommand::Execute(float x, float y)
{
	if(IsEnabled())
		m_Command(x, y);
}




// ----- SCALARCOMMAND -----
vic::ScalarCommand::ScalarCommand(std::function<void( float x)> function)
	:m_Command{std::move(function)}
{}

void vic::ScalarCommand::Execute(float x)
{
	if(IsEnabled())
		m_Command(x);
}
