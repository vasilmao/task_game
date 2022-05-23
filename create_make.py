#!/usr/bin/env python3

import subprocess
import os
import sys
import json


DEFAULT_EXE_NAME = "a.out"

def is_source(filepath : str) -> bool:
    return (filepath.endswith(".cpp") or filepath.endswith(".c"))

def MakeObjFilename(filepath : str) -> str:
    assert(is_source(filepath))
    file_without_path = os.path.split(filepath)[-1]
    return file_without_path[:file_without_path.rfind(".")] + ".o"

def run_dirs_rec(curdir, save_dirs = False, ban_list : list = []):
    dirs = []
    if (save_dirs):
        dirs.append(curdir)
    sources = []
    for subdir in os.listdir(curdir):
        candidate = os.path.join(curdir, subdir)
        abs_candidate = os.path.abspath(candidate)
        if (os.path.islink(candidate)):
            continue
        elif (os.path.isdir(candidate) and (abs_candidate not in ban_list)):
            subdir_dirs, subdir_sources = run_dirs_rec(candidate, save_dirs, ban_list)
            dirs += subdir_dirs
            sources += subdir_sources
        elif (os.path.isfile(candidate) and (abs_candidate not in ban_list) and is_source(candidate)):
            sources.append(candidate)
    return dirs, sources



class Configuration:
    def __init__(self, IFLAGS="", LFLAGS="", CFLAGS=""):
        self._include_dirs = []
        self._prohibited_dirs = []
        self._LFLAGS = LFLAGS
        self._CFLAGS = CFLAGS
        self._IFLAGS = "NO"
        self._CXX = "g++"
        self._LXX = "g++"
        self._OBJDIR = "obj"
        self._iflags_changed = False
        self._lflags_changed = False
        self._cflags_changed = False
        self._objdir_changed = False
        self._cxx_changed = False
        self._lxx_changed = False
        self._targets = {}
        self._sources = []
    
    def SetLFLAGS(self, s : str) -> None:
        if (self._lflags_changed):
            raise SyntaxError("double lflags option definition")
        self._LFLAGS = s
        self._lflags_changed = True

    def SetCFLAGS(self, s : str) -> None:
        if (self._cflags_changed):
            raise SyntaxError("double cflags option definition")
        self._CFLAGS = s
        self._cflags_changed = True
    
    def SetIFLAGS(self, s : str) -> None:
        if (self._iflags_changed):
            raise SyntaxError("double iflags option definition")
        assert(s in KEYVALUES)
        self._IFLAGS = s
        self._iflags_changed = True

    def SetCXX(self, s : str) -> None:
        if (self._cxx_changed):
            raise SyntaxError("double iflags option definition")
        self._CXX = s
        self._cxx_changed = True

    def SetLXX(self, s : str) -> None:
        if (self._lxx_changed):
            raise SyntaxError("double iflags option definition")
        self._LXX = s
        self._lxx_changed = True
    
    def SetOBJDIR(self, s : str) -> None:
        if (self._objdir_changed):
            raise SyntaxError("double iflags option definition")
        self._OBJDIR = s
        self._objdir_changed = True
    
    def AddTarget(self, source : str, out_name : str) -> None:
        self._targets[source] = out_name
    
    def SetProhibitedDirs(self, dirs : list) -> None:
        self._prohibited_dirs += dirs

    def ParseFlags(self):
        if (not self._objdir_changed):
            if (not os.path.exists("obj")):
                os.mkdir("obj")


    def Search(self):
        print(list(self._targets.keys()))
        dirs, sources = run_dirs_rec(os.path.curdir, self._IFLAGS == "ALL", self._prohibited_dirs + list(map(os.path.abspath ,filter(lambda x: not(x is None) ,self._targets.keys()))))
        if (self._IFLAGS == "ROOT"):
            dirs.append(os.path.curdir)
        self._include_dirs = dirs
        self._sources = sources

    def _WriteTargets(self, file):
        if (len(self._targets) == 0):
            self._targets[None] = DEFAULT_EXE_NAME
        file.write("all: Makefile ")

        for target in self._targets:
            file.write(self._targets[target] + " ")
        
        file.write("\n\n")

        obj_sources = list(os.path.join(self._OBJDIR, MakeObjFilename(cpp_file)) for cpp_file in self._sources)
        
        # if it is just a string, then dependencies are all .obj
        # if it is array or dict, for every .cpp target we need 

        for target in self._targets:
            obj_target = ""
            if not (target is None):
                obj_target = os.path.join(self._OBJDIR, MakeObjFilename(target))
            file.write(self._targets[target] + ": Makefile " + obj_target + " ")
            for obj_source in obj_sources:
                file.write(obj_source + " ")
            file.write("\n\t")
            file.write(self._LXX + " " + obj_target + " ")
            for obj_source in obj_sources:
                file.write(obj_source + " ")
            file.write(self._LFLAGS + " ")
            file.write("-o " + self._targets[target] + "\n\n")
                


    def _WriteObj(self, file):
        flags = list(filter(lambda x: len(x) > 0, self._CFLAGS.split()))
        include_flags = []
        for dir in self._include_dirs:
            include_flags.append("-I")
            include_flags.append(dir)
        for cpp_file in self._sources + list(filter(lambda x: not(x is None) ,self._targets.keys())):
            print(cpp_file)
            obj_name = os.path.join(self._OBJDIR, MakeObjFilename(cpp_file))
            make_rule = subprocess.run([self._CXX, "-MM", "-MT", obj_name] + include_flags + [cpp_file], stdout=subprocess.PIPE).stdout.decode("utf-8")
            make_rule = make_rule.rstrip() + " Makefile\n\t"
            file.write(make_rule)
            file.write(self._CXX + " " + " ".join(include_flags) + " " + self._CFLAGS + " -c " + cpp_file + " -o " + obj_name + "\n\n")


    def WriteMake(self):
        f = open("Makefile", "w")
        self._WriteTargets(f)
        self._WriteObj(f)
        f.close()


