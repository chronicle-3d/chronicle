#!/bin/python3

import distutils.spawn
import os
import shutil

DAWN_DIR = "vendor/dawn"
DEPOT_TOOLS_DIR = "vendor/depot_tools"

OUT_DIR = "out/dawn"

def checkExecutableExist(executable):
    result = shutil.which(executable)
    if result is None:
        print("Can't find {0}".format(executable))
        quit()

def runExecutable(executable):
    if os.system(executable):
        print("Error executing {0}".format(executable))
        quit()

def createDirectory(directory):
    if not os.path.exists(directory):
        os.makedirs(directory)

workingPath = os.getcwd();

#### DEPOT TOOLS ###

depotPath = "{0}/{1}".format(workingPath, DEPOT_TOOLS_DIR)

os.environ["PATH"] = "{0};{1}".format(depotPath, os.environ["PATH"])
runExecutable("update_depot_tools")

os.environ["DEPOT_TOOLS_WIN_TOOLCHAIN"] = "0"
os.environ["DEPOT_TOOLS_UPDATE"] = "0"


#### PREPARE DAWN ####

os.chdir(DAWN_DIR)

shutil.copyfile("scripts/standalone.gclient", ".gclient")
runExecutable("gclient sync")

# workaround for chrome version. How to handle this?
#createDirectory("chrome")
#if not os.path.exists("chrome/VERSION"):
#        with open("chrome/VERSION", 'w') as f:
#            f.write('\n\n\nPATCH=0\n')

#createDirectory("{0}/{1}/debug".format(workingPath, OUT_DIR))
#createDirectory("{0}/{1}/release".format(workingPath, OUT_DIR))
#shutil.copyfile("{0}/dawn-win32-debug.gn".format(workingPath), "{0}/{1}/debug/args.gn".format(workingPath, OUT_DIR))
#shutil.copyfile("{0}/dawn-win32-release.gn".format(workingPath), "{0}/{1}/debug/release.gn".format(workingPath, OUT_DIR))

#runExecutable("python build/util/lastchange.py -o build/util/LASTCHANGE")
#runExecutable("gn gen {0}/{1}/debug".format(workingPath, OUT_DIR))
#runExecutable("ninja -C {0}/{1}/debug native tint".format(workingPath, OUT_DIR))
#runExecutable("gn gen {0}/{1}/release".format(workingPath, OUT_DIR))
#runExecutable("ninja -C {0}/{1}/release native tint".format(workingPath, OUT_DIR))
