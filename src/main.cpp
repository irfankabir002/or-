// bonnie: read a sentence and break it down piece by piece.
//
//   bonnie "this and that or the other"
//   echo "this and that" | bonnie

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>

#ifndef VERSION
#define VERSION "dev"
#endif

namespace {

struct Token {
  std::string text;
  bool conjunction;
};

// Words that join or branch. "for" can also be a preposition; bonnie does not
// look at grammar, only at the word itself.
const std::set<std::string> kConjunctions = {"and", "or", "but", "nor",
                                             "so",  "yet", "for"};

std::string to_lower(std::string s) {
  std::transform(s.begin(), s.end(), s.begin(),
                 [](unsigned char c) { return std::tolower(c); });
  return s;
}

// A token is a run of letters, digits or apostrophes. Anything else
// (spaces, punctuation, markdown asterisks) is a boundary between tokens.
std::vector<Token> tokenize(const std::string& sentence) {
  std::vector<Token> tokens;
  std::string current;

  auto flush = [&]() {
    if (current.empty()) return;
    bool is_conj = kConjunctions.count(to_lower(current)) > 0;
    tokens.push_back({current, is_conj});
    current.clear();
  };

  for (unsigned char c : sentence) {
    if (std::isalnum(c) || c == '\'') {
      current.push_back(static_cast<char>(c));
    } else {
      flush();
    }
  }
  flush();  // the last word has no boundary after it
  return tokens;
}

void print_report(const std::vector<Token>& tokens) {
  std::size_t conjunctions = 0;
  std::size_t characters = 0;

  for (std::size_t i = 0; i < tokens.size(); ++i) {
    const Token& t = tokens[i];
    std::cout << (i + 1) << "\t" << t.text << "\t(" << t.text.size() << ")"
              << (t.conjunction ? "\t<- conjunction" : "") << "\n";
    characters += t.text.size();
    if (t.conjunction) ++conjunctions;
  }

  std::cout << "tokens: " << tokens.size() << "\n"
            << "conjunctions: " << conjunctions << "\n"
            << "characters (words only): " << characters << "\n";
}

}  // namespace

int main(int argc, char** argv) {
  std::string sentence;

  if (argc > 1) {
    std::string first = argv[1];
    if (first == "--version") {
      std::cout << "bonnie " << VERSION << "\n";
      return 0;
    }
    if (first == "--help") {
      std::cout << "usage: bonnie [SENTENCE...]\n"
                   "       echo SENTENCE | bonnie\n";
      return 0;
    }
    for (int i = 1; i < argc; ++i) {
      if (i > 1) sentence += ' ';
      sentence += argv[i];
    }
  } else {
    sentence.assign(std::istreambuf_iterator<char>(std::cin),
                    std::istreambuf_iterator<char>());
  }

  print_report(tokenize(sentence));
  return 0;
}
