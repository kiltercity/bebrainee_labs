CC=clang
CMD_MKDIR=mkdir -p



# --- DIRS 
# -----------------

BIN_DIR=bin/
LIB_DIR=libs/
INCLUDE=include/
TEST_DIR=tests/

# -----------------

LIBS_LIST=$(INCLUDE)/hashtable/hashtable.c $(INCLUDE)/unity/unity.c 




#= / Common prerequisites /
#=============================================================================
dirs:
	@echo "Creating directories..."
	@$(CMD_MKDIR) $(BIN_DIR) $(LIB_DIR)

#= / RULES /
#=============================================================================
all: dirs


hashtable_lib: $(INCLUDE)/hashtable/hashtable.c
	@clang -fPIC -shared $< \
			-o $(LIB_DIR)hashtable.so 

hashset_lib: $(INCLUDE)/hashtable/hashset.c
	@clang -fPIC -shared $< \
			-o $(LIB_DIR)hashset.so

libs: dirs hashtable_lib hashset_lib
	@echo "Building libs done!"

lab1_1: src/lab1/task1.c dirs
	@clang $< -o $(BIN_DIR)$@.bin

lab1_2: src/lab1/task2.c dirs
	@clang $< -o $(BIN_DIR)$@.bin

lab2_1: src/lab2/task1.c dirs
	clang $< -o $(BIN_DIR)$@.bin

lab3_queue: src/lab3/queue.c src/lab3/task1_1_queue.c
	@clang $^ -o $(BIN_DIR)$@.bin

lab3_stack: src/lab3/stack.c src/lab3/task2_stack.c
	@clang $^ -o $(BIN_DIR)$@.bin

lab4_hash: include/hashtable/hashtable.c src/lab4/task1_hashtable.c 
	@clang -Iinclude/ $^ -o $(BIN_DIR)$@.bin


#= / BUILD & RUN /
#=============================================================================

run_l11: lab1_1
	@ ./bin/lab1_1.bin

run_l12: lab1_2
	@ ./bin/lab1_2.bin

run_l3_queue: dirs lab3_queue
	@ ./bin/lab3_queue.bin

run_l3_stack: dirs lab3_stack
	@ ./bin/lab3_stack.bin

run_l4_hashtable: dirs lab4_hash
	@ ./bin/lab4_hash.bin



#= / TESTS /
#=============================================================================
test_lab4_hashtable: dirs
	@clang -Iinclude/ \
		include/unity/unity.c \
		include/hashtable/hashtable.c \
		$(TEST_DIR)test_hashtables.c \
			-o $(BIN_DIR)hashtables.bin

test_lab4_hashset: dirs
	@echo " ---------------------- "
	@echo -e "Building lab4 - Hash Set Tests"
	@clang -Iinclude/ \
		include/unity/unity.c \
		include/hashtable/hashtable.c \
		include/hashtable/hashset.c \
		$(TEST_DIR)test_hashset.c \
			-o $(BIN_DIR)lab4_hashsets.bin
	@echo -e "Done! Executable can be found: ./bin/lab4_hashsets.bin"
	@echo " ---------------------- "

clean:
	@echo "Cleaning stuff"
	@rm -rf $(BIN_DIR) $(LIB_DIR)


.PHONY: dirs 
