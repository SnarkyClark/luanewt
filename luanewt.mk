##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=luanewt
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/stefan/Projects"
ProjectPath            := "/home/stefan/Projects/luanewt"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Stefan
Date                   :=03/25/2013
CodeLitePath           :="/home/stefan/.codelite"
LinkerName             :=g++
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/newt.so
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -fPIC $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." "$(IncludeSwitch)/usr/include" "$(IncludeSwitch)/usr/include/lua5.1" 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)lua5.1 $(LibrarySwitch)newt 
LibPath                := "$(LibraryPathSwitch)." "$(LibraryPathSwitch)/usr/lib/x86_64-linux-gnu" 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/luanewt$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(SharedObjectLinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/luanewt$(ObjectSuffix): luanewt.c $(IntermediateDirectory)/luanewt$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/stefan/Projects/luanewt/luanewt.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/luanewt$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/luanewt$(DependSuffix): luanewt.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/luanewt$(ObjectSuffix) -MF$(IntermediateDirectory)/luanewt$(DependSuffix) -MM "/home/stefan/Projects/luanewt/luanewt.c"

$(IntermediateDirectory)/luanewt$(PreprocessSuffix): luanewt.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/luanewt$(PreprocessSuffix) "/home/stefan/Projects/luanewt/luanewt.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/luanewt$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/luanewt$(DependSuffix)
	$(RM) $(IntermediateDirectory)/luanewt$(PreprocessSuffix)
	$(RM) $(OutputFile)


