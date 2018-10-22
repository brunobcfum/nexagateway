##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=haabNexa
ConfigurationName      :=Debug
WorkspacePath          :=/home/bruno/Nextcloud/sandbox/cpp/CPPWorkspace
ProjectPath            :=/home/bruno/Nextcloud/sandbox/cpp/CPPWorkspace/haabNexa
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=bruno
Date                   :=22/10/18
CodeLitePath           :=/home/bruno/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="haabNexa.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS := -std=c++14 -Wall -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/SerialPort.cpp$(ObjectSuffix) $(IntermediateDirectory)/NexaSocket.cpp$(ObjectSuffix) $(IntermediateDirectory)/Logger.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bruno/Nextcloud/sandbox/cpp/CPPWorkspace/haabNexa/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/SerialPort.cpp$(ObjectSuffix): SerialPort.cpp $(IntermediateDirectory)/SerialPort.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bruno/Nextcloud/sandbox/cpp/CPPWorkspace/haabNexa/SerialPort.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SerialPort.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SerialPort.cpp$(DependSuffix): SerialPort.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SerialPort.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SerialPort.cpp$(DependSuffix) -MM SerialPort.cpp

$(IntermediateDirectory)/SerialPort.cpp$(PreprocessSuffix): SerialPort.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SerialPort.cpp$(PreprocessSuffix) SerialPort.cpp

$(IntermediateDirectory)/NexaSocket.cpp$(ObjectSuffix): NexaSocket.cpp $(IntermediateDirectory)/NexaSocket.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bruno/Nextcloud/sandbox/cpp/CPPWorkspace/haabNexa/NexaSocket.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NexaSocket.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/NexaSocket.cpp$(DependSuffix): NexaSocket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/NexaSocket.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/NexaSocket.cpp$(DependSuffix) -MM NexaSocket.cpp

$(IntermediateDirectory)/NexaSocket.cpp$(PreprocessSuffix): NexaSocket.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/NexaSocket.cpp$(PreprocessSuffix) NexaSocket.cpp

$(IntermediateDirectory)/Logger.cpp$(ObjectSuffix): Logger.cpp $(IntermediateDirectory)/Logger.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/bruno/Nextcloud/sandbox/cpp/CPPWorkspace/haabNexa/Logger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Logger.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Logger.cpp$(DependSuffix): Logger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Logger.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Logger.cpp$(DependSuffix) -MM Logger.cpp

$(IntermediateDirectory)/Logger.cpp$(PreprocessSuffix): Logger.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Logger.cpp$(PreprocessSuffix) Logger.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


