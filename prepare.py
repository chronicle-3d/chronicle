#!/bin/python3

import distutils.spawn
import os
import shutil
import urllib.request
import zipfile
import tempfile

DAWN_DIR = "vendor/dawn"
DEPOT_TOOLS_DIR = "vendor/depot_tools"
RMLUI_DIR = "vendor/rmlui"
FREETYPE_URL = "https://github.com/ubawurinna/freetype-windows-binaries/archive/refs/tags/v2.12.1.zip"
FREETYPE_STRIP_DIR = "freetype-windows-binaries-2.12.1"

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

os.chdir(workingPath)

#### PREPARE RMLUI ####

createDirectory("{0}/Dependencies/freetype".format(RMLUI_DIR))
with urllib.request.urlopen(FREETYPE_URL) as sourceFile:
    with tempfile.TemporaryFile() as destFile:
        destFile.write(sourceFile.read())
        with zipfile.ZipFile(destFile) as freeTypeZip:
            for info in freeTypeZip.infolist():
                destinationName = os.path.relpath(info.filename, FREETYPE_STRIP_DIR)
                if destinationName == ".":
                    continue

                destinationName = "{0}/Dependencies/freetype/{1}".format(RMLUI_DIR, destinationName)

                if info.is_dir():
                    createDirectory(destinationName)
                else:
                    with open(destinationName, 'wb') as outputFile:
                        outputFile.write(freeTypeZip.read(info.filename))
createDirectory("{0}/Dependencies/lib".format(RMLUI_DIR))
createDirectory("{0}/Dependencies/include".format(RMLUI_DIR))
shutil.copytree("{0}/Dependencies/freetype/release dll/win64/".format(RMLUI_DIR), "{0}/Dependencies/lib/".format(RMLUI_DIR), dirs_exist_ok=True) 
shutil.copytree("{0}/Dependencies/freetype/include/".format(RMLUI_DIR), "{0}/Dependencies/include/".format(RMLUI_DIR), dirs_exist_ok=True) 
