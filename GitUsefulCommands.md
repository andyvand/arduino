# Git Useful commands #

The following content didn't make it into the [Git and Github Development Guide](GitandGithubGuideforArduinoDevelopment.md)

## Collapse your commits for a pull request ##
Rebasing and applying your changes, then submitting that as a pull request
http://www.gitready.com/advanced/2009/02/11/pull-with-rebase.html

## The Stash, and staging changes ##
How to use the stash:
http://www.gitready.com/beginner/2009/01/10/stashing-your-changes.html

## The Git staging area explanation: ##
http://www.gitready.com/beginner/2009/01/18/the-staging-area.html

## Get a tagged version ##
```
git clone  git@github.com:arduino/Arduino.git
git tag -l
git checkout <tag_name>
```

## Create your own tag ##
```
git tag -a name
```

## show a tagged version ##
```
git show name
```

## Diff a revision and path ##
```
git diff rev path
```

## Restore a file from latest revision ##
```
git checkout filename
```

## List branches ##
```
git branch
```

## Make a branch ##
```
git branch branch_name
```

## Push branch to Github repository ##
```
git push origin branch_name
```

## Check out the branch ##
```
git checkout branch_name
```

## Throw away uncommitted changes ##
```
git --reset hard
```

## Create a new branch based on origin branch\_name instead of the current branch ##
```
git checkout -b orign/master origin/master
git pull origin master
```

## Work on upstream branch other than master ##
```
git checkout --track -b branch_name origin/remote_branch_name
```

## Remove files from deleted from the files system, but not yet removed ##
```
git add -u
```

## Remove directories and files ##
```
git clean -d
```

## Resolve conflicts the quick way when you want all from "their" repository or all from "ours" repository ##
Take all the remote changes
```
git checkout --theirs -- path/to/conflicted-file.txt
```
Take all of our changes
```
git checkout --ours -- path/to/conflicted-file.txt
```