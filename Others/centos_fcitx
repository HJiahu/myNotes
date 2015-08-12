
CentOS 7通过yum安装fcitx五笔输入法

以下通过了亲测：
1、设置源
Posted in Linux at 三月 5th, 2015 / No Comments ?

加入EPEL源
EPEL7几乎是CentOS必备的源:

$ wget http://dl.fedoraproject.org/pub/epel/7/x86_64/e/epel-release-7-5.noarch.rpm
$ sudo rpm -ivh epel-release-7-5.noarch.rpm
$ sudo rpm –import /etc/pki/rpm-gpg/RPM-GPG-KEY-EPEL-7
添加mosquito-myrepo源
mosquito-myrepo是一个私人制作的第三方源，其中包含了fcitx输入法以及基于fcitx的拼音、五笔输入法。

项目地址： https://copr.fedoraproject.org/coprs/mosquito/myrepo/
支持的发行版： Fedora 19/20/21/rawhide 以及RHEL/CentOS 7
$ yum-config-manager –add-repo=https://copr.fedoraproject.org/coprs/mosquito/myrepo/repo/epel-7/mosquito-myrepo-epel-7.repo

2、卸载原来的:
yum remove ibus
yum remove imsettings imsettings-libs im-chooser

3、安装新的
如果只需要安装五笔那么则需要安装包(当然附带会安装一些相应的依赖)：

# yum install fcitx fcitx-table-chinese --enablerepo=mosquito-myrepo
注：这一步，五笔输入法已经安装上了。

如果需要可视化的fcitx设置工具则使用命令：

# yum install fcitx-configtool --enablerepo=mosquito-myrepo

4、进行配置
配置Fcitx
在~/.bashrc中添加如下内容

export GTK_IM_MODULE=fcitx
export QT_IM_MODULE=fcitx
export XMODIFIERS=”@im=fcitx”

关闭gnome-shell 对键盘的监听，然后切换输入法为fcitx:

$ sudo pkill ibus-daemon
$ gsettings set org.gnome.settings-daemon.plugins.keyboard active false
$ imsettings-switch fcitx

重启系统，fcitx自动启动，但图标藏在桌面右下角的通知栏中
打开fcitx的配置工具，选择输入法标签点”+”可以搜索并添加输入法

安装其他输入法

$ yum install fcitx-googlepinyin fcitx-cloudpinyin # 谷歌拼音输入法
$ yum install fcitx-rime fcitx-cloudpinyin # 中州韵输入法
$ yum install fcitx-libpinyin fcitx-cloudpinyin # libpinyin输入法
$ yum install fcitx-sunpinyin sunpinyin-data fcitx-cloudpinyin # sunpinyin输入法

http://seisman.info/fcitx-for-centos-7.html

http://www.92wiki.com/hdwiki/doc-view-424.html

引用文档：http://yuexuan.sinaapp.com/?p=2218

