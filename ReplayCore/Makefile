CC = g++
OBJS = ./main.cpp ./*/*.cpp 
LINK_INCLUDES = -L./*/*.h 
LINKER_FLAGS = -Wno-narrowing -lssl -lcrypto -lz -lmariadb
OBJ_NAME = replayCore
all : $(OBJS)
	$(CC)  $(OBJS) $(LINK_INCLUDES) $(LINKER_FLAGS) -o $(OBJ_NAME)
clean:
	$(RM) count *.o *~ $(OBJ_NAME)
