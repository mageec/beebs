include ../common.mk

SRC = dijkstra_small.c

%_:
	$($(addprefix $@, CC)) $($(addprefix $@, FLAGS)) $($(addprefix $@, SRC)) $(SRC) -o $(addsuffix dijkstra, $@)

clean:
	rm -f *.o *_dijkstra

# vim: set ts=4 sw=4 noet:
