#include "assembly_generator_visitor.hpp"
#include "assembly_ast_nodes.hpp"

#include <any>

std::any AssemblyGeneratorVisitor::VisitProgramNode(ProgramNode *node) {
  auto function_definition =
      std::any_cast<Function>(node->function_definition()->Accept(*this));

  return Program{.function_definition = function_definition};
}

std::any AssemblyGeneratorVisitor::VisitFunctionDefinitionNode(
    FunctionDefinitionNode *node) {
  std::string name = node->identifier().lexeme();

  auto instructions =
      std::any_cast<std::vector<Instruction>>(node->body()->Accept(*this));

  return Function{.name = name, .instructions = instructions};
}

std::any AssemblyGeneratorVisitor::VisitReturnStmtNode(ReturnStmtNode *node) {
  auto src_operand = std::any_cast<Imm>(node->expr()->Accept(*this));

  std::vector<Instruction> instructions;

  instructions.push_back(Mov{.src = src_operand, .dst = Register::EAX});
  instructions.push_back(Ret{});

  return instructions;
}

std::any
AssemblyGeneratorVisitor::VisitConstantExprNode(ConstantExprNode *node) {
  return Imm{.value = node->value()};
}
