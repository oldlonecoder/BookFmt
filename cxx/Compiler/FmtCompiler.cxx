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
//    mConfig.TokensTable->DeclareTable();
//    mConfig.TokensTable->DebugDumpRef();

    Lexer.Config() = {
        .Text       = mConfig.Source,
        .Production = mConfig.TokensTable
    };

    if(!Lexer.Execute()) return Result::Failed;
    mConfig.TokensTable->DebugDumpProduct();


    mCursor = mConfig.TokensTable->Production().begin();
    Book::Debug() << " Entering in the Compiler's Token stream loop:";

    while(mCursor != mConfig.TokensTable->Production().end())
    {
        Book::Debug() << " Top-Loop: " << mCursor->Details();
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
    }
    //...

    Book::Debug() << "Test stops here... ";
    Book::Out() << "Todo: Implement more 'attributes' ...";


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
    A << mCursor++;
    while((mCursor != mConfig.TokensTable->Production().end()) && !Expect(lex::Mnemonic::EndFmt))
    {
        // Keywords:
        // {Fg Bg Colors Icon Brk /}
        auto Node = Keys.find(mCursor->M);
        if(Node == Keys.end())
        {
            if(mCursor->M != lex::Mnemonic::EndFmt)
                return Book::Result::Rejected;

            A << mCursor++;
            return Book::Result::Accepted;
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
    std::string Name;
    A << mCursor;
    if(Expect(lex::Type::Id))
    {
        A << mCursor;
        Name = std::string(mCursor->Text());
        auto [Ok,Acc] = Utf::AccentFR::ScanName(Name);
        if(!Ok) return Result::Rejected;
        A.Assigned.Ac = 1;
        A.Ac = Acc;
        if(!Expect(lex::Mnemonic::Semicolon)) return Book::Result::Rejected;
        A << mCursor++;
        return Book::Result::Accepted;
    }
    return Result::Rejected;
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
    if(mCursor->Sem &  Type) return true;

    --mCursor;
    return false;
}

Book::Result FmtCompiler::CompileFgKeyword(FmtAttribute &A)
{
    A << mCursor;
    if(Expect(lex::Mnemonic::AttrSeq)) {
        A << mCursor;
        if (Expect(lex::Type::Id)) {
            A << mCursor;
            A.Assigned.Fg = 1;
            A.SetFG(Color::Scan(mCursor->Text().data()));
            if(Expect(lex::Mnemonic::Semicolon))
                A << mCursor++; // consume if it is or rewind mCursor if not.
            else
                ++mCursor;
        }
        else return Result::Rejected;
    }
    return Result::Accepted;
}

Book::Result FmtCompiler::CompileBgKeyword(FmtAttribute &A)
{
    A << mCursor;
    if(Expect(lex::Mnemonic::AttrSeq)) {
        A << mCursor;
        if (Expect(lex::Type::Id)) {
            A << mCursor;
            A.Assigned.Bg = 1;
            A.SetBG(Color::Scan(mCursor->Text().data()));
            if(Expect(lex::Mnemonic::Semicolon))
                A << mCursor++; // consume if it is or rewind mCursor if not.
            else
                ++mCursor;
        }
        else return Result::Rejected;
    }
    return Result::Accepted;
}

Book::Result FmtCompiler::CompileColorPairKeyword(FmtAttribute &A)
{
    A << mCursor;
    std::string ColNameTemp;
    if(Expect(lex::Mnemonic::AttrSeq)) {
        A << mCursor;
        if (Expect(lex::Type::Id)) {
            A << mCursor;
            A.Assigned.Fg = 1;
            ColNameTemp = std::string(mCursor->Text());
            A.SetFG(Color::Scan(ColNameTemp));
        }
        if(Expect(lex::Mnemonic::On) || Expect(lex::Mnemonic::ArgSep))
        {
            A << mCursor;
            if(Expect(lex::Type::Id))
            {
                A << mCursor;
                A.Assigned.Bg = 1;
                ColNameTemp = std::string(mCursor->Text());
                A.SetBG(Color::Scan(ColNameTemp));
                if(Expect(lex::Mnemonic::Semicolon))
                    A << mCursor++; // consume if it is or rewind mCursor if not.
                else
                    ++mCursor; // Consume anyway...
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
    A << mCursor;
    if(Expect(lex::Mnemonic::AttrSeq))
    {
        A << mCursor;
        if(Expect(lex::Type::Id))
        {
            A << mCursor;
            auto Name = std::string(mCursor->Text());
            auto [Ok,Ic] = Utf::Glyph::ScanName(Name);
            if(Ok)
            {
                A.Assigned.Ic = 1;
                A.Ic = Ic;
                if(Expect(lex::Mnemonic::Semicolon))
                    A << mCursor++; // consume if it is or rewind mCursor if not.
                else
                    ++mCursor;
            }
            else return Result::Rejected;
        }
    }
    return Result::Accepted;
}

void FmtCompiler::PushAttribute(FmtAttribute &A)
{
    //...
    Book::Debug() << ":";
    A.Length = (A.TokenComponents.back()->Loc.Offset - (*A.TokenComponents.begin())->Loc.Offset)+1;
    A.DebugDumpDetails();
    mConfig.Product->push_back(A);
}

Book::Result FmtCompiler::CompileResetKeyword(FmtAttribute &A)
{
    return  Book::Result::Notimplemented;
}


} // Book::Fmt

