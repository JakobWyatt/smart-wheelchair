latexmk -lualatex -shell-escape thesis.tex
gs -sDEVICE=pdfwrite -dCompatibilityLevel=1.4 -dPDFSETTINGS=/prepress \
-dNOPAUSE -dQUIET -dBATCH -sOutputFile=output.pdf thesis.pdf
