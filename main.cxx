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
    Book::Fmt::BookFmt BF(" Testing  \\{Fg:Yellow} Book::Fmt::BookFmt...Termin&eacute; !!");
    (void)BF.Compile();
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