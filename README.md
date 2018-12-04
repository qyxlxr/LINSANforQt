﻿# routeDesignByDijkstra

北京地铁线路规划软件（Dijkstra实现）

# 程序运行环境等说明

QT:VS2017+QT5.11.1+QT visual studio Tool

MATLAB：matlab2016b

Mysql: Navicat 12 + Mysql8.0

MFC:VS 2017+ MFC

具体QT安装内容选择可参照

https://blog.csdn.net/qq_23473839/article/details/80523318

在VS工具->扩展与更新下可以直接获取Qt VS Tools，注意配置qmake即可，详情可参照

https://www.jianshu.com/p/10de8e60906b

# 数据库内容

`links`记录了地铁线路信息（相邻两站），双向线路只有其中一个方向

`nodes`记录了地铁站线路信息