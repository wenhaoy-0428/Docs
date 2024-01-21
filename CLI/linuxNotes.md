## Linux

### Get all users. `compgen` is used to generate a complete commands list avaible in Linux. [🌐](https://unix.stackexchange.com/questions/151118/understand-compgen-builtin-command)

```bash
compgen -u
```

### Group

#### Show all groups a user is in

```bash
groups username
```

#### To remove a user from a group

`gpasswd` is a command in Linux used to administer the /etc/group file. It is used to manage the group passwords for a group.
```bash
sudo gpasswd -d [username] [groupname]
```

#### To create a group

```bash
sudo groupadd group_name
```

#### To add a user to a group

```bash
sudo usermod -aG group_name username
```

#### To add write permission to a group/user

The `g` stands for "group", `u` for user and `w` for "write"

```bash
sudo chmod g+w /var/log/mylogfile.log
sudo chmod u+w /var/log/mylogfile.log
```

### Systemd

* Read through this [Intro to systemd](https://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-commands.html) to have a basic idea of what's going on.

每一个 Unit 都有一个配置文件，告诉 Systemd 怎么启动这个 Unit 。
Systemd 默认从目录`/etc/systemd/system/`读取配置文件。但是，里面存放的大部分文件都是符号链接，指向目录`/usr/lib/systemd/system/` (different systems may have different path, use `man systemd.unit` to check)，真正的配置文件存放在那个目录。
systemctl enable命令用于在上面两个目录之间，建立符号链接关系。

```bash
$ sudo systemctl enable clamd@scan.service
# 等同于
$ sudo ln -s '/usr/lib/systemd/system/clamd@scan.service' '/etc/systemd/system/multi-user.target.wants/clamd@scan.service'
```

如果配置文件里面设置了开机启动，systemctl enable命令相当于激活开机启动。
与之对应的，systemctl disable命令用于在两个目录之间，撤销符号链接关系，相当于撤销开机启动。
```bash
$ sudo systemctl disable clamd@scan.service
```

**配置文件的后缀名，就是该 Unit 的种类，比如sshd.socket。如果省略，Systemd 默认后缀名为.service，所以sshd会被理解成sshd.service。**

* [Understanding Systemd Units and Unit Files](https://www.digitalocean.com/community/tutorials/understanding-systemd-units-and-unit-files)

If you wish to modify the way that a unit functions, the best location to do so is within the `/etc/systemd/system` directory. Unit files found in this directory location take precedence over any of the other locations on the filesystem. If you need to modify the system’s copy of a unit file, putting a replacement in this directory is the safest and most flexible way to do this.


#### Where to put unit files

In summary, to answer where to put a unit file: Both `Understanding Systemd Units and Unit Files` and [Where do I put my systemd unit file?](https://unix.stackexchange.com/questions/224992/where-do-i-put-my-systemd-unit-file) believe `/etc/systemd/system` is the best place. And it is in the common cases. However, putting unit file inside this folder, meaning you **may** lose the ability to use `systemctl mask`. A discussion can be found at [How can we mask service whose unit file is located under /etc/systemd/system?](https://unix.stackexchange.com/questions/351692/how-can-we-mask-service-whose-unit-file-is-located-under-etc-systemd-system).



!> **THIS STATEMENT IS ABSOLUTELY WRONG**, I leave it here to as a memory reminder: Because `systemctl enable` creates a link to `/etc/systemd/system`, and due to existing file with the same name (the actual file) in the folder, the symbolic link can't be created. The rest work of `enable` will continue to run, like creating symbolic links to `*.want` folder based on `[Install]` section. The problem here is that `disable` does the exact reverse of `enable`. Because no symbolic link is created in `/etc/systemd/system`, there will be no symlink to be removed from this folder as well, resulting in unit alway start at boot.

> A misunderstanding here is that, I believed a symbolic link will be created right inside `/etc/systemd/system/` after running `systemctl enable` and all units have their file inside `/etc/systemd/system/` will be marked as `enabled`,  which is totally wrong!
> 
> what `systemctl enable` does is [creating only the symlinks suggested in the [Install] section of the unit files.](https://man7.org/linux/man-pages/man1/systemctl.1.html). Therefore, if a unit that doesn't have a `[Install]` section specified , it can only be started **manually**. Also, [`WantedBy` and `RequiredBy`](https://www.digitalocean.com/community/tutorials/understanding-systemd-units-and-unit-files#install-section-directives) are directives used inside `[Install]` section to specify when to start the unit. These directives will create folder named `target.wants` where target is the dependency specified by `WantedBy` and `RequiredBy`. Hence, what `enable` does is create a symbolic link **from** unit file from default folders (check all folders by call `man systemd.unit`), **to** the `target.wants` or `target.required` folder inside  `/etc/systemd/system/`. 
>
> `enable` means it will be started automatically after boot.
>
> I personally believe, once a unit is started, systemd will check if there are `target.wants` folder inside `/etc/systemd/system/` and start all units inside. Like a chain reaction. Therefore, even you specify a unit file inside `/etc/systemd/system/` doesn't mean it can be automatically handled by `systemd`
> 
> In summary, if you don't have a need to use `systemctl mask` there is no reason no reason not to be it inside `/etc/systemd/system/` which has the highest priority.

## MAC

### [Enable git autocomplete](https://www.macinstruct.com/tutorials/how-to-enable-git-tab-autocomplete-on-your-mac/)

```bash
echo 'autoload -Uz compinit && compinit' >> ~/.zshrc
source ~/.zshrc
```

### [Add list color in terminal](https://www.cyberciti.biz/faq/apple-mac-osx-terminal-color-ls-output-option/)

```bash
# -G option enables color
ls -G 
# To permanently enables color
echo 'export CLICOLOR=1' >> ~/.zshrc
echo 'alias ls='ls -G' >> ~/.zshrc
echo 'alias ll='ls -lG' >> ~/.zshrc
# or
export CLICOLOR=1
# refer links above for more color options 
export LSCOLORS=GxFxCxDxBxegedabagaced

```

### [Change Prompt message and color](https://blog.devgenius.io/customize-the-macos-terminal-zsh-4cb387e4f447)

* Add `PROMPT` variable in `.zshrc`
```bash
# %n is username; @ is a mark; %m is machine; %. is directory; %% is % mark.
PROMPT='%n@%m %. %% '
```

* Color starts with `%F{color}` and closed by `%f`
```bash
PROMPT='%F{green}%*%f:%F{blue}%~%f %% '
```

## BashScripts

```bash
alias ability="cd ~/work/ohos/master/foundation/ability/"
alias ohos="cd ~/work/ohos/master/"

build() {
    if [ "$1" = "all" ]; then
        echo "~/work/ohos/master/build.sh --product-name rk3568 --ccache"
        ~/work/ohos/master/build.sh --product-name rk3568 --ccache
    else
        echo "~/work/ohos/master/build.sh --product-name rk3568 --target-cpu arm64 --ccache --build-target" "$1" "$2"
        ~/work/ohos/master/build.sh --product-name rk3568 --target-cpu arm64 --ccache --build-target "$1" "$2"
    fi
}

mvto() {
    echo ~/work/ohos/master/out/rk3568/"$1"
    cp ~/work/ohos/master/out/rk3568/"$1" /mnt/c/Users/Hao/built_files/
}

genSyncMessage() {
    repoArray=()
    while read -r repo; do
        repoArray+=($repo)
    done
    echo "repo sync --force-sync ${repoArray[@]} "
}

syncHelper() {
    grep "repo sync" | awk -F\` '{print $2}' | awk '{print $4}' | genSyncMessage
}
```

## Vim

### toggle line number

```bash
:set nu
:set nonu
```

### copy the whole line

```bash
yy or Y
```