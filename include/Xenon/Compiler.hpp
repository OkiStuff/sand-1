#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/Passes/PassBuilder.h>

#include <memory>
#include <string>
#include <vector>

namespace Xenon
{
class Compiler
{
private:
    std::unique_ptr<llvm::Module> &module;

public:
    Compiler(std::unique_ptr<llvm::Module> &module_) : module(module_) {}

    std::vector<std::string> generate_objects(const std::string &os, const std::string &arch, const llvm::PassBuilder::OptimizationLevel &optimization_level);
};
} // namespace Xenon
