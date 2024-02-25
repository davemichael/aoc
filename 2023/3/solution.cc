#include <cassert>
#include <cctype>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

// Note that this could be done one line at a time. Given that the input file is
// <20kb, we'll just load the whole thing, because it will be easier to code
// this way. We'll also pad the margins to make it easy to search around for
// symbols.

struct Number {
  int row = 0;
  int first = 0;
  int last = 0;
};

class Location;

class Diagram {
 public:
  static Diagram ReadDiagram(std::istream& is);
  // Find the next number starting from row,col
  std::optional<Number> GetNextNumber(const Location& location) const;
  std::vector<Location> AdjacentSymbols(
      const Number& num,
      const std::function<bool(const char c)>& is_symbol) const;
  bool BordersSymbol(const Number& num) const;
  int ExtractNum(const Number& num) const;
 private:
  std::vector<std::string> diagram_;
  friend class Location;
};

class Location {
 public:
  Location(int row, int col, const Diagram& diagram)
    : row_(row), col_(col), diagram_(&diagram.diagram_) {}
  bool InBounds() const {
    return row_ > 0 && (row_ < diagram_->size() - 1)
        && col_ > 0 && col_ < (*diagram_)[row_].size() - 1;
  }
  static Location NextLocation(const Number& num, const Diagram& diagram) {
    Location last_loc(num.row, num.last, diagram);
    last_loc.Advance();
    return last_loc;
  }
  bool IsDigit() const {
    assert(InBounds());
    return std::isdigit((*diagram_)[row_][col_]);
  }
  void AdvanceInRow() {
    ++col_;
  }
  void Advance() {
    ++col_;
    if (col_ >= (*diagram_)[row_].size() - 1) {
      ++row_;
      col_ = 1;
    }
  }
  int row() const { return row_; }
  int col() const { return col_; }
 private:
  int row_;
  int col_;
  const std::vector<std::string>* diagram_;
};

bool operator<(const Location& left, const Location& right) {
  if (left.row() == right.row()) return left.col() < right.col();
  return left.row() < right.row();
}

Diagram Diagram::ReadDiagram(std::istream& is) {
   // Make an initially empty first row and the first row for reading.
  std::vector<std::string> diagram(2);
  while (std::getline(is, diagram.back())) {
    // pad front and back
    diagram.back() = std::string(".") + diagram.back() + ".";
    // And append another line for the next row (which might be empty/padding
    diagram.emplace_back();
  }
  if (diagram.size() > 2) {
    // fill out top and bottom padding rows
    diagram.front().resize(diagram[1].size());
    for (char& c : diagram.front()) { c = '.'; }
    diagram.back() = diagram.front();
  }
  Diagram d;
  d.diagram_ = std::move(diagram);
  return d;
}

// Find the next number starting from row,col
std::optional<Number> Diagram::GetNextNumber(const Location& loc) const {
  auto first_loc = loc;
  while (first_loc.InBounds() && !first_loc.IsDigit()) { first_loc.Advance(); }
  if (!first_loc.InBounds()) {
    return std::nullopt;
  }
  Location last_loc = first_loc;
  Location end_loc = last_loc; end_loc.Advance();
  while (end_loc.InBounds() && end_loc.IsDigit()) {
    last_loc = end_loc;
    end_loc.AdvanceInRow();
  }
  assert(last_loc.InBounds());
  assert(first_loc.row() == last_loc.row());
  return Number{.row = first_loc.row(),
                .first = first_loc.col(),
                .last = last_loc.col()};
}

std::vector<Location> Diagram::AdjacentSymbols(
    const Number& num,
    const std::function<bool(const char c)>& is_symbol) const {
  std::vector<Location> locs;
  for (int row = num.row-1; row <= num.row+1; row += 2) {
    for (int col = num.first - 1; col <= num.last + 1; ++col) {
      if (is_symbol(diagram_[row][col])) {
        locs.push_back(Location(row, col, *this));
      }
    }
  }
  if (is_symbol(diagram_[num.row][num.first - 1])) {
    locs.emplace_back(num.row, num.first - 1, *this);
  }
  if (is_symbol(diagram_[num.row][num.last + 1])) {
    locs.emplace_back(num.row, num.last + 1, *this);
  }
  return locs;
}

int Diagram::ExtractNum(const Number& num) const {
  std::string s = diagram_[num.row].substr(num.first, num.last+1-num.first);
  std::istringstream is(s);
  int val;
  is >> val;
  return val;
}

int SumNumbersAdjacentToSymbols(const Diagram& diagram) {
  Location first_loc(1, 1, diagram);
  int sum = 0;
  for (std::optional<Number> num = diagram.GetNextNumber(first_loc);
       num != std::nullopt;
       num = diagram.GetNextNumber(Location::NextLocation(*num, diagram))) {
    std::vector<Location> symbols =
        diagram.AdjacentSymbols(*num,
                                [](const char c) {
                                  return c != '.' && !std::isdigit(c);
                                });
    if (!symbols.empty()) {
      sum += diagram.ExtractNum(*num);
    }
  }
  return sum;
}

int SumGearRatios(const Diagram& diagram) {
  Location first_loc(1, 1, diagram);
  std::map<Location, std::vector<Number>> gear_numbers;
  for (std::optional<Number> num = diagram.GetNextNumber(first_loc);
       num != std::nullopt;
       num = diagram.GetNextNumber(Location::NextLocation(*num, diagram))) {
    std::vector<Location> gears =
        diagram.AdjacentSymbols(*num,
                                [](const char c) {
                                  return c == '*';
                                });
    for (const Location& gear : gears) {
      gear_numbers[gear].push_back(*num);
    }
  }
  int sum = 0;
  for (const auto& [gear, nums] : gear_numbers) {
    if (nums.size() == 2) {
      sum += diagram.ExtractNum(nums[0]) * diagram.ExtractNum(nums[1]);
    }
  }
  return sum;
}

int main() {
  Diagram diagram = Diagram::ReadDiagram(std::cin);
  std::cout << SumNumbersAdjacentToSymbols(diagram) << std::endl;
  std::cout << SumGearRatios(diagram) << std::endl;
}
