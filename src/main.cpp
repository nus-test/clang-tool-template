#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

#include "clang/ASTMatchers/ASTMatchFinder.h"        // MatchFinder
#include "clang/Tooling/Transformer/RangeSelector.h" // RangeSelector
#include "clang/Tooling/Transformer/Stencil.h"       // cat

#include "MatchPrinter.h"
#include "RewritePrinter.h"

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");
static llvm::cl::extrahelp
    CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);
static llvm::cl::extrahelp MoreHelp("\nMore help text...\n");

int main(int argc, const char **argv) {
  using namespace clang::tooling;

  // CommonOptionsParser constructor will parse arguments and create a
  // CompilationDatabase.  In case of error it will terminate the program.
  auto OptionsParser = CommonOptionsParser::create(argc, argv, MyToolCategory);

  if (!OptionsParser) {
    llvm::errs() << OptionsParser.takeError() << "\n";
    return 1;
  }

  ClangTool Tool(OptionsParser->getCompilations(),
                 OptionsParser->getSourcePathList());

  enum class Mode {
    Match,
    Rewrite,
  };

  /* !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    Change this variable to determine what kind of tool you want to generate!
  */
  auto ToolMode = Mode::Match;

  switch (ToolMode) {
  case Mode::Match: {
    using namespace clang::ast_matchers;

    clang::ast_matchers::MatchFinder Finder;
    nus::test::MatchPrinter Printer;

    /*
      If you are only looking out for patterns, the only thing you need to
      change is this rule.

      By default, this definition tries to find a main function that
      takes in two arguments.

      For more information on how to make rules, see the ASTMatchers documentation
      at: https://clang.llvm.org/docs/LibASTMatchersReference.html
    */
    auto MatchRule =
        functionDecl(allOf(hasName("main"), parameterCountIs(2))).bind("mainFunc");

    Finder.addMatcher(MatchRule, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
  }

  case Mode::Rewrite: {
    using namespace clang::ast_matchers;
    using namespace clang::transformer;

    clang::ast_matchers::MatchFinder Finder;

    /*
      For a rewriter, there are four objects you need to define.

      \var MatchRule
      The MatchRule is the AST matcher as in Match

      \var RangeSelector
      The RangeSelector is the region of code to rewrite.

      \var RewriteRule
      The RewriteRule uses the MatchRule and the selector, as well as a Stencil,
      to define the transformation of the code.

      For more information, see the following documentation:
      - ASTMatchers: https://clang.llvm.org/docs/LibASTMatchersReference.html
      - Transformer: https://clang.llvm.org/docs/ClangTransformerTutorial.html
    */
    DeclarationMatcher MatchRule = functionDecl(
        allOf(hasName("main"), hasDescendant(compoundStmt().bind("mainFn"))));

    RangeSelector Selector = statements("mainFn");

    // This surrounds the main function in a true block.
    // Note that we cannot insert AST nodes, only source code.
    Stencil Transformed = cat("if (1) {", Selector, "}");

    RewriteRule Rewrite = makeRule(MatchRule, changeTo(Selector, Transformed));

    nus::test::RewritePrinter Printer(Rewrite);
    Finder.addMatcher(MatchRule, &Printer);

    return Tool.run(newFrontendActionFactory(&Finder).get());
  }
  }
}