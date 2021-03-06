if (DEPENDENCY_PHASE)
	find_package (yaml-cpp QUIET 0.5)
	if (NOT YAML-CPP_FOUND)
		remove_plugin (yamlcpp "yaml-cpp (libyaml-cpp-dev >= 0.5) not found")
	else (NOT YAML-CPP_FOUND)
		if (YAML-CPP_VERSION VERSION_LESS "0.6.0")
			find_package (Boost QUIET)
			if (NOT Boost_FOUND)
				remove_plugin (yamlcpp "yaml-cpp ${YAML-CPP_VERSION} requires Boost")
			endif (NOT Boost_FOUND)
			# Disable warnings about shadow declarations in yaml-cpp source code
			if (APPLE AND CMAKE_COMPILER_IS_GNUCXX)
				string (REPLACE "-Wshadow" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
			endif (APPLE AND CMAKE_COMPILER_IS_GNUCXX)
		set (YAML_PLUGIN_INCLUDE_DIRS ${Boost_INCLUDE_DIR})
		endif (YAML-CPP_VERSION VERSION_LESS "0.6.0")
	endif (NOT YAML-CPP_FOUND)

	set (YAML_PLUGIN_INCLUDE_DIRS ${YAML_PLUGIN_INCLUDE_DIRS} ${YAML-CPP_INCLUDE_DIR})
endif (DEPENDENCY_PHASE)

add_plugin (yamlcpp
	CPP
	ADD_TEST
	INSTALL_TEST_DATA
	SOURCES
		yamlcpp.hpp yamlcpp.cpp
		read.hpp read.cpp
		write.hpp write.cpp
	INCLUDE_DIRECTORIES
		${YAML_PLUGIN_INCLUDE_DIRS}
	LINK_LIBRARIES
		${YAML-CPP_LIBRARIES}
	LINK_ELEKTRA
		elektra-ease
	)
