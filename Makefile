CROSS_COMPILE 	?=
TARGET		  	?= car

CC 				:= $(CROSS_COMPILE)gcc
LD				:= $(CROSS_COMPILE)ld

INCDIRS 		:= common \
                   source/car
				   
				   			   
SRCDIRS			:= project \
				   common  \
				   source/car \

				   
				   
INCLUDE			:= $(patsubst %,-I%, $(INCDIRS))

CFILES			:= $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))

CFILENDIR		:= $(notdir  $(CFILES))

OBJS			:= $(patsubst %, obj/%, $(CFILENDIR:.c=.o))

VPATH			:= $(SRCDIRS)

.PHONY: clean


$(TARGET) : $(OBJS)
	$(CC) $^ -o $@
$(OBJS) : obj/%.o : %.c
	$(CC) -c $< $(INCLUDE) -o $@ 
	
clean:
	rm -rf $(OBJS) $(TARGET)
	