def PrettifyStr(s : str) -> str:
    return " ".join((" ".join(s.strip().split("\n"))).split("\t"))

def SetCFLAGS(flag_value, config : Configuration) -> None:
    assert(type(flag_value) == list)
    config.SetCFLAGS(" ".join(map(PrettifyStr, flag_value)))

def SetLFLAGS(flag_value, config : Configuration) -> None:
    assert(type(flag_value) == list)
    config.SetLFLAGS(" ".join(map(PrettifyStr, flag_value)))

def SetIFLAGS(flag_value, config : Configuration) -> None:
    assert(flag_value in KEYVALUES)
    config.SetIFLAGS(flag_value)
    
def SetCXX(flag_value, config : Configuration) -> None:
    config.SetCXX(flag_value)

def SetLXX(flag_value, config : Configuration) -> None:
    config.SetLXX(flag_value)

def SetOBJDIR(flag_value, config : Configuration) -> None:
    config.SetOBJDIR(flag_value)

KEYVARS = {
    "CFLAGS" : SetCFLAGS,
    "LFLAGS" : SetLFLAGS,
    "IFLAGS" : SetIFLAGS,
    "CXX"    : SetCXX,
    "LXX"    : SetLXX,
    "OBJDIR" : SetOBJDIR
}

KEYVALUES = {  # enum actually
    "NO"   : 0,
    "ALL"  : 1,
    "ROOT" : 2
}

def ParseTargets(targets, config : Configuration) -> None:
    # setting targets
    if (type(targets) == list):
        # only .cpp files mentioned
        for target in targets:
            target_filename = os.path.split(target)[-1]
            out_name = target_filename[:target_filename.rfind(".")] + ".out"
            config.AddTarget(target, out_name)
    elif (type(targets) == dict):
        # .cpp -> .out
        for source, out_name in targets.items():
            config.AddTarget(source, out_name)
    elif (type(targets) == str):
        # just one out file with specific name
        config.AddTarget(None, targets)

def ParseFlags(flags : dict, config : Configuration) -> None:
    none_func = lambda x, y: None
    for flag in flags:
        KEYVARS.get(flag, none_func)(flags[flag], config)

def ParseProhibitedDirs(dirs : list, config : Configuration) -> None:
    abs_dirs = list(map(os.path.abspath, dirs))
    config.SetProhibitedDirs(abs_dirs)


def ParseFile(json_dict : dict, config : Configuration):
    if (json_dict.get("targets", -1) != -1):
        ParseTargets(json_dict["targets"], config)
    if (json_dict.get("flags", -1) != -1):
        ParseFlags(json_dict["flags"], config)
    if (json_dict.get("prohibited_dirs", -1) != -1):
        ParseProhibitedDirs(json_dict["prohibited_dirs"], config)


def FindAndParse(filename) -> Configuration:
    config = Configuration()
    if (os.path.exists(filename)):
        file = json.load(open(filename, "r"))
        ParseFile(file, config)
    return config

if __name__ == "__main__":
    if (len(sys.argv) > 1):
        os.chdir(sys.argv[1])
    config = FindAndParse("create_make.json")
    config.ParseFlags()
    config.Search()
    config.WriteMake()