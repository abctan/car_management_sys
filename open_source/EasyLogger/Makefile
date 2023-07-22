CFILES := 	easylogger/src/elog.c \
			easylogger/src/elog_utils.c \
			easylogger/port/elog_port.c

COBJS := $(CFILES:.c=.o)
OBJS  := $(addprefix $(OUTPUT)/, $(COBJS))

all: $(OBJS)

$(OUTPUT)/%.o: %.c
	$(Q)$(CC) -c $(CFLAGS) $^ -o $(OUTPUT)/$(notdir $@)
	$(if $(Q), $(Q)$(info CC   $^))
