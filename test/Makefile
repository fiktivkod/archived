# Test makefile

CC		= gcc
CFLAGS  = -g -D__DEBUG__
LD      = $(CC)
LDFLAGS =

include ../Makefile.include

ROOT = ../
TESTS = $(patsubst t_%.c,%,$(wildcard t_*.c))

# workaround to force make not to remove "intermediate" files
# (that apperantly make decided *.o files was :)
.SECONDARY:

.PHONY : clean
all : $(TESTS)

strbuf : unit.c $(addprefix $(ROOT),$(obj-strbuf))
rbtree : unit.c $(addprefix $(ROOT),$(obj-rbtree))
queue : $(ROOT)src/queue.o $(addprefix $(ROOT),$(obj-xalloc))
path : unit.c $(addprefix $(ROOT),$(obj-path))
fscrawl : $(ROOT)src/fscrawl.o $(addprefix $(ROOT),$(obj-fscrawl))
notify : $(addprefix $(ROOT),$(obj-notify))
inotify-map : $(addprefix $(ROOT),$(obj-inotify-map))
inotify-watch : $(addprefix $(ROOT), $(obj-xalloc)) $(addprefix $(ROOT), $(obj-path)) $(ROOT)src/tree.o ../src/inotify-watch.o
log : $(addprefix $(ROOT),$(obj-log))
tree : $(addprefix $(ROOT),$(obj-xalloc)) $(ROOT)src/tree.o
list : $(addprefix $(ROOT),$(obj-list))
str-list : unit.c $(addprefix $(ROOT),$(obj-str-list))

clean :
	$(RM) $(patsubst t_%.c,test_%,$(wildcard t_*.c))
	$(RM) *.o

% : t_%.o
	$(QUIET_LD)$(LD) $(LDFLAGS) $(sort $(^)) -o test_$@

%.o : %.c
	$(QUIET_CC)$(CC) $(CFLAGS) -c $< -o $@
