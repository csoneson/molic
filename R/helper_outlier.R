## ---------------------------------------------------------
##                NON-EXPORTED HELPERS
## ---------------------------------------------------------
new_outlier_model <- function(A, sims, mu, sigma, cdf, Cms, Sms) {
  structure(
    list(
      A     = A,
      sims  = sims,
      mu    = mu,
      sigma = sigma,
      cdf   = cdf,
      Cms   = Cms,
      Sms   = Sms
    ),
    class = c("outlier_model", "list")
  )
}

new_outlier <- function(m, dev, pv, cv, a) {
  # m : outlier_model object
  m$dev    <- dev
  m$pval   <- pv
  m$cv     <- cv
  m$alpha  <- a
  class(m) <- c("outlier", class(m))
  return(m)
}

new_mixed_outlier <- function(m, dev, pv, cv, a) {
  # m : outlier_model object
  m <- new_outlier(m, dev, pv, cv, a)
  class(m) <- c("mixed_outlier", class(m))
  return(m)
}

convolute <- function(m1, m2) {
  # m1 and m2 : outlier_model objects
  .sims <- m1$sims + m2$sims
  .cdf  <- stats::ecdf(.sims)
  .mu   <- m1$mu + m2$mu
  .sig  <- m1$sigma + m2$sigma
  m     <- new_outlier_model(rbind(m1$A, m2$A), .sims, .mu, .sig, .cdf, NULL, NULL)
  return(m)
}

only_single_chars <- function(A) {
  for (i in seq_along(nrow(A))) {
    for (j in seq_along(ncol(A)))
      if ( nchar(A[i,j]) != 1L ) return(FALSE)
  }
  return(TRUE)
}


## Shut up CRAN check - foreach and z are good friends!
utils::globalVariables('z') 

.sim_internal <- function(A,
                  C_marginals,
                  S_marginals,
                  nsim         = 1000,
                  type         = "lr",
                  ncores       = 1) {
  y <- replicate(nsim, vector("character", ncol(A)), simplify = FALSE)
  M <- nrow(A)
  Delta   <- colnames(A)
  C1_vars <- attr(C_marginals[[1]], "vars")
  C1_idx  <- match(C1_vars, Delta)
  p_nC1   <- C_marginals[[1]] / M
  yC1_sim <- sample(names(p_nC1), nsim, replace = TRUE, prob = p_nC1)
  if(!( length(C_marginals) - 1L)) {
    # The complete graph
    yC1_sim <- lapply(strsplit(yC1_sim, ""), function(z) {names(z) = C1_vars; z})
    return( sapply(yC1_sim, TY, C_marginals, S_marginals) )
  }
  doParallel::registerDoParallel(ncores)
  combine_ <- switch(type, "deviance"  = 'c', "raw" = "rbind")
  y <- foreach::`%dopar%`(foreach::foreach(z = 1:nsim, .combine = combine_, .inorder = FALSE), {
    y_sim_z <- y[[z]]
    y_sim_z[C1_idx] <- .split_chars(yC1_sim[1])
    for( k in 2:length(C_marginals) ) {
      nCk     <- C_marginals[[k]]
      Ck_vars <- attr(nCk, "vars")     # Clique names
      Ck_idx  <- match(Ck_vars, Delta) # Where is Ck in Delta
      nSk     <- S_marginals[[k]]      # For Sk = Ø we have that nSk = M
      Sk_vars <- attr(nSk, "vars")     # Separator names
      if( is.null(Sk_vars) ) {         # For empty separators
        p_nCk_minus_nSk <- nCk / nSk   # nSk = M !
        y_sim_z[Ck_idx] <- .split_chars(sample(names(p_nCk_minus_nSk), 1L, prob = p_nCk_minus_nSk))
      } else {
        Sk_idx              <- match(Sk_vars, Delta)
        Sk_idx_in_Ck        <- match(Sk_vars, Ck_vars)
        Ck_idx_minus_Sk_idx <- Ck_idx[-Sk_idx_in_Ck]
        ySk                 <- y_sim_z[Sk_idx]
        nSk_ySk             <- na_ya(nSk, paste0(ySk, collapse = ""))
        nCk_given_Sk        <- n_b(nCk, structure(Sk_idx_in_Ck, names = ySk) )
        p_nCk_given_Sk_ySk  <- nCk_given_Sk / nSk_ySk # Cant be Inf, since ySk MUST be present since we simulated it
        y_sim_z[Ck_idx_minus_Sk_idx] <- .split_chars(sample(names( p_nCk_given_Sk_ySk), 1L, prob =  p_nCk_given_Sk_ySk))
      }
    }
    out <- structure(y_sim_z, names = Delta)
    if ( type == "deviance") {
      out <- TY(out, C_marginals, S_marginals)
    }
    out
  })
  doParallel::stopImplicitCluster()
  y
}

## ---------------------------------------------------------
##                   EXPORTED HELPERS
## ---------------------------------------------------------

#' Simulate observations from a decomposable graphical model
#'
#' This function simulates observations from a DGM
#' 
#' @param A Character Matrix (data)
#' @param adj Adjacency list of a decomposable graph
#' @param nsim Number of simulations
#' @param ncores Number of cores to use in parallelization
#' @return This function returns a matrix of dimension \code{nsim x ncol(A)} where each row correspond to a simulated observation from a DGM represented by \code{adj}.
#' @examples
#'
#' \dontrun{
#' 
#' library(dplyr)
#' 
#' d <- digits %>%
#'   filter(class == "1") %>%
#'   select(-class)
#' G <- adj_lst(fit_graph(d))
#' dgm_sim(as.matrix(d), G, nsim = 10)
#'
#' }
#' @export
dgm_sim <- function(A, adj, nsim = 1000, ncores = 1) {
  stopifnot( is.matrix(A) )
  RIP   <- rip(adj) # the rip (or actually mcs) will check for decomposability here
  Cms   <- a_marginals(A, RIP$C)
  Sms   <- a_marginals(A, RIP$S)
  out   <- .sim_internal(A, Cms, Sms, nsim = nsim, type = "raw", ncores = ncores)
  row.names(out) <- NULL
  return(out)
}

