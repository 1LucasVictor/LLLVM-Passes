#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "CGAnalyzer.hpp"

using namespace llvm;

void registerAnalyses(FunctionAnalysisManager &FAM) {
    FAM.registerPass([] { return cganalyzer_nm::CGAnalyzer(); });
}

bool registerPipeline(StringRef Name, FunctionPassManager &FPM,
                      ArrayRef<PassBuilder::PipelineElement>) {
    if (Name == "print<add-const>") {
        FPM.addPass(cganalyzer_nm::CGAnalyzerPrinterPass(errs()));
        return true;
    }

    // if (Name == "add-const") {
    //     FPM.addPass(cganalyzer_nm::CGAnalyzerPrinterPass());
    //     return true;
    // }

    return false;
}

PassPluginLibraryInfo getAddConstPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "CGAnalyzer", LLVM_VERSION_STRING,
          [](llvm::PassBuilder &PB) {
            PB.registerAnalysisRegistrationCallback(registerAnalyses);
            PB.registerPipelineParsingCallback(registerPipeline);
          }};
}
extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getAddConstPluginInfo();
}