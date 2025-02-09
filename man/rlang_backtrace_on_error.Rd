% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/cnd-abort.R
\name{rlang_backtrace_on_error}
\alias{rlang_backtrace_on_error}
\alias{add_backtrace}
\title{Display backtrace on error}
\description{
rlang errors carry a backtrace that can be inspected by calling
\code{\link[=last_error]{last_error()}}. You can also control the default display of the
backtrace by setting the option \code{rlang_backtrace_on_error} to one
of the following values:
\itemize{
\item \code{"none"} show nothing.
\item \code{"reminder"}, the default in interactive sessions, displays a reminder that
you can see the backtrace with \code{\link[=last_error]{last_error()}}.
\item \code{"branch"} displays a simplified backtrace.
\item \code{"collapse"} displays a collapsed backtrace tree.
\item \code{"full"}, the default in non-interactive sessions, displays the full tree.
}

rlang errors are normally thrown with \code{\link[=abort]{abort()}}. If you promote
base errors to rlang errors with \code{\link[=global_entrace]{global_entrace()}},
\code{rlang_backtrace_on_error} applies to all errors.
}
\section{Promote base errors to rlang errors}{


You can use \code{options(error = rlang::entrace)} to promote base errors to
rlang errors. This does two things:
\itemize{
\item It saves the base error as an rlang object so you can call \code{\link[=last_error]{last_error()}}
to print the backtrace or inspect its data.
\item It prints the backtrace for the current error according to the
\code{rlang_backtrace_on_error} option.
}
}

\section{Errors in RMarkdown}{


The display of errors depends on whether they're expected (i.e.
chunk option \code{error = TRUE}) or unexpected:
\itemize{
\item Expected errors are controlled by the global option
\code{"rlang_backtrace_on_error_report"} (note the \verb{_report} suffix).
The default is \code{"none"} so that your expected errors don't
include a reminder to run \code{rlang::last_error()}. Customise this
option if you want to demonstrate what the error backtrace will
look like.

You can also use \code{\link[=last_error]{last_error()}} to display the trace like you
would in your session, but it currently only works in the next
chunk.
\item Unexpected errors are controlled by the global option
\code{"rlang_backtrace_on_error"}. The default is \code{"branch"} so you'll
see a simplified backtrace in the knitr output to help you figure
out what went wrong.
}

When knitr is running (as determined by the \code{knitr.in.progress}
global option), the default top environment for backtraces is set
to the chunk environment \code{knitr::knit_global()}. This ensures that
the part of the call stack belonging to knitr does not end up in
backtraces. If needed, you can override this by setting the
\code{rlang_trace_top_env} global option.
}

\examples{
# Display a simplified backtrace on error for both base and rlang
# errors:

# options(
#   rlang_backtrace_on_error = "branch",
#   error = rlang::entrace
# )
# stop("foo")
}
