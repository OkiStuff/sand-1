#include <Sand/Compiler.hpp>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/PassManager.h>
#include <llvm/Passes/PassBuilder.h>

#include <llvm/Support/FileSystem.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>

#include <llvm/Target/TargetMachine.h>

#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>

#include <iostream>

std::vector<std::string> Sand::Compiler::generate_objects(const std::string &os, const std::string &arch, const llvm::PassBuilder::OptimizationLevel &optimization_level, const bool &verbose)
{
    if (verbose)
    {
        std::cout << "Data layout: " << this->module->getDataLayoutStr() << std::endl;
        std::cout << "Target triple: " << this->module->getTargetTriple() << std::endl;
    }

    std::string output_path = std::tmpnam(nullptr);
    std::error_code error_code;
    llvm::raw_fd_ostream dest(output_path, error_code, llvm::sys::fs::OF_None);

    if (error_code)
    {
        llvm::errs() << "Could not open file: " << error_code.message();
        return {};
    }

    if (optimization_level != llvm::PassBuilder::OptimizationLevel::O0)
    {
        llvm::PassBuilder builder;
        llvm::LoopAnalysisManager loop_analisys_manager(true);
        llvm::FunctionAnalysisManager function_analisys_manager(true);
        llvm::CGSCCAnalysisManager CGSCC_analisys_manager(true);
        llvm::ModuleAnalysisManager module_analisys_manager(true);

        builder.registerModuleAnalyses(module_analisys_manager);
        builder.registerCGSCCAnalyses(CGSCC_analisys_manager);
        builder.registerFunctionAnalyses(function_analisys_manager);
        builder.registerLoopAnalyses(loop_analisys_manager);
        builder.crossRegisterProxies(loop_analisys_manager, function_analisys_manager, CGSCC_analisys_manager, module_analisys_manager);

        llvm::ModulePassManager module_pass_manager = builder.buildPerModuleDefaultPipeline(optimization_level, true);
        module_pass_manager.run(*module, module_analisys_manager);
    }

    llvm::legacy::PassManager pass;

    pass.add(llvm::createInstructionCombiningPass());
    pass.add(llvm::createReassociatePass());
    pass.add(llvm::createGVNPass());
    pass.add(llvm::createCFGSimplificationPass());

    llvm::CodeGenFileType file_type = llvm::CGFT_ObjectFile;

    if (this->target_machine->addPassesToEmitFile(pass, dest, nullptr, file_type))
    {
        llvm::errs() << "TargetMachine can't emit a file of this type";
        return {};
    }

    pass.run(*this->module);
    dest.flush();

    return {output_path};
}
