add_library( ${LIB_NAME} SHARED
	ivi-logging.cpp
	backtrace.cpp
	${DLT_LIBRARY_FILES}
)

set_target_properties(${LIB_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${PROJECT_MAJOR_VERSION})

TARGET_LINK_LIBRARIES( ${LIB_NAME}
  ${DLT_LIBRARIES}
  ${CPP_LIBS}
  Threads::Threads
)

INSTALL(TARGETS ${LIB_NAME}
  DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
