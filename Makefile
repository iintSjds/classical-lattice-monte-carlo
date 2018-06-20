CC=g++
CFLAG=-Ofast -std=c++11
EXE=./bin/kag_io.exe

Q := 0.1 0.2 0.25 6.5 7.0 7.5 8.0
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

