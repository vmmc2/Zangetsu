#pragma once

#include <string>

#include "assembly_ast_nodes.hpp"

class AssemblyEmitter {
public:
  std::string Emit(const Program &program);

private:
  std::string EmitFunction(const Function &function);
  std::string EmitInstruction(const Instruction &instruction);
  std::string EmitSpecificInstruction(const Mov &mov);
  std::string EmitSpecificInstruction(const Ret &ret);
  std::string EmitOperand(const Operand &operand);
  std::string EmitSpecificOperand(const Imm &imm);
  std::string EmitSpecificOperand(const Register &reg);
};
