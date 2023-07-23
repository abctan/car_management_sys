CFILES := 	easylogger/src/elog.c \
			easylogger/src/elog_utils.c \
			easylogger/port/elog_port.c

OUTPUT ?= .
NOTDIR_CFILES := $(notdir $(CFILES))
COBJS := $(NOTDIR_CFILES:.c=.o)
OBJS  := $(addprefix $(OUTPUT)/, $(COBJS))
VPATH := $(sort $(dir $(CFILES)))


all: $(OBJS)

$(OUTPUT)/%.o: %.c
	$(Q)$(CC) -c $(CFLAGS) $^ -o $@
	$(if $(Q), $(Q)$(info CC   $^))

test:
	@echo "$(OBJS)"
	@echo "$(CFILES)"
	@echo "$(notdir $(CFILES))"
	@echo "$(VPATH)"
	@echo "$(dir $(CFILES))"
	@echo "$(sort $(dir $(CFILES)))"