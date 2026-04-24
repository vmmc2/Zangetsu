#include "assembly_emitter.hpp"

#include <format>
#include <sstream>
#include <string>
#include <variant>

#include "assembly_ast_nodes.hpp"

std::string AssemblyEmitter::Emit(const Program &program) {
  std::stringstream ss;
  ss << EmitFunction(program.function_definition);
  ss << ".section .note.GNU-stack,\"\",@progbits";
  return ss.str();
}

std::string AssemblyEmitter::EmitFunction(const Function &function) {
  std::stringstream ss;

  ss << std::format("\t.globl {}\n", function.name);
  ss << std::format("{}:\n", function.name);

  for (const auto &instruction : function.instructions) {
    ss << EmitInstruction(instruction);
  }

  return ss.str();
}

std::string AssemblyEmitter::EmitInstruction(const Instruction &instruction) {
  return std::visit([this](auto &&arg) { return EmitSpecificInstruction(arg); },
                    instruction);
}

std::string AssemblyEmitter::EmitSpecificInstruction(const Mov &mov) {
  return std::format("\tmovl {}, {}\n", EmitOperand(mov.src),
                     EmitOperand(mov.dst));
}

std::string AssemblyEmitter::EmitSpecificInstruction(const Ret &ret) {
  return "\tret\n";
}

std::string AssemblyEmitter::EmitOperand(const Operand &operand) {
  return std::visit([&](auto &&arg) { return EmitSpecificOperand(arg); },
                    operand);
}

std::string AssemblyEmitter::EmitSpecificOperand(const Imm &imm) {
  return std::format("${}", imm.value);
}

std::string AssemblyEmitter::EmitSpecificOperand(const Register &reg) {
  if (reg == Register::EAX) {
    return "%eax";
  }

  return "";
}
