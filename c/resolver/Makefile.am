include ../../../../oracc-am-rules.txt

subdirs=ccgi

.g.c:
	gperf -N `basename $*` -tT $< >$@

AM_CFLAGS=-ansi -pedantic -Wall -g \
	-I@top_srcdir@/c/lib/expat/xmlparse

AM_CPPFLAGS=-I@top_srcdir@/c/include -Wall -pedantic -ansi

cgibin_PROGRAMS=oracc-server

# noinst_PROGRAMS=content_test
# content_test_SOURCES=content_test.c content.c runexpat.c
# content_test_LDADD=ccgi/libccgi.la -lexpat

oracc_server_SOURCES=oracc-server.c or_builtins.c or_stable_uris.c \
	selections.c builtins.c or_response.c or_common.c xmlrpc.c \
	or_gdf.c or_pqx.c pqx_map.c pqx_h_tab.c ncname.c p3.c listdir.c \
	sl.c content.c runexpat.c

oracc_server_LDADD=ccgi/libccgi.la -lexpat

ccgi/libccgi.la:
	(cd ccgi ; make)

or_builtins.c: or_builtins.c.in
	$(ORACCIFY) or_builtins.c.in

or_common.c: or_common.c.in
	$(ORACCIFY) or_common.c.in

or_gdf.c: or_gdf.c.in
	$(ORACCIFY) or_gdf.c.in

or_pqx.c: or_pqx.c.in
	$(ORACCIFY) or_pqx.c.in

oracc-server.c: oracc-server.c.in ccgi/libccgi.la
	$(ORACCIFY) oracc-server.c.in

or_response.c: or_response.c.in
	$(ORACCIFY) or_response.c.in

or_stable_uris.c: or_stable_uris.c.in
	$(ORACCIFY) or_stable_uris.c.in

p3.c: p3.c.in
	$(ORACCIFY) p3.c.in

pqx_map.c: pqx_map.c.in
	$(ORACCIFY) pqx_map.c.in

xmlrpc.c: xmlrpc.c.in
	$(ORACCIFY) xmlrpc.c.in

EXTRA_DIST=*.h
