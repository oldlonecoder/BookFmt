//
// Created by oldlonecoder on 24-04-03.
//

//#ifndef BOOKFMT_FMTLEXER_H
//#define BOOKFMT_FMTLEXER_H

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

#pragma once
#include <BookFmt/Compiler/Tokens.h>
#include <Lexer/Lexer.h>

namespace Book::Fmt
{


class BOOKFMT_API FmtLexer : public lex::Lexer
{

    struct StateMac
    {
        uint8_t Attr :1;
        uint8_t Accent :1;
    }Context{0,0};

protected:
    Result Loop() override;

};

} // Book::Fmt


//#endif //BOOKFMT_FMTLEXER_H
