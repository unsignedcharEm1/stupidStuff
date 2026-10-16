# Configuration
CC := gcc

# File config
TARGET := head

SRCS := main.c numutil.c

OBJS := $(SRCS:.c=.o)

DEPS := $(SRCS:.c=.d)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -MMD -MP -c -o $@ $<

.PHONY: clean

clean:
	rm -rf $(TARGET) $(OBJS) $(DEPS)

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPS)
endif
