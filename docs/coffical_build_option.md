#

##
- https://github.com/sony/easyhttpcpp/wiki/Build-options
##
Build options
Himanshu Shekhar edited this page on 5 Oct 2017 · 1 revision
By default the library is built as a static library in Release mode (fit for production use). Also to speed up build time, test suites, docs and samples are not build by default.

Building library in debug mode
cmake -DCMAKE_BUILD_TYPE=Debug ../
make install
Building as shared library
cmake -DFORCE_SHAREDLIB=ON ../
make install
Building test suites
cmake -DENABLE_TESTS=ON ../
make install
Test suite runners are present inside ${CMAKE_BINARY_DIR}/bin as easyhttp-IntegrationTestRunner & easyhttp-UnitTestRunner for running integration tests and unit tests respectively.

Building docs
cmake -DENABLE_DOCS=ON ../
make doc
Doxygen api doc will be created inside ${CMAKE_INSTALL_PREFIX}/doc/api.
