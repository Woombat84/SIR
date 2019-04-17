# SIR
Sewer fault detection P4 project
A projct for detecting faults within the sewer.



Hardware use: Intel RealSense d435i


What works so far is a skeleton setup before any prossecing.
Depth, IR and RGB are displayed, the IMU data is printed to the console.

Software needed : Intel RealSence SDK
                  A cpp comipler as visual studio
                  
                  
                  
A note : If you get and error regarding a path do the following 
         1.find Project1.vcxproj
         2.open with notepad or any plain text editor
         3.locate this  </ImportGroup>
                        <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
                        <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
                        <Import Project="intel.realsense.props" />
                        <Import Project="opencv.props" />
                        </ImportGroup>
                        note: their maybe a morre path's with in this structur
         4.delete everhting between </ImportGroup> EXCEPT the two top lines
         5.save    the end result should look like this:
                        </ImportGroup>
                        <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
                        <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
                        </ImportGroup>
