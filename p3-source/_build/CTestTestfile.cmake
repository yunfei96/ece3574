# CMake generated Testfile for 
# Source directory: /vagrant
# Build directory: /vagrant/_build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unit "unittests")
add_test(test0 "vtray" "/vagrant/tests/scene0.json" "output0.png")
add_test(test1 "vtray" "/vagrant/tests/scene1.json" "output1.png")
add_test(test2 "vtray" "/vagrant/tests/scene2.json" "output2.png")
add_test(test3 "vtray" "/vagrant/tests/scene3.json" "output3.png")
set_tests_properties(test3 PROPERTIES  WILL_FAIL "ON")
add_test(test4 "vtray" "/vagrant/tests/scene4.json" "output4.png")
set_tests_properties(test4 PROPERTIES  WILL_FAIL "ON")
add_test(test0diff "perceptualdiff" "--sum-errors" "--output" "output0diff.png" "/vagrant/tests/scene0.png" "output0.png")
add_test(test1diff "perceptualdiff" "--threshold" "200000" "--sum-errors" "--output" "output1diff.png" "/vagrant/tests/scene1.png" "output1.png")
add_test(test2diff "perceptualdiff" "--threshold" "400000" "--sum-errors" "--output" "output2diff.png" "/vagrant/tests/scene2.png" "output2.png")
