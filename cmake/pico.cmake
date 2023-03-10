message("found pico.cmake")

#set(CMAKE_SYSTEM_NAME Generic)
message(${CMAKE_SYSTEM_NAME})

enable_language( C CXX ASM )

# Include the Pico SDK cmake file
# Include the subsidiary .cmake file to get the SDK
list(APPEND CMAKE_MODULE_PATH "/Users/mike/development/pico-sdk/external")
include(pico_sdk_import)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

#set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -O3 -mcpu=cortex-a7 -mfloat-abi=hard -mfpu=neon-vfpv4")

# Link the Project to a source file (step 4.6)
add_executable(${OUTPUT_NAME}
    src/main.cpp
    src/perlin.cpp
    src/pixel.cpp
    src/util.cpp)

# Link the Project to an extra library (pico_stdlib)
target_link_libraries(${OUTPUT_NAME}
    pico_stdlib
    pico_multicore
)

# Initalise the SDK
pico_sdk_init()

pico_add_extra_outputs(${OUTPUT_NAME})
pico_set_float_implementation(${OUTPUT_NAME} pico)
