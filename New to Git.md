### git    软件版本控制系统
> Git --- The stupid content tracker

### git的使用：
windows下的[git](http://msysgit.github.io/)

初始化git  ：
-	$ git config --global user.name "Your Name"
-	$ git config --global user.email "email@example.com"

-	开始使用git：
1. 选择一个合适的地方，创建一个空目录如mkdir    /home/jiahu/Git。这个文件夹被称为工作区。
2. cd进这个文件夹，通过git init命令把这个目录变成Git可以管理的仓库 ，你可以发现当前目录下多了一个.git的目录。不可随便删除git目录，这个目录被称为版本库。所有需要进行版本控制的文件都必须放在这个文件夹Git内。 
3. 将相应文件放在Git中：
	-	把一个文件放到Git仓库只需要两步： 
　　　　1. 用命令git add告诉Git，把文件添加到仓库：               
```
　　　　    git add filename          #将指定文件保存至缓存区
			git add -A                #将当前文件夹下的所有文件保存到暂存区。
            git add -u                #将本地已经被跟踪且被修改的文件保存到暂存区。
```
　　　  2. 用命令git commit告诉Git，把文件提交到仓库：         
　　           ` git commit -m "wrote a readme file"     #将文件保存到库中。存在 -m 和其后面的描述是为了标记操作，便于以后纠错。`
4. git status命令可以让我们时刻掌握仓库当前的状态，不是文件的状态。
5. 如果git status告诉你有文件被修改过，用git diff可以查看修改内容。
6. git log命令显示从最近到最远的提交日志。　　如果嫌输出信息太多，可以试试加上`--pretty=oneline`参数。输出的一串数字是版本号，可以截取这串数字的一部分来代表某一个版本。
7. 我们要把当前版本回退到上一个版本，就可以使用git reset命令：                
　　　　` git reset --hard HEAD^ `HEAD相当于一个指针，其指向当前的版本，HEAD^表示前一个版本，HEAD^^表示前两个版本...HEAD~100表示前第100个版本。
8. 使用指令***git reflog***可以看见未来的版本号，如果你返回到了一个过去的版本，但现在想回到未来的版本，这个指令就可以找到未来的版本。
10. git与其他版本库的一个不同之处就是git存在暂存区的概念，只有同时使用git add ***  和git commit -m *** 才会将更改保存到版本库中。使用git add ***将文件保存在暂存区，再使用git commit -m *** 将文件提交至版本库。 
11. 撤销修改git checkout --filename 将文件回到到最近一次的git commit或git add 的状态。如果暂存区有文件就从暂存区恢复文件，如果暂存区没有文件就从版本库中恢复文件。git reset HEAD filename 会将暂存区的文件删除。git checkout --filename 相当于使用版本库或暂存区的文件替换工作区的指定文件。 
12. 如果想将版本库中的文件索引删除而不更改工作区间的文件，可以使用指令git rm。 
13. 远程库：
 	1. 创建ssh  key  ：ssh-keygen -t rsa -C  "email@email"。
	一般而言与.git相同的文件下需要有.ssh文件夹，这样可以不用每次都输入密码。你可以创建多个sshkey，但公钥都必须上传到你的github上。一般在windows下生成的key会保存在用户的根目录下。判断sshkey是否可用  ssh -T git@github.com
	2. 在gitgub下创建一个版本库。
	3. 为远程版本库取个别名：git remote add origin git@github.com:yourgithubname/yourrepository.git在这里，origin是你远程库的别名，当然可以是其他的名字。
	4. 将本地的库推送到远程：git push -u origin master ，origin是你远程版本库的别名，在推送一个全新的库时，一般要加上参数 -u 这样可以使远程的库与新库进行关联，当推送一个旧库时可以不加参数-u。
14. 从云端克隆文件：git clone git@github.com:yourgithubname/repository.git
15. 从云端更新本地库：git pull
16. 将本地文件推送到云端：git push <remote> [branch]
15. git分支： 分支的作用：当仅有一个人在写项目时，分支的作用不是很大，但也会方便你对代码的更改。比如你想测试一个想法但不想改变当前的代码，这时用一个分支会比直接在主分支上进行更改更容易理解与记忆。当多个人合作一个项目时，分支的存在是十分重要的。例如你更改一部分代码需要很长时间，但你又必须将代码推进远程库，这时你可以建立一个你自己的分支，这样你可以在自己的分支上对代码进行更改而不会影响到其他人。主分支应该是稳定的，而对代码进行更改时可以考虑在分支上进行，等分支稳定之后再将分支合并到主分支。
>g it可以创建不同的分支，而主分支被称为master。在没有分支的情况下，HEAD指向主分支master，master会随着commit的重复而变长，每一个节点代表一个commit版本。创建分支的指令：git branch newbranch这样可以创建出一个新的分支newbranch。              
	切换到新的分支：git checkout newbranch 注意与git checkout --filemane 的区别，切换到分支newbranch上工作。余后的工作不会更改主分支master中的内容。上面这两条指令可以合并：git checkout -b newbranch。                   
	查看不同的分支：git branch，当前工作的分支前会有一个星号。                 
	分支的合并：git merge newbranch ，将newbranch合并到当前的分支之上。一般在这之前要将工作的分支切换到主分支之上：git checkout master。随后可以删除无用的分支：                
git branch -d newbranch，那么现在就只剩下主分支master了。
分支之间会存在冲突，一般而言在多人的项目中这种情况出现的概率更大，在这里不做更多的介绍。
使git忽略特定的文件和文件夹：编辑文件 .git/info/exculde, 按照要求在其中添加不想提交的文件类型和文件夹的名字。
