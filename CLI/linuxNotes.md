## Linux

### Get all users. `compgen` is used to generate a complete commands list avaible in Linux. [🌐](https://unix.stackexchange.com/questions/151118/understand-compgen-builtin-command)

```bash
compgen -u
```

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