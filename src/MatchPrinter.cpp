#include "MatchPrinter.h"

namespace nus::test {
void MatchPrinter::run(const MatchResult &Result) {
    for (auto [id, node] : Result.Nodes.getMap()) {
        llvm::outs() << "Found " << id << ":\n";
        node.dump(llvm::outs(), *Result.Context);
    }
}
}