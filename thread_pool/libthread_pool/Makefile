# Libthread_pool Makefile
targets := libthread_pool.a
objs	:= thread_pool.o

CC	:= gcc
CFLAGS	:= -Wall -Werror
CFLAGS	+= -g
PANDOC	:= pandoc

ifneq ($(V),1)
Q = @
endif

all: $(targets)

deps := $(patsubst %.o,%.d,$(objs))
-include $(deps)
DEPFLAGS = -MMD -MF $(@:.o=.d)

libthread_pool.a: $(objs)
	@echo "CC $@"
	ar rcs libthread_pool.a $(objs)

%.o: %.c
	@echo "CC $@"
	$(Q)$(CC) $(CFLAGS) -c -o $@ $< $(DEPFLAGS)

clean:
	@echo "clean"
	$(Q)rm -f $(targets) $(objs) $(deps)

