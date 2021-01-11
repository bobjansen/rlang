#ifndef RLANG_RLANG_H
#define RLANG_RLANG_H

#define R_NO_REMAP
#include <Rinternals.h>
#include <inttypes.h>
#include <stdbool.h>
#include "rlang-types.h"


#include <Rversion.h>
#if (R_VERSION < R_Version(3, 5, 0))
# define r_list_deref_const(x) ((sexp* const *) STRING_PTR(x))
#else
# define r_list_deref_const(x) ((sexp* const *) DATAPTR_RO(x))
#endif

extern sexp* r_shared_true;
extern sexp* r_shared_false;

r_ssize r_as_ssize(sexp* n);


#include "sexp.h"

#include "attrib.h"
#include "debug.h"
#include "c-utils.h"
#include "call.h"
#include "cnd.h"
#include "dict.h"
#include "env.h"
#include "env-binding.h"
#include "eval.h"
#include "export.h"
#include "fn.h"
#include "formula.h"
#include "node.h"
#include "parse.h"
#include "quo.h"
#include "session.h"
#include "stack.h"
#include "state.h"
#include "sym.h"
#include "vec.h"
#include "vec-chr.h"
#include "vec-lgl.h"
#include "vendor.h"

sexp* r_init_library();


#endif
