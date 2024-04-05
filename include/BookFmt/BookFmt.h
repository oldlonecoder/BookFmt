//
// Created by oldlonecoder on 24-04-02.
//

//#ifndef BOOKFMT_BOOKFMT_H
//#define BOOKFMT_BOOKFMT_H

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
#include <AppBook/Book/AppBook.h>
#include <AppBook/Util/Delegate.h>
#include <BookFmt/Compiler/FmtCompiler.h>
//#include "BookFmt/Compiler/FmtLexer.h"

namespace Book::Fmt
{


class BOOKFMT_API BookFmt
{
    std::string_view        mText{};
    StrAcc                  mProduction{}; ///< Rendered Production - or temporary Rendered string(Working buffer).
    FmtAttribute::Array     mAttributes{};
    Tokens                  mTokens{};

    // - Hooks :
    Delegate<FmtAttribute&> RenderAttributeDelegate;
    Delegate<std::string_view const&> RenderTextDelegate;
    // ========================================================
    FmtCompiler::ConfigData mCFG{};
public:

    BookFmt() = default;
    explicit BookFmt(std::string_view Txt);

    ~BookFmt();

    FmtAttribute::Array& Attributes() { return mAttributes; }

    template<typename Class> Delegate<FmtAttribute&>::Slot& DelegateAttributeRenderer(Class& Obj, Delegate<FmtAttribute&>::Slot Slot)
    {
        return RenderAttributeDelegate.Connect(&Obj, Slot);
    }
    template<typename Class> BookFmt& DelegateTextRenderer(Class& Obj, Book::Action(Class::*Slot)(const std::string_view&))
    {
        RenderTextDelegate.Connect(&Obj, Slot);
        return *this;
    }

    BookFmt&     operator << (const std::string& Input);
    Book::Result operator >> (StrAcc& Output);


    Book::Result Process();
private:

    std::string RenderAttribute(FmtAttribute const& A);

//    /*!
//     * @brief Render production into \c Input
//     * @tparam InputType
//     * @param Input
//     * @note Input operator '<<' must be implemented on InputType
//     * @return RTS ( Ref-To_Self )
//     */
//    template<class InputType> BookFmt& operator >> (InputType& Input)
//    {
//
//    }

    Book::Result Compile();


};

} // Book

//#endif //BOOKFMT_BOOKFMT_H
