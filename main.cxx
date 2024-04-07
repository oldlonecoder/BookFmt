//
// Created by oldlonecoder on 24-04-03.
//
#include <AppBook/Book/ApplicationBase.h>
#include <BookFmt/BookFmt.h>



class Application : public Book::ApplicationBase
{

public:

    Application(const std::string &appName, int argc, char **argv) : ApplicationBase(appName, argc, argv)
    {}

protected:
    virtual Book::Result Setup() override;

public:
    Book::Result Run() override;


};

Book::Result Application::Run()
{
    Setup();
    StrAcc Txt;
    Book::Fmt::BookFmt BF;
    BF << R"( Testing  \{Colors:Yellow On Blue Icon:Success} Book\{Colors:White On Grey}::\{Fg:Grey100}Fmt\{Fg:Cyan}::\{Fg:BlueViolet}BookFmt\{Fg:White}...\{Colors:Red,White;}Termin&eacute; !!)" >> Txt;
    Book::Test() << "Test Result:" << Txt;
    return Book::Result::Ok;
}

Book::Result Application::Setup()
{
    Book::Debug() << " here...";
    //...
    return ApplicationBase::Setup();

}



auto main(int argc, char** argv) -> int
{
    Application App = Application("BookFmt", argc,argv);
    App.Run();

}