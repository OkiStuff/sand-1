#pragma once

#include <san/Scope.hpp>
#include <san/Type.hpp>
#include <san/Values/Function.hpp>
#include <san/Values/GlobalVariable.hpp>

#include <llvm/IR/IRBuilder.h>

namespace San::Types
{
struct UnionProperty
{
    std::string name;
    Type *type;

    UnionProperty(const std::string &name_, Type *type_) : name(name_), type(type_) {}
};

class UnionType : public Type
{
public:
    std::shared_ptr<Scope> static_scope = nullptr;
    std::shared_ptr<Scope> scope = nullptr;

    std::vector<Type *> generics;

    std::vector<UnionProperty *> properties;
    Type *main_type = nullptr;

    UnionType(const std::string &name,
              llvm::StructType *ref,
              std::shared_ptr<Scope> static_scope_,
              const std::vector<Type *> &generics_ = {})
        : Type(name, ref),
          static_scope(static_scope_),
          scope(Scope::create(static_scope_->env)),
          generics(generics_)
    {
    }

    size_t size(std::unique_ptr<llvm::Module> &module) override
    {
        return this->main_type->size(module);
    }

    static UnionType *create(std::shared_ptr<Scope> scope, const std::string &name = "")
    {
        auto ref = llvm::StructType::create(scope->context(), name + ".union");
        return new UnionType(name, ref, scope);
    }

    llvm::StructType *get_ref() override
    {
        return llvm::cast<llvm::StructType>(this->ref);
    }

    UnionProperty *get_property(const std::string &name)
    {
        for (auto &property : this->properties)
        {
            if (property->name == name)
            {
                return property;
            }
        }

        return nullptr;
    }

    void set_properties(const std::vector<UnionProperty *> &properties, llvm::IRBuilder<> &builder, std::unique_ptr<llvm::Module> &module)
    {
        this->properties = properties;

        this->main_type = Type::i8(builder.getContext());

        for (auto &property : properties)
        {
            if (property->type->size(module) > main_type->size(module))
            {
                this->main_type = property->type;
            }
        }

        this->get_ref()->setBody({this->main_type->get_ref()}, true);
    }
};
} // namespace San::Types