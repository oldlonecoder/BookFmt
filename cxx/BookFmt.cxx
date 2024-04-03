//
// Created by oldlonecoder on 24-04-02.
//

#include "BookFmt/BookFmt.h"

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


#include <BookFmt/Compiler/Tokens.h>

namespace Book
{
Fmt::BookFmt::BookFmt(std::string_view Txt):mText(Txt)
{

    mCFG = {
        .Source = Txt,
        .TokensTable = & mTokens,
        .Product     = & mAttributes
    };

}


Fmt::BookFmt::~BookFmt()
{
    mAttributes.clear();
}


Book::Result Fmt::BookFmt::Compile()
{
    FmtCompiler Comp;
    Comp.Config() = mCFG;
    if(!Comp.Compile()) return Book::Result::Failed;
    // mAttributes is built...
    return Result::Success;
}


} // Book
