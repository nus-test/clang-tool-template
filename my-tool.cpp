#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"
#include "llvm/Support/CommandLine.h"

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");
static llvm::cl::extrahelp CommonHelp(clang::tooling::CommonOptionsParser::HelpMessage);
static llvm::cl::extrahelp MoreHelp("\nMore help text...\n");

int main(int argc, const char **argv) {
  using namespace clang::tooling;
  using namespace llvm;
  // CommonOptionsParser constructor will parse arguments and create a
  // CompilationDatabase.  In case of error it will terminate the program.
  auto OptionsParser = CommonOptionsParser::create(argc, argv, MyToolCategory);
  
  if (!OptionsParser) {
    llvm::errs() << OptionsParser.takeError() << "\n";
    return 1;
  }

  ClangTool Tool(OptionsParser->getCompilations(),
                 OptionsParser->getSourcePathList());

  return Tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get());
}