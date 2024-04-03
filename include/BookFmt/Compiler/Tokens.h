//
// Created by oldlonecoder on 24-04-02.
//

//#ifndef BOOKFMT_TOKENS_H
//#define BOOKFMT_TOKENS_H

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


#include <Lexer/TokenTable.h>
#include <BookFmt/Interface.h>
namespace lex::Mnemonic
{
constexpr T BeginFmt    = 121;
constexpr T EndFmt      = 122;
constexpr T ForeGround  = 123;
constexpr T BackGround  = 124;
constexpr T Icon        = 125;
constexpr T Accent      = 126;
constexpr T AttrSeq     = 127;
constexpr T ColorPair   = 128;
constexpr T Reset       = 129;
constexpr T ArgSep      = 130;
constexpr T LineBreak   = 131;
constexpr T Left        = 132;
constexpr T Right       = 133;
constexpr T Top         = 134;
constexpr T Bottom      = 135;
constexpr T Center      = 136;
constexpr T HVCenter    = 137;
constexpr T Box         = 138;
constexpr T On          = 139;

}


namespace lex::Lexem
{
constexpr T BeginFmt = "\\{"; ///< Pourquoi pas faire comme LaTex ? lol
constexpr T EndFmt   = "}";
constexpr T ForeGround  = "Fg";
constexpr T BackGround  = "Bg";
constexpr T Icon        = "Icon";
constexpr T Accent      = "&";
constexpr T AttrSeq     = ":";
constexpr T ColorPair   = "Colors";
constexpr T Reset       = "/";
constexpr T ArgSep      = ",";
constexpr T LineBreak   = "Brk";
constexpr T JustifyLeft = "<";
constexpr T JustifyRight= ">";
constexpr T Top         = "^";
constexpr T Bottom      = "_";
constexpr T Center      = "-";
constexpr T HVCenter    = "+";
constexpr T Box         = "Box";
constexpr T On          = "On";
}


namespace Book::Fmt
{



class BOOKFMT_API Tokens : public lex::TokenTable
{
public:

    size_t DeclareTable() override;
};

} // Book::Fmt


