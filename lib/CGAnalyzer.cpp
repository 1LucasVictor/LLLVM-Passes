#include "CGAnalyzer.hpp"
#include "llvm/IR/Constants.h"
#include "llvm/Support/Casting.h"

using namespace llvm;

namespace cganalyzer_nm {
	
PreservedAnalyses CGAnalyzerPass::run(llvm::Module &M,
                                      llvm::ModuleAnalysisManager &MAM) {
  CallGraph &CG = MAM.getResult<CallGraphAnalysis>(M);
  int numNodes = 0;
	int totalCalls = 0;
  int numCalledFunctions = 0;
	float outDegreeMean;
	int maxOutDegree = 0;

  for (auto &nodePair : CG) {
    const Function* Caller = nodePair.first;
    CallGraphNode* Node = nodePair.second.get();
		if(!Caller)
			continue;
		
		int nodeCalls = Node->size();
		numNodes++;
		totalCalls += nodeCalls;
		if(nodeCalls > maxOutDegree)
			maxOutDegree = nodeCalls;

		for(auto &Edge : *Node) {
			CallGraphNode* CalleNode = Edge.second;
			Function* Callee = CalleNode->getFunction();
			if(!Callee)
				continue;
		}
	
  }

	outDegreeMean = (float) totalCalls/numNodes;

	errs() << "Número de nós no Call Graph: " << numNodes << "\n";
	errs() << "Número de Calls no Call Graph: " << totalCalls << "\n";
	errs() << "Grau de Saída Médio: " << outDegreeMean << "\n";
	errs() << "Grau de Saída Máximo: " << maxOutDegree << "\n";
  return PreservedAnalyses::all();
}
} // namespace cganalyzer_nm