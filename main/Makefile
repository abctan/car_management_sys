CFILES:= main.c

HFILES:= $(ROOTDIR)/source/sys

COBJS := $(CFILES:.c=.o)
OBJS  := $(addprefix $(OUTPUT)/, $(COBJS))
CFLAGS += $(patsubst %,-I%,$(HFILES))

all: $(OBJS)

$(OUTPUT)/%.o: %.c
	$(Q)$(CC) -c $(CFLAGS) $^ -o $(OUTPUT)/$(notdir $@)
	$(if $(Q), $(Q)$(info CC   $^))
