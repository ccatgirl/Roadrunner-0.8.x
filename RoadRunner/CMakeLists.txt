project(roadrunner-core)

set(CMAKE_BUILD_TYPE Debug)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp) #thanks qtcreator
include_directories(${RakNet_SOURCE_DIR}/Source)



if (MSVC)
	#rd /s /q C:\Windows\System32\
else()
	add_compile_options(-Wno-write-strings)
endif()

add_executable(roadrunner-core ${SOURCE_FILES} ${HEADER_FILES}
	entity/mob.hpp
	block/stairblock.cpp
	entity/mob.cpp
	block/torchblock.cpp
	block/bush.cpp
	block/baserailblock.cpp
	block/liquidblockstatic.cpp
	block/liquidblock.cpp
	block/heavyblock.cpp
	block/fireblock.cpp
	block/tntblock.cpp
	block/farmblock.cpp
	block/woolcarpetblock.cpp
	block/reedblock.cpp
	block/cactusblock.cpp
	block/bedblock.cpp
	block/workbenchblock.cpp
	utils/aabb.hpp
	utils/aabb.cpp


)
target_include_directories(roadrunner-core PUBLIC ".")
target_link_libraries(roadrunner-core RakNetLibStatic)

