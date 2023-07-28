file(GLOB ITEMS ${CMAKE_CURRENT_SOURCE_DIR}/*)

FOREACH(item ${ITEMS})
    if(IS_DIRECTORY ${item})
        file(RELATIVE_PATH relpath ${CMAKE_CURRENT_SOURCE_DIR} ${item})

        # message("Year located: " ${relpath})
        file(GLOB DAYS ${item}/*)

        FOREACH(day ${DAYS})
            file(RELATIVE_PATH dayName ${item} ${day})

            string(CONCAT fullName ${relpath} "_" ${dayName})

            # message(STATUS "DAY: " ${fullName})
            file(GLOB_RECURSE SOURCES
                ${day}/*.cpp
                ${day}/*.hpp
            )

            # message(STATUS "Sources: ${SOURCES}")
            add_executable(${fullName} ${SOURCES})
            target_compile_definitions(${fullName} PRIVATE SOURCE_PATH="${day}")
        ENDFOREACH()
    ENDIF()
ENDFOREACH()
