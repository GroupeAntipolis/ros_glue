#delete old libs and headers

rm ../include/*.h
rm ../include/*.cpp
rm ../libglue/*.a

# add headers
cp ~/prog/Projects/LIBRARIES/CPP/glue/*.h ~/catkin_ws/src/ros_glue/include/
cp ~/prog/Projects/LIBRARIES/CPP/rng/*.h ~/catkin_ws/src/ros_glue/include/
cp ~/prog/Projects/LIBRARIES/CPP/SmartDataCPP/*.h ~/catkin_ws/src/ros_glue/include/

# add libs
cp ~/prog/Projects/LIBRARIES/CPP/glue/bin/Release/*.a ~/catkin_ws/src/ros_glue/libglue/
cp ~/prog/Projects/LIBRARIES/CPP/rng/bin/Release/*.a ~/catkin_ws/src/ros_glue/libglue/
cp ~/prog/Projects/LIBRARIES/CPP/SmartDataCPP/bin/Release/*.a ~/catkin_ws/src/ros_glue/libglue/