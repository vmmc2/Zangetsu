#include "asm_codegen_visitor.hpp"

#include <any>

#include "../asm_ast/asm_ast_nodes.hpp"

std::any AssemblyCodeGenVisitor::VisitProgramNode(ProgramNode *node) {
  Function function_definition =
      std::any_cast<Function>(node->function_definition()->Accept(*this));

  return Program{.function_definition = function_definition};
}

std::any AssemblyCodeGenVisitor::VisitFunctionDefinitionNode(
    FunctionDefinitionNode *node) {
  std::string name = node->identifier().lexeme();

  std::vector<Instruction> instructions =
      std::any_cast<std::vector<Instruction>>(node->body()->Accept(*this));

  return Function{.name = name, .instructions = instructions};
}

std::any AssemblyCodeGenVisitor::VisitReturnStmtNode(ReturnStmtNode *node) {
  Imm src_operand = std::any_cast<Imm>(node->expr()->Accept(*this));

  std::vector<Instruction> instructions;

  instructions.push_back(Mov{.src = src_operand, .dst = Register::EAX});
  instructions.push_back(Ret{});

  return instructions;
}

std::any AssemblyCodeGenVisitor::VisitConstantExprNode(ConstantExprNode *node) {
  return Imm{.value = node->value()};
}
