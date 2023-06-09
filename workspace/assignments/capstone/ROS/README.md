# Motion Planning for Mobile Robots -- 移动机器人运动规划: Capstone, Quadrotor Navigation

深蓝学院移动机器人运动规划大作业框架.

---

## Overview

本作业旨在引导您:

* 基于ROS C++, 实现完整的Quadrotor Motion Planning Pipeline

---

## Up & Running

启动Docker后, 打开浏览器, 前往localhost:40080, 进入Web Workspace. **若需要提高清晰度, 可以更改URL中的quality参数**. 启动Terminator, 将两个Shell的工作目录切换如下:

<img src="doc/images/terminator.png" alt="Terminator" width="100%">

在**左侧**的Shell中, 输入如下命令, **编译Search Based Path Finder**

```bash
# build
catkin_make
```

然后**启动解决方案**:

```bash
# set up session:
source devel/setup.bash
# launch:
roslaunch trajectory_generator demo.launch 
```

随后在**RViz**中, 通过**3D Nav Goal**插件, 发布导航目标点, 触发运动规划. **Demo运行结果如下**

<img src="doc/images/demo.gif" alt="Quad Nav Demo" width="100%">

---

## Q1. Motion Planning Pipeline Workflow

整个Pipeline由如下的**State Machine**进行管理 [Click Here to Interact](https://stately.ai/viz/embed/d9d2f910-858d-402e-8bc6-48ec8fc36efd?mode=viz&panel=code&showOriginalLink=1&readOnly=1&pan=1&zoom=1&controls=1):

<img src="doc/images/stm.gif" alt="Quadrotor Motion Planner STM" width="100%">

其中Motion Planning核心算法流程如下:

1. **Path Finding with A Star** [Implementation Here](https://github.com/AlexGeControl/Motion-Planning-for-Mobile-Robots/blob/1586a98e86387e72de01cc1bed357da8ee648e08/workspace/assignments/capstone/ROS/src/trajectory_generator/src/trajectory_generator_node.cpp#L250)
2. **Simplify Path with RDF** [Implementation Here](https://github.com/AlexGeControl/Motion-Planning-for-Mobile-Robots/blob/1586a98e86387e72de01cc1bed357da8ee648e08/workspace/assignments/capstone/ROS/src/trajectory_generator/src/trajectory_generator_node.cpp#L255)
3. **Trajectory Optimization with Collision Check** [Interface Here](https://github.com/AlexGeControl/Motion-Planning-for-Mobile-Robots/blob/1586a98e86387e72de01cc1bed357da8ee648e08/workspace/assignments/capstone/ROS/src/trajectory_generator/src/trajectory_generator_node.cpp#L290)
   1. **Trajectory Optimization** 
      1. **OBVP, K = 1**[Implementation Here](https://github.com/AlexGeControl/Motion-Planning-for-Mobile-Robots/blob/1586a98e86387e72de01cc1bed357da8ee648e08/workspace/assignments/capstone/ROS/src/trajectory_generator/src/trajectory_optimizer.cpp#L154)
      2. **Piecewise Minimum Jerk, K >= 2**[Implementation Here](https://github.com/AlexGeControl/Motion-Planning-for-Mobile-Robots/blob/1586a98e86387e72de01cc1bed357da8ee648e08/workspace/assignments/capstone/ROS/src/trajectory_generator/src/trajectory_optimizer.cpp#L157)
   2. **Collision Check** [Implementation Here](https://github.com/AlexGeControl/Motion-Planning-for-Mobile-Robots/blob/1586a98e86387e72de01cc1bed357da8ee648e08/workspace/assignments/capstone/ROS/src/trajectory_generator/src/trajectory_generator_node.cpp#L298)
   3. **Mid-Waypoint Update for First Unsafe Segment** [Implementation Here](https://github.com/AlexGeControl/Motion-Planning-for-Mobile-Robots/blob/1586a98e86387e72de01cc1bed357da8ee648e08/workspace/assignments/capstone/ROS/src/trajectory_generator/src/trajectory_generator_node.cpp#L263)
   
---

## Q2. Trajectory Evolution

The legends are defined as follows:

* **BLUE** Raw Path, from either **A Star**
* **GREEN** Simplified Path, from either **RDP**
* **RED** Optimized Trajectory, from either **OBVP** or **Piecewise Minimum Jerk**

<img src="doc/images/raw-refined-optimized.gif" alt="Raw, Refined and Optimized" width="100%">

---