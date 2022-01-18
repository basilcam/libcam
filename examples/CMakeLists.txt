
add_executable(ex_waitpid_nondeterministic waitpid_nondeterministic.c)
target_link_libraries(ex_waitpid_nondeterministic PRIVATE cam)

add_executable(ex_waitpid_deterministic waitpid_deterministic.c)
target_link_libraries(ex_waitpid_deterministic PRIVATE cam)

add_executable(ex_print_args print_args.c)
target_link_libraries(ex_print_args PRIVATE cam)

add_executable(ex_update_args update_args.c)
target_link_libraries(ex_update_args PRIVATE cam)

add_executable(ex_linked_list data/linked_list.c)
target_link_libraries(ex_linked_list PRIVATE cam)

