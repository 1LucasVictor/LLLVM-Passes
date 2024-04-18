#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "CGAnalyzer.hpp"

using namespace llvm;

// void registerAnalyses(ModuleAnalysisManager &MAM) {
//     MAM.registerPass([] { return cganalyzer_nm::CGAnalyzerPass(); });
// }

bool registerPipeline(StringRef Name, ModulePassManager &MAM,
                      ArrayRef<PassBuilder::PipelineElement>) {
    if (Name == "print<add-const>") {
        MAM.addPass(cganalyzer_nm::CGAnalyzerPass(errs()));
        return true;
    }

    // if (Name == "add-const") {
    //     MAM.addPass(cganalyzer_nm::CGAnalyzerPass());
    //     return true;
    // }

    return false;
}

PassPluginLibraryInfo getAddConstPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "CGAnalyzer", LLVM_VERSION_STRING,
          [](llvm::PassBuilder &PB) {
            // PB.registerAnalysisRegistrationCallback(registerAnalyses);
            PB.registerPipelineParsingCallback(registerPipeline);
          }};
}
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getAddConstPluginInfo();
}