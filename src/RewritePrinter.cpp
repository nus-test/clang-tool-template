#include "RewritePrinter.h"
#include "clang/Tooling/Refactoring.h"
#include "llvm/Support/MemoryBuffer.h"
#include <utility> // std::move
#include <algorithm> // std::all_of

namespace nus::test {

namespace detail {
bool isCompilableFilepath(std::string_view path) {
  return path.find(".c") != std::string_view::npos ||
         path.find(".cc") != std::string_view::npos ||
         path.find(".cpp") != std::string_view::npos;
}
} // namespace detail

RewritePrinter::RewritePrinter(const RewriteRule &rule)
    : Transformer(rule,
                  [this](llvm::Expected<clang::tooling::AtomicChange> ac) {
                    if (ac)
                      Changes.push_back(std::move(*ac));
                  }) {}

void RewritePrinter::onEndOfTranslationUnit() {
  if (Changes.size() > 0) {
    auto filepath = Changes.front().getFilePath();
    bool SameFilePath = std::ranges::all_of(Changes, [&filepath](decltype(Changes)::const_reference ac) -> bool {
      return ac.getFilePath() == filepath;
    });

    if (detail::isCompilableFilepath(filepath) && SameFilePath) {
      // open the file
      if (auto buffer = llvm::MemoryBuffer::getFile(filepath, true)) {
        if (auto patched_code = clang::tooling::applyAtomicChanges(
                filepath, (*buffer)->getBuffer(), Changes, {}))
          llvm::outs() << *patched_code; // print the code out to stdout
      }
    }
  }
}
} // namespace nus::test