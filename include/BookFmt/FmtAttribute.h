//
// Created by oldlonecoder on 24-04-02.
//

//#ifndef BOOKFMT_FMTATTRIBUTE_H
//#define BOOKFMT_FMTATTRIBUTE_H

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

#include <BookFmt/Interface.h>
#include <Lexer/Token.h>


namespace Book::Fmt
{

/*!
 * @brief blah
 *
 * @code
    \{ Fg: Yellow; ...} blah \{/Fg}


 */
struct BOOKFMT_API FmtAttribute
{
    Utf::Glyph::Type        Ic{};
    Utf::AccentFR::Type     Ac{};
    Color::Pair         Colors{};
    std::vector<lex::TokenInfo::Iterator> TokenComponents{};

    using Array = std::vector<FmtAttribute>;

    struct BOOKFMT_API AssignBits {
        uint8_t Ic: 1;
        uint8_t Ac: 1;
        uint8_t Fg: 1;
        uint8_t Bg: 1;
        uint8_t Re: 1; ///< Reserved: Assigned Geometry
        uint8_t Fr: 1; ///< Reserved: Assigned Frame Model.
        // ...
    } Assigned{0, 0, 0, 0, 0, 0};


    FmtAttribute& operator = (Utf::Glyph::Type Graphen);
    FmtAttribute& operator = (Utf::AccentFR::Type A);
    FmtAttribute& operator = (Color::Pair Pair);
    FmtAttribute& SetFG(Color::Code C);
    FmtAttribute& SetBG(Color::Code C);

    FmtAttribute& operator << (lex::TokenInfo::Iterator It) { TokenComponents.emplace_back(It); return *this; }

};

} // Book::Fmt

//#endif //BOOKFMT_FMTATTRIBUTE_H
