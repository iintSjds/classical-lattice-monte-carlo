CC=g++
CFLAG=-Ofast
EXE=./bin/kag_io.exe

Q := 0.97 1.48 1.71 1.73
RES := $(Q:%=./results/J%.txt)
PLT := $(RES:%.txt=%.png)


compile:$(EXE)

$(EXE):./src/kagomi.cpp
	$(CC) -o $(EXE) $(CFLAG) ./src/kagomi.cpp

%.txt:$(EXE)
	./bin/kag_io.exe $(@:results/J%.txt=%) $@

result:$(RES)

%.png:%.txt
	python ./results/plot.py $(@:.png=.txt)

plot:$(PLT)
	echo $(PLT)

