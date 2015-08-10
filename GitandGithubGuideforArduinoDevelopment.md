# ATTENTION #

This page is out of date. Please refer to:
https://github.com/arduino/Arduino/wiki/Git-Guide-for-Arduino

# Git and Github guide for Arduino Development #

Install git locally and create an account on github
Check out Get Started with Git and Github
http://help.github.com/

For those with Subversion background there's a Crash Course:
http://git.or.cz/course/svn.html

## To get started you’ll need to: ##
  1. Take a [quick crash course](http://gitref.org/) on Git
  1. [Install Git](http://help.github.com/git-installation-redirect)
  1. [Generate a keypair](http://help.github.com/key-setup-redirect)
    * http://help.github.com/mac-key-setup/
    * http://help.github.com/linux-key-setup/
    * http://help.github.com/msysgit-key-setup/
    * **You need create this keypair to authorize your commits by machine, and your user account.
  1. http://help.github.com/git-email-settings Set your user and email in git]**

```
git config --global user.name "Your Name"
git config --global user.email you@example.com
```

You are now up and running in with Github. At this point there are three major options for development.  You can create you're own repository. You can clone the Arduino project. You can fork the Arduino project.


## Create your own repository ##
http://help.github.com/creating-a-repo

## Clone the Arduino project ##
```
git clone git@github.com:arduino/Arduino.git
```
If you don’t need the entire project history
```
git clone git@github.com:arduino/Arduino.git --depth 1
```
## Fork the Arduino project for development ##
http://help.github.com/forking/



## There are two development patterns to follow ##

  1. Submit a patch:
    * Clone the repository, update to the master, make edits, and then use git diff, or git format-patch to generate a patch set that can be attached to the bug in the bug system. This is a nice trackable way to make changes and be able to effect multiple files. This is good for most cases, there is still a chance the some one else change would effect your patch, but it's less likely. Your changes are only stored on your local system.
  1. Fork the project:
    * Create a fork of Arduino project, then git clone your fork, and start working. This technique allows for changes to submitted as patches, and/or pull requests. With this mode you can work towards long term goals, and major changes more easily. Also, it's fine for short term patches, and pulls.

## Case 1: Patch Style Development ##
(Thanks to G. Carlini for creating the skeletion of this process)

**Setup:**
To clone the arduino repository and then check out "working" files.
```
git clone git@github.com:arduino/Arduino.git
git checkout branchName
```


**Edit, build, test.**
> Just like normal.

**Check in to your _local_ repository.**
This DOES NOT check into the official arduino repository:
```
git commit -a -m "Summary of the changes being committed. Add the issue number."
```
**Prepare a patch.**
You will send the patch to the arduino team.
```
git diff upstream/master > issueNumber.patch
```

**Update your repository with the latest changes from the arduino repository:**
```
git fetch
git merge upstream/master
```

# Case 2: Fork Style Development #

## Setting up your environment for development: ##
  1. Log into Github,  http://github.com
  1. Go to the Arduino project
> > http://github.com/arduino/Arduino
  1. Select "fork" of the Arduino project in the Github interface.
  1. Then clone your fork
```
git clone git@github.com:username/Arduino.git
```
  1. Set the official Arduino repository as the upstream repository
```
cd Arduino
git remote add upstream git@github.com:arduino/Arduino.git
```
  1. Fetch and merge changes from upstream
```
git fetch upstream
git merge upstream/master 
```
> > You can do a test of the merge. Like --dry-run in Subversion.
```
git merge --no-commit --no-ff upstream/master
```
  1. Now  you are all set up to begin working

## Decide what you’ll be working on ##
  * Check the to do list http://github.com/arduino/Arduino/blob/master/todo.txt
  * Check the issue list at http://code.google.com/p/arduino/issues/list

Note the issue number related to the issue or task your working on. Put this in the comments you make as your work so you can keep track of what work you did related to a specific bug. It’s also handy at this point to think of a test or way of knowing your fix is working.

Seriously consider working in a branch rather than in master all the time.

## Start your day ##
  1. Pull changes from upstream repository
```
git pull upstream master
```

> or
```
git fetch upstream/master
git merge upstream/master
```
  1. Edit, Build, Test
  1. Check status
```
git status
```
  1. git add new files http://stackoverflow.com/questions/572549/difference-of-git-add-a-and-git-add
```
git add file1, file2
git add .
git add *
git add -A
```
  1. Check the files you wanted are added
```
git status 
```
  1. Commit your changes
```
git commit -a -m “These are changes for issue nnnn and here’s what I did.”
```
  1. Push your changes to your github repository
```
git push origin master
```

Check out your changes see if they work. If they look good you can submit a pull request. However, if the master repository which is upstream from you has changed, then you need to fetch the changes from upstream.
  * Pull changes from upstream repository
  * Check that the changes work with your code

Submit your changes to the master project
Submit a pull request, a pull request needs to have the following info:
  * Hyperlink to Google Code Issue Number
  * Description of the change
  * A test or way to verify that this fixed the issue or adds the feature

Please report any typos or questions to the Arduino developer mailing list. There is an expectation to update, edit, and make this document more useful.