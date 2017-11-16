# Asaf Rosemarin 
# 211544846
# Ben Cohen
# Add your ID here 

CPP_FILES = $(shell find . -name "*.cpp")
H_FILES = $(shell find . -name "*.h")
O_FILES = $(shell find . -name "*.o")

a.out: compile
	g++ $(O_FILES)
compile: $(CPP_FILES) $(H_FILES)
	g++ -c $(CPP_FILES)
clean:
	rm $(O_FILES)


