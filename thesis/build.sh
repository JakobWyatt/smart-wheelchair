latexmk -lualatex -shell-escape $1.tex
gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/prepress \
-dNOPAUSE -dQUIET -dBATCH -sOutputFile=19477143.pdf $1.pdf
