//
// Created by oldlonecoder on 24-04-02.
//

#include "BookFmt/Compiler/Tokens.h"

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

using namespace lex;


namespace Book
{

size_t Fmt::Tokens::DeclareTable()
{
    Ref = TokenInfo::Array{
        {
            .Prim  = Type::Punc,
            .Sem   = Type::Punc,
            .M     = Mnemonic::BeginFmt,
            .Name = "Mnemonic::BeginFmt",
            .D     = Oper::Identifier,
            .Loc   = { .Begin                 = Lexem::BeginMarkup },
            .Flags = { .V                     = 0 }
        },
        {
            .Prim  = Type::Punc,
            .Sem   = Type::Punc,
            .M     = Mnemonic::EndFmt,
            .Name = "Mnemonic::EndFmt",
            .D     = Oper::Identifier,
            .Loc   = { .Begin            = Lexem::EndMarkup },
            .Flags = { .V                = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::ForeGround,
            .Name = "Mnemonic::ForeGround",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::ForeGround},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::BackGround,
            .Name = "Mnemonic::Background",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::BackGround},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::Icon,
            .Name = "Mnemonic::Icon",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::Icon},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::Accent,
            .Name = "Mnemonic::Accent",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::Accent},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Punc,
            .Sem   = Type::Punc,
            .M     = Mnemonic::AttrSeq,
            .Name = "Mnemonic::AttrSeq",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::AttrSeq},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::ColorPair,
            .Name = "Mnemonic::ColorPair",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::ColorPair},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::Reset,
            .Name = "Mnemonic::Reset",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::Reset},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Punc,
            .Sem   = Type::Punc,
            .M     = Mnemonic::ArgSep,
            .Name = "Mnemonic::ArgSep",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::ArgSep},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::LineBreak,
            .Name = "Mnemonic::LineBreak",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::LineBreak},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::Left,
            .Name = "Mnemonic::JustifyLeft",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::JustifyLeft},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::Right,
            .Name = "Mnemonic::JustifyRight",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::JustifyRight},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::Top,
            .Name = "Mnemonic::Top",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::Top},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::Bottom,
            .Name = "Mnemonic::Bottom",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::Bottom},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::Center,
            .Name = "Mnemonic::Center",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::Center},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::HVCenter,
            .Name = "Mnemonic::HVCenter",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::HVCenter},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Keyword,
            .Sem   = Type::Keyword,
            .M     = Mnemonic::Box,
            .Name = "Mnemonic::Box",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::Box},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Punc,
            .Sem   = Type::Punc,
            .M     = Mnemonic::Semicolon,
            .Name = "Mnemonic::SemiColon",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::Semicolon},
            .Flags = { .V                 = 0 }
        },
        {
            .Prim  = Type::Punc,
            .Sem   = Type::Punc,
            .M     = Mnemonic::On,
            .Name = "Mnemonic::ArgSep",
            .D     = Oper::Identifier,
            .Loc   = {. Begin             = Lexem::On},
            .Flags = { .V                 = 0 }
        }
    };


    return Ref.size();
}
} // Book

