
# How to run sdkbox samples

**NOTE**: PhunwareMessaging does not support android project, only android studio project.

Steps:

~~~bash
mkdir samples
cd samples

# must clone this repo
git clone --depth 1 https://github.com/sdkbox/sdkbox-cocos2d-x-binary.git

# clone sample repo
git clone --depth 1 https://github.com/sdkbox/sdkbox-sample-phunwaremessaging.git

# run sample with specified language and platform
# eg: cpp and ios
./sdkbox-cocos2d-x-binary/run_sample.sh phunwaremessaging cpp ios

# javascript and android studio
cd js && cocos run -p android --android-studio -j 8

# <optional> if exists "download-depends.sh" in sample repo, execute it
# ./sdkbox-sample-phunwaremessaging/download-depends.sh

~~~

Memo:

1.  Sample repo and cocos2dx repo must be in same level directory

~~~
+-- sdkbox-cocos2d-x-binary
+-- sdkbox-sample-phunwaremessaging
| +-- cpp
| +-- lua
| \-- js
~~~
