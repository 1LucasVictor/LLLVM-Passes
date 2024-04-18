#ifndef CG_ANALYZER
#define CG_ANALYZER

#include "llvm/Pass.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/CallGraphSCCPass.h"
#include "llvm/Support/GraphWriter.h"
#include "llvm/Support/raw_ostream.h"

namespace cganalyzer_nm {

// class CGAnalyzer : public llvm::AnalysisInfoMixin<CGAnalyzer> {
// public:
//   using Result = llvm::SmallVector<llvm::BinaryOperator *, 0>;
//   Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
//   static llvm::AnalysisKey Key;
// };

class CGAnalyzerPass : public llvm::PassInfoMixin<CGAnalyzerPass> {
public:
  explicit CGAnalyzerPass(llvm::raw_ostream &OS) : OS(OS) {}

  llvm::PreservedAnalyses run(llvm::Module &M,
                              llvm::ModuleAnalysisManager &MAM);

  // Without isRequired returning true, this pass will be skipped for functions
  // decorated with the optnone LLVM attribute. Note that clang -O0 decorates
  // all functions with optnone.
  static bool isRequired() { return true; }

private:
  llvm::raw_ostream &OS;
};
} // namespace cganalyzer_nm
#endif