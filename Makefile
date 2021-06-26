M_FILE=`ls Makefile_*`
all:
	for file in $(M_FILE);\
		 do\
		 $(MAKE) -f $$file;\
		 done
clean:
	for file in $(M_FILE);\
		 do\
		 $(MAKE) clean -f $$file;\
		 done



