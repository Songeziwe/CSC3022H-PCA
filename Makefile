# Makefile PCA Tutorial
#
# Author: Songeziwe S. Soboois
# Date: July 30, 2019

GPP=g++
STD=-std=c++11

pca:pcaDriver.o pca.o pca.h
	$(GPP) pcaDriver.o pca.o -l armadillo -o pca

pcaDriver.o:pcaDriver.cpp pca.h
	$(GPP) -c pcaDriver.cpp -o pcaDriver.o $(STD)

pca.o:pca.cpp pca.h
	$(GPP) -c pca.cpp -o pca.o $(STD)
clean:
	@rm -f *.o pca

run:
	./pca
