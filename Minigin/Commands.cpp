#include "Commands.h"

#include <utility>

#include "InputManager.h"


// ----- BASECOMMAND -----
inline minigin::BaseCommand::~BaseCommand()
{
	InputManager::GetInstance().RemoveCommand(this);
}



// ----- BUTTONCOMMAND -----
minigin::ButtonCommand::ButtonCommand(std::function<void()> function)
	:m_Command{std::move(function)}
{}

void minigin::ButtonCommand::Execute()
{
	m_Command();
}




// ----- VECTORCOMMAND -----
minigin::VectorCommand::VectorCommand(std::function<void( float deltaX, float deltaY)> function)
	:m_Command{std::move(function)}
{}

void minigin::VectorCommand::Execute(float x, float y)
{
	m_Command(x, y);
}




// ----- SCALARCOMMAND -----
minigin::ScalarCommand::ScalarCommand(std::function<void( float x)> function)
	:m_Command{std::move(function)}
{}

void minigin::ScalarCommand::Execute(float x)
{
	m_Command(x);
}
