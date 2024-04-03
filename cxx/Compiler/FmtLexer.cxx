//
// Created by oldlonecoder on 24-04-03.
//

#include "BookFmt/Compiler/FmtLexer.h"

/******************************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                                        *
 *   serge.lussier@oldlonecoder.club                                                      *
 *                                                                                        *
 *                                                                                        *
 *   Unless otherwise specified, all Code IsIn this project is written                    *
 *   by the author (Serge Lussier)                                                        *
 *   and no one else then not even {copilot, chatgpt, or any other AI calamities}         *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply To the Code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 ******************************************************************************************/

//#pragma once




namespace Book::Fmt
{



Result FmtLexer::Loop()
{
    Book::Debug() << "Before entering the loop: ";
    Book::Out() << " Scanner position set at (col:" << Scanner()-Scanner.Begin() << "):{" << Scanner.Mark() << Book::Fn::Endl << "}";
    Book::Test() << " Now Entering in the loop:";
    //return Book::Result::Ok;
    auto Cursor = Scanner(); // Save current position.
    lex::TokenInfo Token{};
    while(!Scanner.Eof() && (State != Book::Result::Eof))
    {
        Book::Debug() << " FmtLexer::Loop: " << Scanner.Mark();

        if((Context.Attr || Context.Accent) ) // Returned Eof!! WTF?
        {
            if(!Tokenize(mConfig.Production->Scan(Scanner())))
            {
                if (Scanner.Eof() || (State == Book::Result::Eof)) return Book::Result::Accepted;
                AppBook::Status() << " Lexer Rejected Token at: " << Book::Fn::Endl << Scanner.Mark();
                return Book::Result::Rejected;
            }
            Token = mConfig.Production->Production().back();
            if((Token.M == lex::Mnemonic::EndFmt) || ((Token.M == lex::Mnemonic::Semicolon) && Context.Accent))
            {
                Context = {0,0};
                Book::Debug() << "Exit lexing context...";
                Cursor = Scanner();
                continue;
            }

        }
        else
        {
            //if(Scanner.Eof()) return Result::Accepted;

            Book::Debug() << " Global context: Check:";
            Token = mConfig.Production->Scan(Scanner());
            if(Token.M == lex::Mnemonic::BeginFmt)
            {
                Book::Debug() << " Entering into Attribute context:";
                Context = {1, 0};
                Tokenize(Token);
            }
            else {
                if (Token.M == lex::Mnemonic::Accent) {
                    Book::Debug() << "Entering into Accent context:";
                    Tokenize(Token);
                    Context = {0, 1};
                }
                else {
                    ++Scanner;
                    continue;
                }
            }
        }

        if(Cursor == Scanner())
        {
            AppBook::Error() << " loop: No Scanning (unhandled yet or bug ;) )" << Book::Fn::Endl << Scanner.Mark();
            return Book::Result::Rejected;
        }
        if(Token && ((Token.M == lex::Mnemonic::EndFmt) || ((Token.M == lex::Mnemonic::Semicolon) && Context.Accent)))
        {
            Context = {0,0};
            Book::Debug() << "Exit lexing context...";
        }

        Cursor = Scanner();
    }

    return Book::Result::Accepted;
}



} // Book::Fmt
