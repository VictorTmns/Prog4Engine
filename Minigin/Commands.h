#pragma once
#include <functional>

namespace minigin
{

    class BaseCommand
    {
    public:
        virtual ~BaseCommand();
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
    // REVIEW
    //template<typename T>
    //class Command {
    //public:
    //    Command(std::function<void(BaseComponent* actor, T... args)> function, BaseComponent* actor)
    //	: m_Command([=](T... args) { function(actor, args...); })
    //	{}
    //
    //    void Execute(T... args) {
    //        m_Command(args...);
    //    }
    //
    //private:
    //    std::function<void(T...)> m_Command;
    //};
}