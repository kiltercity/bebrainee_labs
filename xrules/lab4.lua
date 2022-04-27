add_rules("mode.debug", "mode.release")



target("lab4_jibberish")
    set_kind("binary")
    add_files("$(projectdir)/src/lab4/task1_jibberish_hashtable.c")
    add_deps("ht")


target("lab4_task1")
    set_kind("binary")
    add_files("$(projectdir)/src/lab4/task_4.1_VRP.c")
    add_deps("ht")
    add_deps("hs")



target("l4_utils")
    set_kind("shared")
    add_files("$(projectdir)/include/lab4/lab4_utils.c")
    add_files("$(projectdir)/include/hashtable/hashtable.c")
    
target("lab4_task2")
    set_kind("binary")
    add_files("$(projectdir)/src/lab4/task_4.2_Autobus.c")
    -- add_files("src/include/lab4/lab4_utils.c")
    -- add_files("include/hashtable/hashtable.c") 
    add_deps("ht")
    add_deps("l4_utils")