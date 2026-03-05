# ROS Environment

[TOC]



## Vcstool

### Ubuntu

```sh
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl # if you haven't already installed curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt-get update
sudo apt-get install python3-vcstool
```

### Python

```sh
sudo pip install -U vcstool

echo 'export PATH="your python binary:$PATH"' >> ~/.zshrc
```



## Colcon

### Ubuntu

```sh
sudo sh -c 'echo "deb [arch=amd64,arm64] http://repo.ros2.org/ubuntu/main `lsb_release -cs` main" > /etc/apt/sources.list.d/ros2-latest.list'
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo update & sudo upgrade
sudo apt-get install python3-colcon-common-extensions
```

### Python

```sh
pip install -U colcon-common-extensions
```

### Source Code

```sh
pip install -U git+https://github.com/colcon/colcon-common-extensions.git
```



## Ros2

### Ubuntu

```sh
locale  # check for UTF-8
sudo apt update && sudo apt install locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8
locale  # verify settings

sudo apt install software-properties-common
sudo add-apt-repository universe

sudo apt update && sudo apt install curl -y
export ROS_APT_SOURCE_VERSION=$(curl -s https://api.github.com/repos/ros-infrastructure/ros-apt-source/releases/latest | grep -F "tag_name" | awk -F\" '{print $4}')
curl -L -o /tmp/ros2-apt-source.deb "https://github.com/ros-infrastructure/ros-apt-source/releases/download/${ROS_APT_SOURCE_VERSION}/ros2-apt-source_${ROS_APT_SOURCE_VERSION}.$(. /etc/os-release && echo ${UBUNTU_CODENAME:-${VERSION_CODENAME}})_all.deb"
sudo dpkg -i /tmp/ros2-apt-source.deb

sudo apt update && sudo apt install ros-dev-tools

sudo apt update 
sudo apt upgrade 
sudo apt install ros-kilted-desktop 
sudo apt install ros-kilted-ros-base

source /opt/ros/kilted/setup.bash
```

### From Source

```sh
mkdir -p ~/ros2_kilted/src
cd ~/ros2_kilted
vcs import --input https://raw.githubusercontent.com/ros2/ros2/kilted/ros2.repos src

sudo apt upgrade

sudo rosdep init
rosdep update
rosdep install --from-paths src --ignore-src -y --skip-keys "fastcdr rti-connext-dds-7.3.0 urdfdom_headers"
```



## Reference

[1] [ROS 2 Documentation](https://docs.ros.org/en/kilted/index.html)