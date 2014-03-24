include_directories( ./include/lsd )
set(
	lsd_SOURCE
	src/lsd.c
)

add_library(lsd ${lsd_SOURCE})