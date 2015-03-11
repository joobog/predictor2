project ( Predictor )

add_library ( prediction SHARED
	functions.cpp
	)

target_link_libraries ( prediction
	-L${Shogun_LIBDIR}
	libshogun.so
  )

install (FILES NeuralNetwork.hpp DESTINATION ${KE_INSTALL_INCLUDE_DIR})
install (FILES CART.hpp DESTINATION ${KE_INSTALL_INCLUDE_DIR})
install (FILES functions.hpp DESTINATION ${KE_INSTALL_INCLUDE_DIR})
install (TARGETS prediction LIBRARY DESTINATION ${KE_INSTALL_LIBRARY_DIR})

add_subdirectory( test )
