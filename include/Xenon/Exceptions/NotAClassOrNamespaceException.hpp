#pragma once

#include <Xenon/Exceptions/CompilationException.hpp>

namespace Xenon
{
class NotAClassOrNamespaceException : public CompilationException
{
public:
    NotAClassOrNamespaceException(const fs::path &source, antlr4::Token *token) : NotAClassOrNamespaceException(source, token, token->getText()) {}
    NotAClassOrNamespaceException(const fs::path &source, antlr4::Token *token, const std::string &text) : CompilationException(source, "Name is not a class or namespace: " + text, token) {}
};
} // namespace Xenon