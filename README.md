molic: Multivariate OutLIerdetection In Contingency Tables
================

<!-- README.md is generated from README.Rmd. Please edit that file -->
[![Travis Build Status](https://travis-ci.com/mlindsk/molic.svg?token=AuXvB5mAnHuxQxKszxph&branch=master)](https://travis-ci.com/mlindsk/molic) [![AppVeyor build status](https://ci.appveyor.com/api/projects/status/github/mlindsk/molic?branch=master&svg=true)](https://ci.appveyor.com/project/mlindsk/molic) [![status](https://joss.theoj.org/papers/9fa65ced7bf3db01343d68b4488196d8/status.svg)](https://joss.theoj.org/papers/9fa65ced7bf3db01343d68b4488196d8)

About molic
-----------

An **R** package to perform outlier detection in contingency tables using decomposable graphical models (DGMs); models for which the underlying association between all variables can be depicted by an undirected graph. **molic** also offers algorithms for fitting undirected decomposable graphs. Compute-intensive procedures are implementet using [Rcpp](http://www.rcpp.org/)/C++ for better run-time performance.

Getting Started
---------------

If you want to learn the "behind the scenes" of the model it is recommended to go through [The Outlier Model](https://mlindsk.github.io/molic/articles/) and look at the [documentation](https://mlindsk.github.io/molic/reference/index.html) as you read along. See also the examples below and the software paper.

You can install the development version of the package by using the `devtools` package:

``` r
devtools::install_github("mlindsk/molic", build_vignettes = FALSE)
```

How To Cite
-----------

-   If you want to cite the **outlier method** please use

``` latex
@article{lindskououtlier,
  title={Outlier Detection in Contingency Tables Using Decomposable Graphical Models},
  author={Lindskou, Mads and Svante Eriksen, Poul and Tvedebrink, Torben},
  journal={Scandinavian Journal of Statistics},
  publisher={Wiley Online Library},
  doi={10.1111/sjos.12407},
  year={2019}
}
```

-   If you want to cite the **molic** package please use

``` latex
TBA
```

Example - Outlier Detection
---------------------------

To demonstrate the outlier method we use the `car` data set from the [UCI Machine Learning Repository](https://archive.ics.uci.edu/ml/index.php). The data have 4 classes that labels the evaluation of a car; `unacceptable, acc, vgood` and `good`. These classes are determined by the other variables in the data - and theses are *not* necessarily independent of each other and we must therefore "fit their association".

### Reading Data

``` r
library(dplyr)
car <- read.table("https://archive.ics.uci.edu/ml/machine-learning-databases/car/car.data",
  header = FALSE, sep = ",", dec = ".") %>%
  as_tibble() %>%
  mutate_all(as.character)
colnames(car) <- c("buying", "maint", "doors", "persons", "lug", "safety", "class")
```

### Defining Sub-Classes

``` r
vgood_cars <- car %>%
  filter(class == "vgood") %>%
  select(-class)

unacc_cars <- car %>%
  filter(class == "unacc") %>%
  select(-class)
```

### Fitting an Interaction Graph

We fit the interaction graph for the `vgood` cars and plot the result.

``` r
G_vgood  <- fit_graph(vgood_cars, q = 0.5, trace = FALSE) # AIC (q = 0) and BIC (q = 1)
plot(G_vgood)
```

<img src="man/figures/README-acc-1.png" width="100%" style="display: block; margin: auto;" />

For comparison we also fit the interaction graph for the `unacc_cars`

``` r
G_unacc  <- fit_graph(unacc_cars, q = 0.5, trace = FALSE)
plot(G_unacc)
```

<img src="man/figures/README-unacc-1.png" width="100%" style="display: block; margin: auto;" />

It is apparent that very good cars and unacceptable cars are determined by two different mechanisms.

### Outlier Test

We randomly select a car from the `unacc_cars` data and test if it is an outlier in `vgood_cars`.

``` r
set.seed(7)
z <- sample_n(unacc_cars, 1) %>% unlist()
M <- fit_outlier(as.matrix(vgood_cars), z, adj_lst(G_vgood))
#>   Note: A has values larger than a single character. to_single_chars() was used to correct this
M
#> 
#>  -------------------------------- 
#>   Simulations: 5000 
#>   Variables: 6 
#>   Observations: 66 
#>   Estimated mean: -16.22 
#>   Estimated variance: 0.78 
#>     ---------------------------   
#>   Critical value: -15.57848 
#>   Deviance: -3.350997 
#>   P-value: 0 
#>   Alpha: 0.05 
#>   <outlier, outlier_model, list> 
#>  --------------------------------
```

Thus the car is declared an outlier on a 0.05 significance level. We can visualize this by plotting the corresponding density of the deviance statistic as

``` r
pmf(M)
```

<img src="man/figures/README-unnamed-chunk-4-1.png" width="100%" />

and verify that the estimated deviance of the selected car is -3.3509971 which is larger than the critical value of -15.5784775.

Example - Variable Selection
----------------------------

The `fit_graph` procedure can be used as a variable selection tool. The idea is, to fit an interaction graph with the class variable of interest included. The most influential variables on the class variable is then given by the neighboring variables. Lets investigate which variables influences how the cars are labelled.

``` r
G_car <- fit_graph(car, trace = FALSE)
plot(G_car)
```

<img src="man/figures/README-var-select1-1.png" width="100%" style="display: block; margin: auto;" />

So the class of a car is actually determined by all variables except for `doors` (the number of doors in the car). The neighbors of `class` can be extracted as follows

``` r
adj_lst(G_car)$class
#> [1] "safety"  "persons" "buying"  "maint"   "lug"
```

We can also state e.g. that the `safety` of a car is independent of the price (the `buying` varible) when the class of the car is known; this phenomena is also known as *conditional independence*.
