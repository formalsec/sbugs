SYMBOLIC := symbolic
FILTER := $(SYMBOLIC) Makefile
SUBDIRS := $(filter-out $(FILTER) , $(shell ls ./ | sort -n))

.PHONY: all symbolic
all: $(SUBDIRS)

$(SUBDIRS): symbolic
	
ifeq ($(pre),true)
	+$(MAKE) -C $@ pre -s
else
	+$(MAKE) -C $@ -s
endif

symbolic:
	+$(MAKE) -C $(SYMBOLIC) -s

clean: 
	find -name \*.exe -type f -delete
	find -name \*.o -type f -delete
	find -name \*.bc -type f -delete
	

