//
// Created by oldlonecoder on 24-04-03.
//

#include "BookFmt/Compiler/FmtCompiler.h"
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


#include <Lexer/Lexer.h>


namespace Book::Fmt
{


Book::Result FmtCompiler::Compile()
{
    FmtLexer Lexer;
    mConfig.TokensTable->DeclareTable();
    mConfig.TokensTable->DebugDumpRef();

    Lexer.Config() = {
        .Text       = mConfig.Source,
        .Production = mConfig.TokensTable
    };

    if(!Lexer.Execute()) return Result::Failed;
    mConfig.TokensTable->DebugDumpProduct();

    Book::Debug() << "Test stops here... ";

    return Result::Ok;
}
} // Book::Fmt

