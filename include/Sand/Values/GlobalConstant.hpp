#pragma once

#include <Sand/Values/Constant.hpp>

#include <llvm/IR/IRBuilder.h>

namespace Sand::Values
{
class GlobalConstant : public Constant
{
public:
    llvm::GlobalVariable *global = nullptr;

    GlobalConstant(const std::string &name, Type *type, llvm::GlobalVariable *ref) : Constant(name, type, ref->getInitializer(), true), global(ref)
    {
        this->is_alloca = true;
    }

    static GlobalConstant *create(const std::string &name, Type *type, llvm::Constant *constant, std::unique_ptr<llvm::Module> &module)
    {
        auto global = new llvm::GlobalVariable(*module, type->get_ref(), true, llvm::GlobalValue::PrivateLinkage, constant, ".str");
        global->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
        global->setAlignment(llvm::Align(1));

        return new GlobalConstant(name, type, global);
    }

    llvm::GlobalVariable *get_ref() const override
    {
        return this->global;
    }
};
} // namespace Sand::Values
