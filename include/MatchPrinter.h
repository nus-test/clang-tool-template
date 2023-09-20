#ifndef MATCHPRINTER_H_
#define MATCHPRINTER_H_

#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace nus::test {
class MatchPrinter : public clang::ast_matchers::MatchFinder::MatchCallback {
public:
    using MatchResult = clang::ast_matchers::MatchFinder::MatchResult;

    void run(const MatchResult &Result) override;
};
    
}

#endif /* MATCHPRINTER_H_ */
