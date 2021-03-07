function plugin_create()
	io.write("    lua created\n")
end

function plugin_destroy()
	io.write("    lua destroyed\n")
end

function plugin_name()
	return "lua"
end

counter = 0

function plugin_test()
	io.write("    lua tested " .. counter .. " times\n")
	counter = counter + 1
end

