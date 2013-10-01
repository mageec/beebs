include ../common.mk

SRC = sha.c sha_driver.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix sha, $@)

clean:
	rm -f *.o *_sha

# vim: set ts=4 sw=4 noet:
