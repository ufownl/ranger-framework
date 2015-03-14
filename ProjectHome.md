# Components #
  * **Utils** C++程序设计基础组件库(内存管理、线程同步、STL容器扩展、设计模式泛型组件等)
  * **Framework** 插件式逻辑处理框架
  * **BehaviorTree** 行为树框架
  * **Network** 基于libevent的网络模块
  * **AutoRecast** RecastNavigation的Helper
# Build & Install #
## Linux ##
  1. 安装构建工具cmake-2.8.x，ubuntu用户可通过以下命令安装：
```
sudo apt-get install cmake
```
  1. 安装依赖项：boost\_1\_52\_0、libevent-2.0.21-stable、lua-5.2.1、luabind-0.9、rapidxml-1.13、recastnavigation、cppunit-1.12.1
  1. 打开终端，进入项目所在目录并执行以下命令：
```
mkdir build
cd build
cmake -i ..
sudo make && make install
```
# Downloads #
  * 文件：[luabind-0.9.tar.gz](http://ubuntuone.com/6ph9TLVm8fy0oayL2G3IIU)
  * 说明：luabind-0.9 for lua-5.2。添加了Makefile并修复了使用某些版本的gcc编译预处理出错的问题。

  * 文件：[RecastNavigation.tar.gz](http://ubuntuone.com/3ATLUNr6hyUtxhKGj7JF8w)
  * 说明：recastnavigation-r351。在CMakeLists.txt中增加了install定义，并使其在非Windows平台下生成动态链接库。修改RecastDemo，使其能读取navmesh\_sample生成的数据文件，以方便进行测试。