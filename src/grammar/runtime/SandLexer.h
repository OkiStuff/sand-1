
// Generated from SandLexer.g4 by ANTLR 4.8

#pragma once


#include "antlr4-runtime.h"




class  SandLexer : public antlr4::Lexer {
public:
  enum {
    Add = 1, Sub = 2, Mul = 3, Div = 4, Mod = 5, Not = 6, Neg = 7, ConditionalOr = 8, 
    ConditionalAnd = 9, EqualTo = 10, NotEqualTo = 11, LessThanOrEqualTo = 12, 
    LessThan = 13, GreaterThan = 14, Xor = 15, BitwiseOr = 16, BitwiseAnd = 17, 
    Equal = 18, AddEqual = 19, SubEqual = 20, MulEqual = 21, DivEqual = 22, 
    ModEqual = 23, XorEqual = 24, OrEqual = 25, AndEqual = 26, OpeningParen = 27, 
    ClosingParen = 28, OpeningBrace = 29, ClosingBrace = 30, OpeningBracket = 31, 
    ClosingBracket = 32, Variadic = 33, InclusiveRange = 34, ExclusiveRange = 35, 
    As = 36, SizeOf = 37, Const = 38, Class = 39, Extends = 40, Special = 41, 
    Static = 42, Dot = 43, Arrow = 44, Union = 45, Enum = 46, Destructor = 47, 
    Namespace = 48, ScopeResolver = 49, VariableDeclarator = 50, If = 51, 
    Else = 52, While = 53, Break = 54, For = 55, In = 56, Function = 57, 
    Extern = 58, Return = 59, Cast = 60, Alias = 61, Comma = 62, Colon = 63, 
    Attribute = 64, Assembly = 65, Import = 66, True = 67, False = 68, NullLiteral = 69, 
    InstructionsSeparator = 70, VariableName = 71, StringLiteral = 72, CharLiteral = 73, 
    DecimalLiteral = 74, FloatingLiteral = 75, ZeroLiteral = 76, HexadecimalLiteral = 77, 
    BinaryLiteral = 78, Comment = 79, WhiteSpace = 80, LineTerminator = 81
  };

  SandLexer(antlr4::CharStream *input);
  ~SandLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

