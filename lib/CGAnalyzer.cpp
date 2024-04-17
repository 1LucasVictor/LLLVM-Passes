#include "CGAnalyzer.hpp"
#include "llvm/IR/Constants.h"
#include "llvm/Support/Casting.h"

using namespace llvm;

namespace cganalyzer_nm {
/// Takes an instruction and checks whether its operands are constant or not.
///
/// \returns true if all operands are constant; otherwise, returns false.
bool isConstantIntOnly(Instruction &I) {
    for (Use &Op : I.operands()) {
        // Check if the operand is a constant integer:
        if (!isa<ConstantInt>(Op)) return false;
    }
    // Return true if all operands are constant integer.
    return true;
}

// Initialize the analysis key.
AnalysisKey CGAnalyzer::Key;

CGAnalyzer::Result CGAnalyzer::run(Function &F,
                                               FunctionAnalysisManager &FAM) {
    SmallVector<BinaryOperator *, 0> AddInsts;
    for (BasicBlock &BB : F) {
        for (Instruction &I : BB) {
            // First, check if "I" is an instance of BinaryOperator:
            if (!I.isBinaryOp()) continue;
            // If it is, check if its opcode is "Add":
            if (!(I.getOpcode() == Instruction::BinaryOps::Add)) continue;
            // Check if all operands are constant integer:
            if (!isConstantIntOnly(I)) continue;
            // If it is "Add", append it to the result vector:
            AddInsts.push_back(&cast<BinaryOperator>(I));
        }
    }
    return AddInsts;
}

PreservedAnalyses CGAnalyzerPrinterPass::run(Function &F,
                                           FunctionAnalysisManager &FAM) {
    auto &AddInsts = FAM.getResult<CGAnalyzer>(F);
    OS << "=============================================\n";
    OS << "|| " << F.getName() << " ||\n";
    OS << "=============================================\n";
    for (auto &Add : AddInsts) OS << *Add << "\n";
    OS << "=============================================\n";
    return PreservedAnalyses::all();
}
} // namespace CGAnalyzer