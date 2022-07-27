add_rules("mode.debug", "mode.release")


set_symbols('debug')

target("lab5_task1")
    add_deps("hs")
    add_deps("graphs")
    add_files("$(projectdir)/src/lab5/lab5_task1.c")