#ifndef CG_ANALYZER
#define CG_ANALYZER

#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/PassManager.h"

namespace cganalyzer_nm {


class CGAnalyzer : public llvm::AnalysisInfoMixin<CGAnalyzer> {
  public:
    /// Result of the analysis: a list of instructions of type
    /// "BinaryOperator", opcode "add" and constant operands.
    using Result = llvm::SmallVector<llvm::BinaryOperator *, 0>;
    /// Traverses the function \p F, collecting all the "add" instructions
    /// inside it.
    ///
    /// \returns a list of all the collected "add" instructions.
    Result run(llvm::Function &F, llvm::FunctionAnalysisManager &FAM);
    // A special type used by analysis passes to provide an address that
    // identifies that particular analysis pass type.
    static llvm::AnalysisKey Key;
};



class CGAnalyzerPrinterPass
    : public llvm::PassInfoMixin<CGAnalyzerPrinterPass> {
public:
  explicit CGAnalyzerPrinterPass(llvm::raw_ostream &OS) : OS(OS) {}

  llvm::PreservedAnalyses run(llvm::Function &F,
                              llvm::FunctionAnalysisManager &FAM);

private:
  llvm::raw_ostream &OS;
};
} 
#endif