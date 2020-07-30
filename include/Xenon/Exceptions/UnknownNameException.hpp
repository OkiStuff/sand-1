#pragma once

#include <Xenon/Exceptions/CompilationException.hpp>

namespace Xenon
{
class UnknownNameException : public CompilationException
{
public:
    UnknownNameException(const fs::path &source, antlr4::Token *token) : CompilationException(source, "Unknown name: " + token->getText(), token) {}
};
} // namespace Xenon