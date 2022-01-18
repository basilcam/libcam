
add_executable(waitpid_nondeterministic waitpid_nondeterministic.c)
target_link_libraries(waitpid_nondeterministic PRIVATE cam)

add_executable(waitpid_deterministic waitpid_deterministic.c)
target_link_libraries(waitpid_deterministic PRIVATE cam)

add_executable(print_args print_args.c)
target_link_libraries(print_args PRIVATE cam)

add_executable(update_args update_args.c)
target_link_libraries(update_args PRIVATE cam)

