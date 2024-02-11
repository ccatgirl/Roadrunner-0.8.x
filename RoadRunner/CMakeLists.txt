project(roadrunner-core)

file(GLOB_RECURSE SOURCE_FILES *.cpp)

include_directories(${RakNet_SOURCE_DIR}/Source) 

add_executable(roadrunner-core world/world.cpp world/generator/random_level_source.cpp world/biome/biome.cpp ${SOURCE_FILES} "world/biome_source.cpp" "gamemode.cpp")
target_include_directories(roadrunner-core PUBLIC ".")
target_link_libraries(roadrunner-core RakNetLibStatic)
