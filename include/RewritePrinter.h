#ifndef REWRITEPRINTER_H_
#define REWRITEPRINTER_H_

#include "clang/Tooling/Refactoring.h"
#include "clang/Tooling/Transformer/RewriteRule.h"
#include "clang/Tooling/Transformer/Transformer.h"

namespace nus::test {
class RewritePrinter : public clang::tooling::Transformer {
public: 
  using RewriteRule = clang::transformer::RewriteRule;
  explicit RewritePrinter(const RewriteRule& rule);
  void onEndOfTranslationUnit() override;
private:
  clang::tooling::AtomicChanges Changes;
};
} // namespace nus::test

#endif /* REWRITEPRINTER_H_ */
