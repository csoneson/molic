.PHONY: compile doc check install build_site run_main clean

all: compile doc check

compile:
	Rscript -e "Rcpp::compileAttributes()"

doc:
	Rscript -e "devtools::document()"

check: 
	Rscript -e "devtools::check()"

install:
	Rscript -e "devtools::install()"

build_site:
	Rscript -e "pkgdown::build_site()"

run_main:
	Rscript src/mainR.R

readme:
	Rscript -e "rmarkdown::render('README.Rmd')"; \
	convert man/figures/README-acc-1.png -fuzz 10% -trim +repage man/figures/README-acc-1.png; \
	convert man/figures/README-unacc-1.png -fuzz 10% -trim +repage man/figures/README-unacc-1.png; \
	convert man/figures/README-var-select-1.png -fuzz 10% -trim +repage man/figures/README-var-select-1.png; \
	firefox README.html

clean:
	cd src/ && rm -f *.o && rm -f *.so