#' Print outlier model
#'
#' A print method for \code{outlier_model} objects
#'
#' @param x A \code{outlier_model} object
#' @param ... Not used (for S3 compatability)
#' @export
print.outlier_model <- function(x, ...) {
  cls <- paste0("<", paste0(class(x), collapse = ", "), ">")
  cat(
    "\n --------------------------------",
    "\n  Simulations:",         length(x$sims),
    "\n  Variables:",           ncol(x$A),
    "\n  Observations:",        nrow(x$A),
    "\n  Estimated mean:",      round(x$mu, 2),
    "\n  Estimated variance:",  round(x$sigma, 2),
    paste0("\n  ", cls),
    "\n --------------------------------\n"
  )
}

#' Print outlier
#'
#' A print method for \code{outlier} objects
#'
#' @param x A \code{outlier} object
#' @param ... Not used (for S3 compatability)
#' @export
print.outlier <- function(x, ...) {
  cls <- paste0("<", paste0(class(x), collapse = ", "), ">")
  cat(
    "\n --------------------------------",
    "\n  Simulations:",         length(x$sims),
    "\n  Variables:",           ncol(x$A),
    "\n  Observations:",        nrow(x$A),
    "\n  Estimated mean:",      round(x$mu, 2),
    "\n  Estimated variance:",  round(x$sigma, 2),
    "\n    ---------------------------  ",
    "\n  Critical value:", x$cv,
    "\n  Deviance:", x$dev,
    "\n  P-value:", x$pval,
    "\n  Alpha:", x$alpha,
    paste0("\n  ", cls),
    "\n --------------------------------\n"
  )
}

#' Calculate deviance
#'
#' This function calculates the affine value \code{T(y)} of \code{-2 log} likelihood-ratio statistic which is also called the deviance
#'
#' @param x A \code{outlier_model} object
#' @param y An observation (name character vector)
#' @param ... Not used (for S3 compatability)
#' @export
deviance <- function(x, y, ...) {
  UseMethod("deviance")
}

#' @rdname deviance
#' @export
deviance.outlier_model <- function(x, y,...) {
  TY(y, x$Cms, x$Sms)
}

#' Plot of pmf
#'
#' A plot method to show the pmf of the approximated pmf of \code{T(Y)}
#'
#' @param x A \code{outlier_model} object
#' @param ... Not used (for S3 compatability)
#' @export
pmf <- function(x, ...) {
  UseMethod("pmf")
}

#' @rdname pmf
#' @export
pmf.outlier_model <- function(x, ...) {
  graphics::hist(x$sims, breaks = 30, xlab = "Deviance",  freq = FALSE, main = " ")
}

#' Emprical distribution function
#'
#' The empirical cdf of \code{T(Y)}
#'
#' @param x A \code{outlier_model} object
#' @param ... Not used (for S3 compatability)
#' @export
cdf <- function(x, ...) UseMethod("cdf")

#' @rdname cdf
#' @export
cdf.outlier_model <- function(x, ...) return(x$cdf)

#' P-value
#'
#' Calculate the p-value for obtaining \code{ty_new} under \code{H_0}
#'
#' @param x A \code{outlier_model} object
#' @param dz The deviance of the observation \code{z}.
#' @param ... Not used (for S3 compatability)
#' @details The value \code{dz} can be obtained used the \code{deviance} function.
#' @seealso \code{\link{deviance}}
#' @export
pval <- function(x, dz, ...) UseMethod("pval")

#' @rdname pval
#' @export
pval.outlier_model <- function(x, dz, ...) return(1 - x$cdf(dz))


#' Critical value
#'
#' Calculate the critical value for test statistic under \code{H_0}
#'
#' @param m A \code{outlier_model} object
#' @param alpha Significance level (between \code{0} and \code{1})
#' @details The value \code{dz} can be obtained used the \code{deviance} function.
#' @seealso \code{\link{deviance}}
#' @export
critval <- function(m, alpha = 0.05) UseMethod("critval")

#' @rdname critval
#' @export
critval.outlier_model <- function(m, alpha = 0.05) {
  stats::uniroot(function(x) pval(m, x) - alpha, interval = range(m$sims))$root
}

#' Mean
#'
#' Estimated mean of deviance statistic \code{T(Y)}
#'
#' @param x A \code{outlier_model} object
#' @param ... Not used (for S3 compatability)
#' @export
mean.outlier_model <- function(x, ...) return(x$mu)

#' Variance
#'
#' Estimated variance of of the deviance statistic \code{T(Y)}
#'
#' @param x A \code{outlier_model} object
#' @param ... Not used (for S3 compatability)
#' @export
variance <- function(x) UseMethod("variance")

#' @rdname variance
#' @export
variance.outlier_model <- function(x, ...) return(x$sigma)


#' To Single Chars
#'
#' Convert all values in a dataframe or matrix of characters to a single character representation
#'
#' @param x Data frame or matrix of characters
#' @examples
#' d <- data.frame(x = c("11", "2"), y = c("2", "11"))
#' to_single_chars(d)
#' @export
to_single_chars <- function(x) {
  ## Implicitly assumes that no columns has more than length(letters) = 26 unique levels
  apply(x, 2, function(z) {
    f <- as.factor(z)
    levels(f) <- letters[1:length(levels(f))]
    as.character(f)
  })
}
