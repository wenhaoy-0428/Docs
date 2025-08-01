# Git

## [Rebase](https://git-scm.com/docs/git-rebase)

```bash
git rebase [-i | --interactive] [<options>] [--exec <cmd>]
	[--onto <newbase> | --keep-base] [<upstream> [<branch>]]
# all are optional, but <upstream> has to be specified if current branch doesn't have one.
```
* `git rebase` changes the the ancestors of the changing commits.

1. `git rebase master` will check all commits that **current** branch has and `master` doesn't, and save them into a temporary area. 
2. hard reset current branch to match `master` exactly.
3. reapply all commits in the temporary area.

* `git rebase master current` is not included in the synopsis as it's actually only a shortcut for `git checkout current` first then do a `git rebase master`

## [.gitignore](https://www.atlassian.com/git/tutorials/saving-changes/gitignore#git-ignore-patterns)

Create `.gitignore` file to tell `Git` to ignore files match the pattern described in `.gitignore`.

To ignore committed files use `git rm --cached`

```bash
find . -name .DS_Store -print0 | xargs -0 git rm --cached
# -print0 asks the output to be printed in a line with \0 separated.
# -0 is used in concert with -print0.
```

## Common Actions

### Git port 22 time out

* port 22 may be walled by proxy and therefore changing ssh through 443 will solve the problem. [->Ref](https://www.jianshu.com/p/c3aac5024877)

    ```bash
    # vim ~/.ssh/config and add the followings
    Host github.com
    Hostname ssh.github.com
    Port 443## Fetch and Get a clean branch

```bash
# First, run a fetch to update master refs to latest:
git fetch origin master
# Backup your current branch:
git branch backup-master
# Reset to a clean branch
git reset --hard origin/master

```

### [Push in detatched branch](https://stackoverflow.com/questions/38494546/git-push-what-is-the-difference-between-headrefs-heads-branch-and-branch/38496360#38496360)

```bash
git push HEAD:refs/heads/branchName
```

### Show the Hash code of a branch/HEAD

```bash
git rev-parse master
```

### Remove Untracked Files

```bash
# perform dry run: tells you what files will be removed upon executing the clean
git clean -n
# remove untracked files.
git clean -f
# remove untracked files and folders.
git clean -fd
# remove untracked and ignored files.
git clean -fx
```

### create a local branch based on a remote branch

```bash
git fetch origin
git checkout <remote-branch-name> # without remote/origin/ prefix
```

### check "lost" commits.

This happens when I worked on the detached Head branch and checkout to an older commit and the I can't find the latest commit.

`Reflog` is a mechanism to record when the tip of branches are updated.

```bash
git reflog # list records of HEADs
```

### check all remotes

```bash
git remote -v
```

### Check personal contribution to a repository

```bash
git log --author="yanwenhao" --pretty=tformat: --numstat | awk '{ add += $1; subs += $2; loc += $1 - $2 } END { printf "added lines: %s, removed lines: %s, total lines: %s\n", add, subs, loc }' -;
```

### [Remove remote branch](https://stackoverflow.com/questions/2003505/how-do-i-delete-a-git-branch-locally-and-remotely)

``` bash
git push <remote_name> --delete <branch_name>
# for short
git push <remote_name> :<branch_name>
```

### [git add excludes files](https://stackoverflow.com/questions/4475457/add-all-files-to-a-commit-except-a-single-file)

```bash
# add all first then de-select unwanted ones.
git add -u
git reset -- main/dontcheckmein.txt
# intuitively, excludes unwanted ones.
git add --all -- ':!path/to/file1' ':!path/to/file2' ':!path/to/folder1/*'

```

### Stash specific files only [->Ref](https://stackoverflow.com/questions/3040833/how-do-i-stash-only-one-file-out-of-multiple-files-that-have-changed)
```bash
git stash push -p
```

### Rewrite history [->Ref](https://git-scm.com/book/zh/v2/Git-%E5%B7%A5%E5%85%B7-%E9%87%8D%E5%86%99%E5%8E%86%E5%8F%B2)
```bash
git stash # stash needed changes.
git rebase -i HEAD~n # n is the number of old commits.
# change pick to edit then save.
git stash pop
git add
git commit --amend # attach new edits to the commit.
git rebase --continue
```

### [Untrack already tracked files](https://stackoverflow.com/questions/1274057/how-do-i-make-git-forget-about-a-file-that-was-tracked-but-is-now-in-gitignore)

```bash
# remove the file from index 
git rm --cached <file>
# --cached means the action is applied on git and not on filesystem
```





### [What is dot-dot in Git](https://stackoverflow.com/questions/7251477/what-are-the-differences-between-double-dot-and-triple-dot-in-git-dif)

* `git diff A..B` and `git diff A...B` show the difference of tip A and tip B, and the difference between B from A since their common ancestor (basically saying the all commits of B since the common ancestor).

* `git log A..B` and `git log A...B` show the difference of B from A (basically saying all commits of B since the common ancestor), and the difference between A and B (commits that not both A and B have).


---

## Git Large File Storage

[Managing Large Files](https://docs.github.com/en/repositories/working-with-files/managing-large-files)

1. [How to remove that was added in an earlier commit](https://docs.github.com/en/repositories/working-with-files/managing-large-files/about-large-files-on-github#removing-a-file-that-was-added-in-an-earlier-commit)