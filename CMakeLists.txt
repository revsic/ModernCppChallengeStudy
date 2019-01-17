
cmake_minimum_required(VERSION 3.1)

project(ModernCppChallenge LANGUAGES CXX)

set(CMAKE_MODULE_PATH       ${CMAKE_SOURCE_DIR}/Scripts)
set(ROOT_DIR                ${CMAKE_SOURCE_DIR})
set(CMAKE_INSTALL_PREFIX    ${CMAKE_SOURCE_DIR}/Solved)
set(CMAKE_CXX_STANDARD      17)

include(GetModules)

# add_subdirectory(Math)          # Ch.1 done
# add_subdirectory(Language)      # Ch.2 done
# add_subdirectory(Regex)         # Ch.3 done
# add_subdirectory(Filesystem)    # Ch.4 done
# add_subdirectory(DateTime)      # Ch.5 done
# add_subdirectory(Algorithm)     # Ch.6 done
# add_subdirectory(Concurrency)   # Ch.7 done
# add_subdirectory(DesignPattern) # Ch.8 
# add_subdirectory(Serialization) # Ch.9
# add_subdirectory(Archives)      # Ch.10
# add_subdirectory(Database)      #
# add_subdirectory(Images)        # 
# add_subdirectory(Cryptography)  # Ch.11 done
add_subdirectory(Networking)    # Ch.12

# add_subdirectory(Extra)         # Bonus challenge!
