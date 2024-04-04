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


    mCursor = mConfig.TokensTable->Production().begin();
    while(mCursor != mConfig.TokensTable->Production().end())
    {
        if(!CompileFmt(mAttribute)) {
            if (!CompileAccent(mAttribute)) {
                if((mCursor->M != lex::Mnemonic::EndFmt) || ( (mCursor->M != lex::Mnemonic::Semicolon) && (!mAttribute.Assigned.Ac)))
                {
                    ++mCursor;
                    continue;
                }
            }
        }
        PushAttribute(mAttribute);
        mAttribute = FmtAttribute(); // Reset FmtAttribute contents ( new attribute ).
        ++mCursor;
    }
    //...

    Book::Debug() << "Test stops here... ";


    return Result::Ok;
}



/*!
 * @brief Begin Compiling FmtAttribute
 * @param A
 * @return
 */
Book::Result FmtCompiler::CompileFmt(FmtAttribute& A)
{
    //...
    if(mCursor->M != lex::Mnemonic::BeginFmt)
        return Result::Rejected;

    std::map<lex::Mnemonic::T,  Book::Result(FmtCompiler::*)(FmtAttribute&)> Keys =
    {
        {lex::Mnemonic::ForeGround, &FmtCompiler::CompileFgKeyword},
        {lex::Mnemonic::BackGround, &FmtCompiler::CompileBgKeyword},
        {lex::Mnemonic::ColorPair,  &FmtCompiler::CompileColorPairKeyword},
        {lex::Mnemonic::Icon,       &FmtCompiler::CompileIconKeyword},
        {lex::Mnemonic::Reset,      &FmtCompiler::CompileResetKeyword},
        //{lex::Mnemonic::LineBreak,  &FmtCompiler::CompileIconKeyword},
    };
    A << mCursor;
    while((mCursor != mConfig.TokensTable->Production().end()) && !Expect(lex::Mnemonic::EndFmt))
    {
        // Keywords:
        // {Fg Bg Colors Icon Brk /}
        auto Node = Keys.find(mCursor->M);
        if(Node == Keys.end())
        {
            if(mCursor->M == lex::Mnemonic::EndFmt)
            {
                ++mCursor;
                return Book::Result::Accepted;
            }
            if(mCursor->M==lex::Mnemonic::Semicolon)
            {
                ++mCursor;
                continue;
            }
            return Book::Result::Rejected;
        }

        if(!(this->*Node->second)(A))
            return Book::Result::Rejected;
    }

    return Result::Accepted;
}

Book::Result FmtCompiler::CompileAccent(FmtAttribute& A)
{

    //...
    if(mCursor->M != lex::Mnemonic::Accent)
        return Result::Rejected;

    A << mCursor;
    if(Expect(lex::Type::Id))
    {
        A << mCursor;
        auto [Ok,Acc] = Utf::AccentFR::ScanName(mCursor->Text().data());
        if(!Ok) return Result::Rejected;
        A.Assigned.Ac = 1;
        A.Ac = Acc;
    }
    return Result::Accepted;
}

bool FmtCompiler::Expect(lex::Mnemonic::T M)
{
    ++mCursor;
    if(mCursor->M != M)
    {
        --mCursor;
        return false;
    }
    return true;
}

bool FmtCompiler::Expect(lex::Type::T Type)
{
    ++mCursor;
    if(mCursor->Sem &  Type){
        --mCursor;
        return false;
    }
    return true;
}

Book::Result FmtCompiler::CompileFgKeyword(FmtAttribute &A)
{
    if(Expect(lex::Mnemonic::AttrSeq)) {
        A << mCursor;
        if (Expect(lex::Type::Id)) {
            A << mCursor;
            A.Assigned.Fg = 1;
            A.SetFG(Color::Scan(mCursor->Text().data()));
        }
        else return Result::Rejected;
    }
    return Result::Accepted;
}

Book::Result FmtCompiler::CompileBgKeyword(FmtAttribute &A)
{
    if(Expect(lex::Mnemonic::AttrSeq)) {
        A << mCursor;
        if (Expect(lex::Type::Id)) {
            A << mCursor;
            A.Assigned.Bg = 1;
            A.SetBG(Color::Scan(mCursor->Text().data()));
        }
        else return Result::Rejected;
    }
    return Result::Accepted;
}

Book::Result FmtCompiler::CompileColorPairKeyword(FmtAttribute &A)
{
    if(Expect(lex::Mnemonic::AttrSeq)) {
        A << mCursor;
        if (Expect(lex::Type::Id)) {
            A << mCursor;
            A.Assigned.Bg = 1;
            A.SetFG(Color::Scan(mCursor->Text().data()));
        }
        if(Expect(lex::Mnemonic::On) || Expect(lex::Mnemonic::ArgSep))
        {
            if(Expect(lex::Type::Id))
            {
                A << mCursor;
                A.Assigned.Bg = 1;
                A.SetBG(Color::Scan(mCursor->Text().data()));
            }
            else return Result::Rejected;
        }
        else return Result::Rejected;
    }
    return Result::Accepted;
}

Book::Result FmtCompiler::CompileLineBreakKeyword(FmtAttribute &A)
{
    return Result::Notimplemented;
}

Book::Result FmtCompiler::CompileIconKeyword(FmtAttribute &A)
{

    if(Expect(lex::Mnemonic::AttrSeq))
    {
        A << mCursor;
        if(Expect(lex::Type::Id))
        {
            A << mCursor;
            auto [Ok,Ic] = Utf::Glyph::ScanName(mCursor->Text().data());
            if(Ok)
            {
                A.Assigned.Ic = 1;
                A.Ic = Utf::Glyph::Scan(mCursor->Text().data());
            }
            return Result::Rejected;
        }
    }
    return Result::Accepted;
}

void FmtCompiler::PushAttribute(FmtAttribute &A)
{
    //...
    mConfig.Product->emplace_back(A);
}

Book::Result FmtCompiler::CompileResetKeyword(FmtAttribute &A)
{
    if(Expect(lex::Type::Keyword))
    {
        A << mCursor;
        switch(mCursor->M)
        {
            case lex::Mnemonic::ForeGround:
                A.Assigned.Fg = 1;
                A.Colors.Fg = Color::Reset;
                break;
            case lex::Mnemonic::BackGround:
                A.Assigned.Bg = 1;
                A.Colors.Bg = Color::Reset;
                break;
            case lex::Mnemonic::ColorPair:
                A.Assigned.Bg = A.Assigned.Bg = 1;
                A.Colors = {Color::Reset,Color::Reset};
                break;
            default: break;
        }
        return Result::Accepted;
    }
    return  Book::Result::Rejected;
}


} // Book::Fmt

