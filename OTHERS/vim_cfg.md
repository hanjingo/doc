# vim配置



## 安装

### 编译安装

1. 下载官方代码

   ```sh
   git clone https://github.com/vim/vim.git
   ```

2. 编译

   - ubuntu

     1. 安装依赖库

        ```sh
        sudo apt-get install libncurses5-dev libgnome2-dev libgnomeui-dev \
            libgtk2.0-dev libatk1.0-dev libbonoboui2-dev \
            libcairo2-dev libx11-dev libxpm-dev libxt-dev python-dev \
            python3-dev ruby-dev lua5.1 lua5.1-dev git
        ```

     2. 删除原有的vim

        ```sh
        # 查看与vim相关的软件
        dpkg -l | grep vim
        # 删除这些软件
        sudo dpkg -P vim
        ```

     3. 编译安装vim

        ```sh
        cd vim
        
        # 配置源码
        # 参数说明：
        # 		--enable-pythoninterp		 使用python2+
        # 		--enable-python3interp 		使用python3+
        ./configure --with-features=huge \
                    --enable-multibyte \
                    --enable-rubyinterp \
                    --enable-python3interp \
                    --with-python-config-dir=/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu \
                    --enable-perlinterp \
                    --enable-luainterp \
                    --enable-gui=gtk2 --enable-cscope --prefix=/usr
                    
        # 编译安装
        make VIMRUNTIMEDIR=/usr/share/vim/vim80
        sudo make install
        ```
     
     4. 设置默认编辑器

        ```sh
        sudo update-alternatives --install /usr/bin/editor editor /usr/bin/vim 1
        sudo update-alternatives --set editor /usr/bin/vim
        sudo update-alternatives --install /usr/bin/vi vi /usr/bin/vim 1
        sudo update-alternatives --set vi /usr/bin/vim
        ```


报错分析:

如果报这个错:

```sh
E484: 无法打开文件 /usr/share/vim/vim80/syntax/syntax.vim
```

可以这样解决:

```sh
cd /usr/share/vim
mv vim80 vim80.bak
mv vim82 vim80
```





## 配置脚本

在目录:`~`下打开（如果不存在就新建）文件`.vimrc`， 添加内容；

[这里供参考](res/.vimrc)



## 配置插件

这一步可能需要翻墙

1. 下载vundle

   ```sh
   git clone https://github.com/VundleVim/Vundle.vim.git ~/.vim/bundle/Vundle.vim
   ```

2. 安装插件

   ```sh
   vim
   # 在vim中输入 :PluginInstall
   :PluginInstall
   ```



## 配置go插件

1. 设置下go代理

   ```sh
   go env -w GOPROXY=https://goproxy.cn,direct
   ```

2. 自动安装Go插件

   ```sh
   # 在vim中输入 :GoInstallBinaries
   :GoInstallBinaries
   ```



## 配置YouCompleteMe

1. 编译YouCompleteMe

   ```sh
   cd YouCompleteMe && ./install.py --omnisharp-completer --go-completer --clangd-completer
   ```

2. 安装ctags

   ```sh
   sudo apt-get install ctags
   ```

   

3. 在想要打开的源码目录生成tag文件

   ```sh
   ctags -R *
   ```

   