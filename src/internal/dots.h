#ifndef RLANG_INTERNAL_DOTS_H
#define RLANG_INTERNAL_DOTS_H


#define DOTS_CAPTURE_TYPE_MAX 3
enum dots_collect {
  DOTS_COLLECT_expr,
  DOTS_COLLECT_quo,
  DOTS_COLLECT_value
};

enum dots_expansion_op {
  OP_EXPR_NONE,
  OP_EXPR_UQ,
  OP_EXPR_UQS,
  OP_EXPR_UQN,
  OP_EXPR_FIXUP,
  OP_EXPR_DOT_DATA,
  OP_EXPR_CURLY,
  OP_QUO_NONE,
  OP_QUO_UQ,
  OP_QUO_UQS,
  OP_QUO_UQN,
  OP_QUO_FIXUP,
  OP_QUO_DOT_DATA,
  OP_QUO_CURLY,
  OP_VALUE_NONE,
  OP_VALUE_UQ,
  OP_VALUE_UQS,
  OP_VALUE_UQN,
  OP_VALUE_FIXUP,
  OP_VALUE_DOT_DATA,
  OP_VALUE_CURLY,
  OP_DOTS_MAX
};


#endif
