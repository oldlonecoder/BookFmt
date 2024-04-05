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

Book::Result Fmt::BookFmt::Process()
{

    return Result::Ok;
}

std::string Fmt::BookFmt::RenderAttribute(const Fmt::FmtAttribute &A)
{
    if(!RenderAttributeDelegate.Empty())
    {
        RenderAttribute(A);
        return {};
    }
    StrAcc Buffer;
    if(A.Assigned.Ac)
    {
        Buffer << A.Ac;
        return Buffer();
    }
    if(A.Assigned.Fg) Buffer << A.Colors.Fg;
    if(A.Assigned.Bg) Buffer << A.Colors.Bg;
    if(A.Assigned.Ic) Buffer << A.Ic;
    // ... More to come
    return Buffer();
}

Fmt::BookFmt &Fmt::BookFmt::operator<<(const std::string &Input)
{
    mCFG = {
        .Source = Input,
        .TokensTable = & mTokens,
        .Product     = & mAttributes
    };
    (void)Compile();
    return *this;
}

/*!
 * @brief Renders this BookFmt into the \c Output.
 * @param Output
 * @return
 */
Book::Result Fmt::BookFmt::operator>>(StrAcc &Output)
{
    if(mAttributes.empty())
    {
        Output << mText.data();
        return Book::Result::Ok;
    }

    auto Source = mText.begin();
    auto Begin  = Source;
    auto End = mText.end();
    size_t Offset = 0;

    for(auto const& A: mAttributes)
    {
        auto StartAttrIt = *A.TokenComponents.begin();
        auto EndAttrIt  = A.TokenComponents.back();
        Book::Debug() << " This Attribute Surrounding Tokens:" << Book::Fn::Endl << StartAttrIt->Details() << Book::Fn::Endl << EndAttrIt->Details();

        while(Offset < StartAttrIt->Loc.Offset)
        {
            Output += *Source++;
            ++Offset;
        }
        Output << RenderAttribute(A);
        Source += EndAttrIt->Loc.Offset - StartAttrIt->Loc.Offset;
    }
    return Result::Failed;
}

} // Book
