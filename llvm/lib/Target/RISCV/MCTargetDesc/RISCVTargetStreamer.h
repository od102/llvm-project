//===-- RISCVTargetStreamer.h - RISC-V Target Streamer ---------*- C++ -*--===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_RISCV_MCTARGETDESC_RISCVTARGETSTREAMER_H
#define LLVM_LIB_TARGET_RISCV_MCTARGETDESC_RISCVTARGETSTREAMER_H

#include "RISCV.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"

namespace llvm {

class formatted_raw_ostream;

class RISCVTargetStreamer : public MCTargetStreamer {
  RISCVABI::ABI TargetABI = RISCVABI::ABI_Unknown;

public:
  RISCVTargetStreamer(MCStreamer &S);
  void finish() override;
  virtual void reset();

  virtual void emitDirectiveOptionPush();
  virtual void emitDirectiveOptionPop();
  virtual void emitDirectiveOptionPIC();
  virtual void emitDirectiveOptionNoPIC();
  virtual void emitDirectiveOptionRVC();
  virtual void emitDirectiveOptionNoRVC();
  virtual void emitDirectiveOptionRelax();
  virtual void emitDirectiveOptionNoRelax();
  virtual void emitDirectiveVariantCC(MCSymbol &Symbol);
  virtual void emitDirectiveOptionArchFullArch(StringRef Value,
                                               bool &PrefixEmitted);
  virtual void emitDirectiveOptionArchPlusOrMinus(StringRef Value, bool Enable,
                                                  bool &PrefixEmitted,
                                                  bool EmitComma);
  virtual void emitAttribute(unsigned Attribute, unsigned Value);
  virtual void finishAttributeSection();
  virtual void emitTextAttribute(unsigned Attribute, StringRef String);
  virtual void emitIntTextAttribute(unsigned Attribute, unsigned IntValue,
                                    StringRef StringValue);

  void emitTargetAttributes(const MCSubtargetInfo &STI, bool EmitStackAlign);
  void setTargetABI(RISCVABI::ABI ABI);
  RISCVABI::ABI getTargetABI() const { return TargetABI; }
};

// This part is for ascii assembly output
class RISCVTargetAsmStreamer : public RISCVTargetStreamer {
  formatted_raw_ostream &OS;

  void finishAttributeSection() override;
  void emitAttribute(unsigned Attribute, unsigned Value) override;
  void emitTextAttribute(unsigned Attribute, StringRef String) override;
  void emitIntTextAttribute(unsigned Attribute, unsigned IntValue,
                            StringRef StringValue) override;

public:
  RISCVTargetAsmStreamer(MCStreamer &S, formatted_raw_ostream &OS);

  void emitDirectiveOptionPush() override;
  void emitDirectiveOptionPop() override;
  void emitDirectiveOptionPIC() override;
  void emitDirectiveOptionNoPIC() override;
  void emitDirectiveOptionRVC() override;
  void emitDirectiveOptionNoRVC() override;
  void emitDirectiveOptionRelax() override;
  void emitDirectiveOptionNoRelax() override;
  void emitDirectiveVariantCC(MCSymbol &Symbol) override;
  void emitDirectiveOptionArchFullArch(StringRef Value,
                                       bool &PrefixEmitted) override;
  void emitDirectiveOptionArchPlusOrMinus(StringRef Value, bool Enable,
                                          bool &PrefixEmitted,
                                          bool EmitComma) override;
};

}
#endif
