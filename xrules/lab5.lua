add_rules("mode.debug", "mode.release")


target("lab5_task1")
    add_deps("graphs")
    add_files("$(projectdir)/src/lab5/lab5_task1.c")