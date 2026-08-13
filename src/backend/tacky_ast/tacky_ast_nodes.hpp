#pragma once

#include <iostream>
#include <string>
#include <variant>
#include <vector>

struct TackyConstant {
  int value;

  bool operator==(const TackyConstant &) const = default;
};

struct TackyVar {
  std::string name;

  bool operator==(const TackyVar &) const = default;
};

using TackyOperand = std::variant<TackyConstant, TackyVar>;

enum class TackyUnaryOperator { kComplement, kNegate };

struct TackyReturn {
  TackyOperand val;

  bool operator==(const TackyReturn &) const = default;
};

struct TackyUnary {
  TackyUnaryOperator unary_op;
  TackyOperand src;
  TackyOperand dst;

  bool operator==(const TackyUnary &) const = default;
};

using TackyInstruction = std::variant<TackyReturn, TackyUnary>;

template <class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

inline std::ostream &operator<<(std::ostream &os, const TackyOperand &operand) {
  std::visit(overloaded{[&os](const TackyConstant &c) { os << c.value; },
                        [&os](const TackyVar &v) { os << v.name; }},
             operand);
  return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const TackyUnaryOperator &op) {
  switch (op) {
  case TackyUnaryOperator::kComplement:
    os << "COMPLEMENT";
    break;
  case TackyUnaryOperator::kNegate:
    os << "NEGATE";
    break;
  }
  return os;
}

inline std::ostream &operator<<(std::ostream &os,
                                const TackyInstruction &inst) {
  std::visit(
      overloaded{[&os](const TackyReturn &ret) { os << "RETURN " << ret.val; },
                 [&os](const TackyUnary &unary) {
                   os << unary.unary_op << " " << unary.dst << ", "
                      << unary.src;
                 }},
      inst);
  return os;
}

/* This represents a combination of the sequence of instructions needed to
 compute a value and the place (the operand) where this value has been stored.
 */
struct TackyExprResult {
  // List of instructions needed to solve the expression.
  std::vector<TackyInstruction> instructions;
  // Where the result of this expression is stored.
  TackyOperand result;
};

struct TackyFunction {
  std::string name;
  std::vector<TackyInstruction> instructions;
};

struct TackyProgram {
  TackyFunction function_definition;
};
