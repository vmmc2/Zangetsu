#pragma once

#include <string>
#include <variant>
#include <vector>

struct TackyConstant {
  int value;
};

struct TackyVar {
  std::string name;
};

using TackyOperand = std::variant<TackyConstant, TackyVar>;

enum class UnaryOperator { COMPLEMENT, NEGATE };

struct TackyReturn {
  TackyOperand val;
};

struct TackyUnary {
  UnaryOperator unary_op;
  TackyOperand src;
  TackyOperand dst;
};

using TackyInstruction = std::variant<TackyReturn, TackyUnary>;

struct TackyFunction {
  std::string name;
  std::vector<TackyInstruction> instructions;
};

struct TackyProgram {
  TackyFunction function_definition;
};
