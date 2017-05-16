# CMake generated Testfile for 
# Source directory: /Users/YunfeiGuo/Desktop/ece3574/p3-source
# Build directory: /Users/YunfeiGuo/Desktop/ece3574/p3-build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit "unittests")
add_test(test0 "vtray" "/Users/YunfeiGuo/Desktop/ece3574/p3-source/tests/scene0.json" "output0.png")
add_test(test1 "vtray" "/Users/YunfeiGuo/Desktop/ece3574/p3-source/tests/scene1.json" "output1.png")
add_test(test2 "vtray" "/Users/YunfeiGuo/Desktop/ece3574/p3-source/tests/scene2.json" "output2.png")
add_test(test3 "vtray" "/Users/YunfeiGuo/Desktop/ece3574/p3-source/tests/scene3.json" "output3.png")
set_tests_properties(test3 PROPERTIES  WILL_FAIL "ON")
add_test(test4 "vtray" "/Users/YunfeiGuo/Desktop/ece3574/p3-source/tests/scene4.json" "output4.png")
set_tests_properties(test4 PROPERTIES  WILL_FAIL "ON")
