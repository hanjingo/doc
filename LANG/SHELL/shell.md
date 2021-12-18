# shell指南



## shell自动输入密码

通过shell自动输入密码有以下几种方式：

- 通过管道

    例子：自动安装gdb

    ```shell
    #!/bin/sh
    
    passwd=root123
    echo $passwd|sudo -S apt-get install 
    ```

- 通过重定向

    例子：自动安装g++

    ```shell
    #!/bin/sh
    
    passwd=root123
    sudo apt-get install g++ << EOF
    $passwd
    y
    EOF
    ```

