SUBDIRS = mySimpleComputer myTerm myBigChars myReadkey console # simpleassembler simplebasic

TEST_OBJ = mySimpleComputer/obj/*.o

DO_MAKE = for dir in $(SUBDIRS); do $(MAKE) -C $$dir $@; done

all: $(SUBDIRS)

rebuild: clean $(SUBDIRS)

run:
	@./console/console.out

$(SUBDIRS):
	@echo "--------------------------------------- START BUILD ---------------------------------------"
	$(MAKE) -C $@ 
	@echo "--------------------------------------- FINISH BUILD --------------------------------------"

clean:
	@echo "--------------------------------------- START CLEAN ---------------------------------------"
	@$(DO_MAKE)
	@echo "--------------------------------------- FINISH CLEAN --------------------------------------"

test: $(SUBDIRS)
	@echo "--------------------------------------- START TEST ----------------------------------------"
	@$(DO_MAKE)
	@echo "--------------------------------------- FINISH TEST ---------------------------------------"

.PHONY: all rebuild run clean test $(SUBDIRS)

