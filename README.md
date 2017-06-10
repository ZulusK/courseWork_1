#Facecope#
### The photo management program ###

_[Technical documentation](https://docs.google.com/document/d/1uAafzIcO1uX_CPPadWWjw2VOkqY7Sk7aB99loCDafI4/edit?usp=sharing)_

__Facecope__ is a desktop application for control and management image files stored in the user's local file system. It will automate indexing user-selected photos by different criteria

1. registered face in the photo
2. time of creation
3. geotag
4. template name
5. etc.

As mentioned above, the main purpose Facecope - automation of routine management of images, browsing, organizing and limited photo editing, indexing them on your hard drive.

### Supporting platforms
Linux Ubuntu
MacOS

### Before start
* ##### Install gtk+3 
 `sudo apt-get install libgtk-3-dev`
* ##### Install opencv2:
`git clone https://github.com/opencv/opencv.git`
`cd ~/opencv`
`mkdir release`
`cd release`
`cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..`


