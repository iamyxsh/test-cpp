# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-src")
  file(MAKE_DIRECTORY "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-src")
endif()
file(MAKE_DIRECTORY
  "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-build"
  "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-subbuild/fmt-populate-prefix"
  "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-subbuild/fmt-populate-prefix/tmp"
  "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
  "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-subbuild/fmt-populate-prefix/src"
  "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/iamyxsh/Personal/test-cpp/bui/_deps/fmt-subbuild/fmt-populate-prefix/src/fmt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
