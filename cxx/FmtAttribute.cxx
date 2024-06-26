//
// Created by oldlonecoder on 24-04-02.
//

#include "BookFmt/FmtAttribute.h"

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
FmtAttribute &Fmt::FmtAttribute::operator=(Utf::Glyph::Type Graphen)
{
    Assigned.Ic = 1;
    Ic = Graphen;
    return *this;
}

Fmt::FmtAttribute &Fmt::FmtAttribute::operator=(Utf::AccentFR::Type A)
{
    Assigned.Ac = 1;
    Ac = A;
    return *this;
}

Fmt::FmtAttribute &Fmt::FmtAttribute::operator=(Color::Pair Pair)
{
    Colors = Pair;
    Assigned.Fg = Assigned.Bg = 1;
    return *this;
}

Fmt::FmtAttribute &Fmt::FmtAttribute::SetFG(Color::Code C)
{
    Assigned.Fg = 1;
    Colors.Fg = C;
    return *this;
}

Fmt::FmtAttribute &Fmt::FmtAttribute::SetBG(Color::Code C)
{
    Assigned.Bg = 1;
    Colors.Bg = C;
    return *this;
}

void FmtAttribute::DebugDumpDetails()
{
    StrAcc Acc;
    Book::Out() << "FmtAttribute Details:";
    Book::Out() << "-----------------------------------------------------------------";
    Book::Out() << "Tokens Components:";
    for(auto Token: TokenComponents) Book::Out() << Token->Details();
    Book::Out() << "-----------------------------------------------------------------";
    Book::Out() << "Assigned components:";
    if(Assigned.Fg || Assigned.Bg) Book::Out() << Colors << Color::Name(Colors.Fg) << Color::Reset<< " On " << Colors << Color::Name(Colors.Bg) << Color::Reset;
    if(Assigned.Ic) Book::Out() << "Icon       Enum :" << Ic;
    if(Assigned.Ac) Book::Out() << "Accent     Enum :" << Ac;
    Book::Out() << "Length:" << Length;
    Book::Out() << "More to come...";
    //...
}


} // Book
