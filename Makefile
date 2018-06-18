CC=g++
CFLAG=-Ofast -std=c++11
EXE=./bin/kag_io.exe

Q := 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 
RES := $(Q:%=./results/J%.txt)
PLT := $(RES:%.txt=%.png)


compile:$(EXE)

$(EXE):./src/kagomi_openmp.cpp
	$(CC) -o $(EXE) $(CFLAG) ./src/kagomi_openmp.cpp

%.txt:$(EXE)
	./bin/kag_io.exe $(@:results/J%.txt=%) $@

result:$(RES)

%.png:%.txt
	python ./results/plot.py $(@:.png=.txt)

plot:$(PLT)
	echo $(PLT)

