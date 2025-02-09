#include "rlang.h"
#include "decl/cnd-decl.h"


#define BUFSIZE 8192

#define INTERP(BUF, FMT, DOTS)                  \
  {                                             \
    va_list dots;                               \
    va_start(dots, FMT);                        \
    vsnprintf(BUF, BUFSIZE, FMT, dots);         \
    va_end(dots);                               \
                                                \
    BUF[BUFSIZE - 1] = '\0';                    \
  }


__attribute__((noreturn))
void (*r_stop_internal)(const char* fn, const char* fmt, ...) = NULL;

static r_obj* msg_call = NULL;
void r_inform(const char* fmt, ...) {
  char buf[BUFSIZE];
  INTERP(buf, fmt, ...);

  r_eval_with_x(msg_call, KEEP(r_chr(buf)), r_envs.ns);

  FREE(1);
}

static r_obj* wng_call = NULL;
void r_warn(const char* fmt, ...) {
  char buf[BUFSIZE];
  INTERP(buf, fmt, ...);

  r_eval_with_x(wng_call, KEEP(r_chr(buf)), r_envs.ns);

  FREE(1);
}

static r_obj* err_call = NULL;
void r_abort(const char* fmt, ...) {
  char buf[BUFSIZE];
  INTERP(buf, fmt, ...);
  r_obj* message = KEEP(r_chr(buf));

  // Evaluate in a mask but forward error call to the current frame
  r_obj* frame = KEEP(r_peek_frame());
  r_obj* mask = KEEP(r_alloc_environment(2, frame));
  r_env_poke(mask, r_syms.error_call_flag, frame);

  struct r_pair args[] = {
    { r_syms.message, message }
  };

  r_exec_n(r_null, r_syms.abort, args, R_ARR_SIZEOF(args), mask);

  while (1); // No return
}

__attribute__((noreturn))
void r_abort_n(const struct r_pair* args, int n) {
  r_exec_mask_n(r_null, r_syms.abort, args, n, r_envs.ns);
  r_stop_unreached("r_abort_n");
}

void r_cnd_signal(r_obj* cnd) {
  r_eval_with_x(cnd_signal_call, cnd, r_envs.base);
}

// For `R_interrupts_suspended`
#include <R_ext/GraphicsEngine.h>
#include <R_ext/GraphicsDevice.h>

#ifdef _WIN32
#include <Rembedded.h>
void r_interrupt() {
  UserBreak = 1;
  R_CheckUserInterrupt();
}
#else
#include <Rinterface.h>
void r_interrupt() {
  Rf_onintr();
}
#endif

enum r_cnd_type r_cnd_type(r_obj* cnd) {
  r_obj* classes = r_class(cnd);
  if (r_typeof(cnd) != R_TYPE_list ||
      r_typeof(classes) != R_TYPE_character) {
    goto error;
  }

  r_obj* const * v_classes = r_chr_cbegin(classes);
  r_ssize n_classes = r_length(classes);

  for (r_ssize i = n_classes - 2; i >= 0; --i) {
    r_obj* class_str = v_classes[i];

    if (class_str == r_strs.error) {
      return R_CND_TYPE_error;
    }
    if (class_str == r_strs.warning) {
      return R_CND_TYPE_warning;
    }
    if (class_str == r_strs.message) {
      return R_CND_TYPE_message;
    }
    if (class_str == r_strs.interrupt) {
      return R_CND_TYPE_interrupt;
    }
  }

  if (r_inherits(cnd, "condition")) {
    return R_CND_TYPE_condition;
  }

 error:
  r_abort("`cnd` is not a condition object.");
}


void r_init_library_cnd() {
  msg_call = r_parse("message(x)");
  r_preserve(msg_call);

  wng_call = r_parse("warning(x, call. = FALSE)");
  r_preserve(wng_call);

  err_call = r_parse("rlang::abort(x)");
  r_preserve(err_call);

  cnd_signal_call = r_parse("rlang::cnd_signal(x)");
  r_preserve(cnd_signal_call);

  r_stop_internal = (__attribute__((noreturn)) void (*)(const char*, const char*, ...)) R_GetCCallable("rlang", "rlang_stop_internal");

  r_format_error_arg = (const char* (*)(r_obj*)) r_peek_c_callable("rlang", "rlang_format_error_arg");
}

static
r_obj* cnd_signal_call = NULL;

const char* (*r_format_error_arg)(r_obj* arg) = NULL;
