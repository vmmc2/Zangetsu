#include "tacky_codegen_visitor.hpp"

#include <any>
#include <format>

#include "../tacky_ast/tacky_ast_nodes.hpp"

std::any TackyCodegenVisitor::VisitProgramNode(ProgramNode *node) {
  TackyFunction tacky_function_definition =
      std::any_cast<TackyFunction>(node->function_definition()->Accept(*this));

  return TackyProgram{.function_definition = tacky_function_definition};
}

std::any
TackyCodegenVisitor::VisitFunctionDefinitionNode(FunctionDefinitionNode *node) {
  std::string tacky_function_name = node->identifier().lexeme();

  std::vector<TackyInstruction> tacky_instructions =
      std::any_cast<std::vector<TackyInstruction>>(node->body()->Accept(*this));

  return TackyFunction{.name = tacky_function_name,
                       .instructions = tacky_instructions};
}

std::any TackyCodegenVisitor::VisitReturnStmtNode(ReturnStmtNode *node) {
  TackyExprResult tacky_expr_eval =
      std::any_cast<TackyExprResult>(node->expr()->Accept(*this));

  std::vector<TackyInstruction> tacky_instructions =
      tacky_expr_eval.instructions;
  tacky_instructions.push_back(TackyReturn{.val = tacky_expr_eval.result});

  return tacky_instructions;
}

std::any TackyCodegenVisitor::VisitConstantExprNode(ConstantExprNode *node) {
  return TackyExprResult{.instructions = {},
                         .result = TackyConstant(node->value())};
}

std::any TackyCodegenVisitor::VisitUnaryExprNode(UnaryExprNode *node) {
  TackyExprResult inner_eval =
      std::any_cast<TackyExprResult>(node->expr()->Accept(*this));

  TackyVar curr_dst_var = TackyVar{.name = GetCurrTempVarName()};

  TackyUnaryOperator unary_op;
  if (node->unary_op().token_type() == TokenType::kMinus) {
    unary_op = TackyUnaryOperator::kNegate;
  } else if (node->unary_op().token_type() == TokenType::kTilde) {
    unary_op = TackyUnaryOperator::kComplement;
  } else {
    throw std::runtime_error{std::format("Invalid unary operator used: {}",
                                         node->unary_op().lexeme())};
  }

  TackyInstruction curr_tacky_instruction = TackyUnary{
      .unary_op = unary_op, .src = inner_eval.result, .dst = curr_dst_var};

  std::vector<TackyInstruction> curr_instructions = inner_eval.instructions;
  curr_instructions.push_back(curr_tacky_instruction);

  return TackyExprResult{.instructions = curr_instructions,
                         .result = curr_dst_var};
}
