CC=g++
CFLAG=-Ofast
EXE=./bin/kag_io.exe

Q := 1.1 1.5 2.0 2.5 3.0
RES := $(Q:%=./results/J%.txt)
PLT := $(RES:%.txt=%.png)


compile:$(EXE)

$(EXE):./src/kagomi_openmp.cpp
	$(CC) -o $(EXE) $(CFLAG) ./src/kagomi_openmp.cpp

%.txt:$(EXE)
	./bin/kag_io.exe $(@:./results/J%.txt=%) $@

result:$(RES)

%.png:%.txt
	python ./results/plot.py $(@:.png=.txt)

plot:$(PLT)
	echo $(PLT)

