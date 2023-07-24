CFILES := 	drv_db.c

OUTPUT ?= .
NOTDIR_CFILES := $(notdir $(CFILES))
COBJS := $(NOTDIR_CFILES:.c=.o)
OBJS  := $(addprefix $(OUTPUT)/, $(COBJS))
VPATH := $(sort $(dir $(CFILES)))


all: $(OBJS)

$(OUTPUT)/%.o: %.c
	$(Q)$(CC) -c $(CFLAGS) $^ -o $@
	$(if $(Q), $(Q)$(info CC   $^))