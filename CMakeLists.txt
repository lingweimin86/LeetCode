# CMakeList.txt : CMake project for MyCode, include source and define
# project specific logic here.
#


cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
#if (POLICY CMP0141)
#  cmake_policy(SET CMP0141 NEW)
#  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
#endif()

project ("MyCode")

# add_compile_options(-g)

# Add source to this project's executable.
add_executable (MyCode "MyCode.cpp" "MyCode.h" "Array_NumsOfTheSum.h" "MergeTwoArrays.h" "List_MergeTwoLists.h" "List_IsCircle.h" "List_GetIntersectionNode.h" "ReverseList.h" "List_FindLastNode.h" "Stack_DecodeString.h" "Sort.h" "Bit_FindNumAppearOnce.h" "Bit_CountBit.h" "String_AddTwoString.h" "String_Compare.h" "DynamicProgramming.h" "DP.h" "Heap.h" "List_sortOnBase.h" "BiTree_BST.h" "island.h" "String_KWP.h" "String_Manacher.h" "SlideWindow.h" "Stack_OrderStack.h" "DataCleaning.h" "Washer.h" "Tree.h" "Bucket.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MyCode PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
