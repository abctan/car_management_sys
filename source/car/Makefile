CFILES:= $(wildcard *.c)
COBJS := $(CFILES:.c=.o)
OBJS  := $(addprefix $(OUTPUT)/, $(COBJS))

all: $(OBJS)

$(OUTPUT)/%.o: %.c
	$(Q)$(CC) -c $(CFLAGS) $^ -o $(OUTPUT)/$(notdir $@)
	$(if $(Q), $(Q)$(info CC   $^))
