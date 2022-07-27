add_includedirs("$(projectdir)/include")


target("ht")
    set_kind("static")
    add_files("$(projectdir)/include/hashtable/hashtable.c") 
    -- add_includedirs("$(projectdir)/include/", {public = true})


target("hs")
    set_kind("shared")
    add_files("$(projectdir)/include/hashtable/hashtable.c")
    add_files("$(projectdir)/include/hashtable/hashset.c")
    -- add_includedirs("include/", {public = true})

    -- add_rules("utils.symbols.export_all")


target("graphs")
    set_kind("shared")
    add_files("$(projectdir)/include/graphs/graph.c")



includes("xrules/lab4.lua")
includes("xrules/lab5.lua")