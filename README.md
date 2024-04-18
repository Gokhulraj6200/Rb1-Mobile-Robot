# Robotnik's Rb-1 Mobile robot
This project implements a simulation model of Rb-1 robotnik mobile robot using Robot operating system and Gazebo.

## Table of Contents

- [Introduction](#introduction)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Results](#result)
- [Contributing](#contributing)

## Introduction <a name="introduction"></a>
This project showcases the creation of the URDF file for the Rb-1 robot by defining all the required links and joints and by adding required actuator and sensor plugins. A simple yet efficient rosservice in cpp is created to rotate the robot at given specific angle by the user.

## Prerequisites <a name="prerequisites"></a>

- ROS (Robot Operating System)
- Gazebo
- c++ compiler
- Linux
  
## Installation <a name="installation"></a>

1\. clone this repository inside your `catkin_ws/src` directory:

```bash
cd ~/catkin_ws/src
git clone https://github.com/Gokhulraj6200/Rb1-Mobile-Robot.git
```
2\. build the project

```bash
cd ~/catkin_ws
catkin_make
source devel/setup.bash
```

## Usage <a name="usage"></a>

#### Displaying the Robot in RViz

To visualize the robot in RViz, use the following command:

```bash
roslaunch my_rb1_description display.launch
```

#### Moving the Robot in Gazebo

To spawn the robot in the Gazebo simulation, use the following command in terminal_1:

```bash
roslaunch my_rb1_gazebo my_rb1_robot_warehouse.launch
```

To spawn the robot in the Gazebo simulation, use the following command in terminal_2:

```bash
rostopic pub /cmd_vel geometry_msgs/Twist -r 3 -- '[0.5,0.0,0.0]' '[0.0, 0.0, 0.0]'
```

use the following command in terminal_3, to see the robot moving in Gazebo:

```bash
rostopic echo /scan
```

#### Controlling Robot Rotation

To control the robot's rotation, first ensure the `rotate_service` server is running:

```bash
roslaunch my_rb1_ros rotate_service.launch
```

To rotate the robot at any specified degrees, use the following command:

```bash
rosservice call /rotate_robot "degrees: 90"
rosservice call /rotate_robot "degrees: -90"
```

## Results <a name="result"></a>
Robot moving forward:

![Rb-1 linear motion](https://github.com/Gokhulraj6200/Rb1-Mobile-Robot/assets/142083650/a3d9251e-2c76-417d-90e5-507c440f6d1f)


Robot's controlled rotation motion:

![Rb-1 rotation motion](https://github.com/Gokhulraj6200/Rb1-Mobile-Robot/assets/142083650/da75fe1b-ddd2-4098-be81-2cdad2fcf581)

## Contributing
Feel free to contribute to this project by following these simple steps:

1\. Fork the repository.

2\. Create a new branch for your input: `git checkout -b branch-name`.

3\. Make your changes and commit them: `git commit -m 'Add new feature'`.

4\. Push to the branch: `git push origin branch-name`.

5\. Create a pull request.
