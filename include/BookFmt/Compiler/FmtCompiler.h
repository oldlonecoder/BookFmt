//
// Created by oldlonecoder on 24-04-03.
//

//#ifndef BOOKFMT_FMTCOMPILER_H
//#define BOOKFMT_FMTCOMPILER_H

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

#include <BookFmt/FmtAttribute.h>
#include <BookFmt/Compiler/Tokens.h>
namespace Book::Fmt
{


class BOOKFMT_API FmtCompiler
{


    lex::TokenInfo::Iterator mCursor{};
    FmtAttribute             mAttribute{};
public:


    struct BOOKFMT_API ConfigData
    {
        std::string_view        Source;
        Tokens*                 TokensTable{nullptr};
        FmtAttribute::Array*    Product{nullptr};
    };



    FmtCompiler() = default;
    ~FmtCompiler() =default;

    Book::Result Compile();

    FmtCompiler::ConfigData& Config() { return mConfig; }


private:
    ConfigData mConfig{};

    bool Expect(lex::Mnemonic::T M);
    bool Expect(lex::Type::T Type);
    Book::Result CompileFmt(FmtAttribute& A);
    Book::Result CompileAccent(FmtAttribute& A);
    Book::Result CompileFgKeyword(FmtAttribute& A);
    Book::Result CompileBgKeyword(FmtAttribute& A);
    Book::Result CompileColorPairKeyword(FmtAttribute& A);
    Book::Result CompileLineBreakKeyword(FmtAttribute& A);
    Book::Result CompileIconKeyword(FmtAttribute& A);
    Book::Result CompileResetKeyword(FmtAttribute& A);

    void PushAttribute(FmtAttribute& A);

};

} // Book::Fmt

//#endif //BOOKFMT_FMTCOMPILER_H
