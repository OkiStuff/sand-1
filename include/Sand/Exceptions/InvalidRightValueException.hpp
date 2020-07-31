#pragma once

#include <Sand/Exceptions/CompilationException.hpp>

namespace Sand
{
class InvalidRightValueException : public CompilationException
{
public:
    InvalidRightValueException(const fs::path &source, antlr4::Token *token) : InvalidRightValueException(source, token, token->getText()) {}
    InvalidRightValueException(const fs::path &source, antlr4::Token *token, const std::string &text) : CompilationException(source, "Invalid right-value: " + text, token) {}
};
} // namespace Sand