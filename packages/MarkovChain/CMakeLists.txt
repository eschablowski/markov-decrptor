find_package(GMP REQUIRED)

set(MarkovChain_SRCS src/MarkovChain.cpp src/Extractor.cpp)

add_library(MarkovChain ${MarkovChain_SRCS})
target_include_directories(MarkovChain PUBLIC include)

target_link_libraries(MarkovChain PUBLIC ${GMP_LIBRARY})
