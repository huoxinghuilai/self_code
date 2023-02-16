# Target programs
programs := \
	test.x

# User-level thread_pool library
THREAD_POOL_LIB := libthread_pool
THREAD_POOL_PATH := $(THREAD_POOL_LIB)
libthread_pool := $(THREAD_POOL_PATH)/${THREAD_POOL_LIB}.a

# Default rule
all: $(libthread_pool) $(programs)

# Avoid builtin rules and variables
MAKEFLAGS += -rR

# Don't print the command unless explicitely requested with 'make V=1'
ifneq ($(V),1)
Q = @
V = 0
endif

# Define compilation toolchain
CC	= gcc

# General gcc options
CFLAGS := -Wall -Werror
CFLAGS += -pipe
## Debug flag
ifneq ($(D),1)
CFLAGS += -O2
else
CFLAGS += -O0
CFLAGS += -g
endif

# Include path
INCLUDE := -I$(THREAD_POOL_PATH)

# Application objects to compile
objs := $(patsubst %.x,%.o,$(programs))

# Include dependencies
deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)

# Rule for libthread_pool.a
$(libthread_pool):
	@echo "MAKE	$@"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(THREAD_POOL_PATH)

# Generic rule for linking final application
%.x: %.o $(libthread_pool)
	@echo "LD	$@"
	$(Q)$(CC) $(CFLAGS) -o $@ $< -L$(THREAD_POOL_LIB) -lthread_pool -lpthread

# Generic rule for compiling objects
%.o: %.c
	@echo "CC	$@"
	$(Q)$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $< $(DEPFLAGS)

# Cleaning rule
clean:
	@echo "CLEAN	$(shell pwd)"
	$(Q)$(MAKE) V=$(V) D=$(D) -C $(THREAD_POOL_PATH) clean
	$(Q)rm -rf $(objs) $(deps) $(programs)

.PHONY: clean $(libthread_pool)

