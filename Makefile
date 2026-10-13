# Project
NAME	=	c-refactor-ls
OUT		=	ls.out

# Path
BUILD_DIR	?=	$(abspath ./build)
prefix		?=	/usr/local

# Tool
CC			?=	clang
RM			=	rm -rf
MKDIR		?=	mkdir -p

# File
HEADERS		=	$(shell find include -type f -name '*.h')
SRCS		=	$(shell find ls -type f -name '*.c')
OBJS		=	$(addprefix $(BUILD_DIR)/, $(SRCS:.c=.o))

# Option
CPPFLAGS	+=	-I./include -D_GNU_SOURCE
CFLAGS		+=	-std=gnu23 -Wall -Wextra -g -O2 -fvisibility=hidden
LDFLAGS		+=	
LDLIBS		+=	

all: $(BUILD_DIR) $(BUILD_DIR)/$(OUT)

$(BUILD_DIR):
	$(MKDIR) $@
$(BUILD_DIR)/$(OUT): $(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
$(BUILD_DIR)/%.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(BUILD_DIR)

.PHONY: all clean