
add_executable(waitpid1 waitpid1.c)
target_link_libraries(waitpid1 PRIVATE libcam)

add_executable(waitpid2 waitpid2.c)
target_link_libraries(waitpid2 PRIVATE libcam)

add_executable(print-args print-args.c)
target_link_libraries(print-args PRIVATE libcam)

add_executable(update-args update-args.c)
target_link_libraries(update-args PRIVATE libcam)

