project(roadrunner-core)

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
	block/torchblock.cpp)
target_include_directories(roadrunner-core PUBLIC ".")
target_link_libraries(roadrunner-core RakNetLibStatic)

