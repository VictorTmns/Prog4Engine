#pragma once
#include <functional>

namespace vic
{

    class BaseCommand
    {
    public:
        virtual ~BaseCommand();

        void Enable() {m_Enabled = true; }
        void Disable() { m_Enabled = false; }
        bool IsEnabled() const { return m_Enabled; }
    private:
        bool m_Enabled = true;
    };




    class ButtonCommand : public BaseCommand
    {
    public:
        ButtonCommand(std::function<void()> function);
        void Execute();
    private:
        std::function<void()> m_Command;
    };


	class VectorCommand : public BaseCommand
    {
    public:
        VectorCommand(std::function<void(float deltaX, float deltaY)> function);
        void Execute(float x, float y);

    private:
        std::function<void(float deltaX, float deltaY)> m_Command;
    };


	class ScalarCommand : public BaseCommand
    {
    public:
        ScalarCommand(std::function<void(float x)> function);
        void Execute(float x);

    private:
        std::function<void(float value)> m_Command;
    };

}